/**
 * @file SceneManager.cpp
 * @author Dan Albert <dan@gingerhq.net>
 *
 * @section LICENSE
 * 
 * Apollo 2D Rendering Engine
 * Copyright (C) 2012 Dan Albert
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * @section DESCRIPTION
 * 
 * Manages all of the objects in the scene.
 * 
 * Manages all Scene Objects allocated to this manager, and handles the
 * viewport for the scene. Responsible for saving and loading the scene as well
 * as updating and drawing objects when appropriate.
 * 
 */
#include "SceneManager.h"

namespace Apollo
{
	SceneManager::SceneManager(RenderSystem* renderSystem)
	{
		m_RenderSystem = renderSystem;
		if (m_RenderSystem == NULL)
		{
			Log("SceneManager recieved NULL reference to the render system.");
			return;
		}

		m_Viewport = new Viewport(m_RenderSystem->GetWidth(), m_RenderSystem->GetHeight());

		m_lastUpdateTime = GetTickCount();
		m_lastDrawTime = m_lastUpdateTime;
	}

	SceneManager::~SceneManager(void)
	{
		Release();
	}

	void SceneManager::Release(void)
	{
		for (int i = 0; i < m_GameAssets.size(); ++i)
		{
			delete m_GameAssets[i];
		}

		m_GameAssets.clear();

		if (m_Viewport)
		{
			m_Viewport->Release();
			m_Viewport = NULL;
		}
	}

	bool SceneManager::SaveState(const char* szPath)
	{
		Log("[SceneManager] Saving scene state.");

		TiXmlDocument doc;
		TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "ISO-8859-1", "");
		doc.LinkEndChild(decl);

		TiXmlElement* rootElem = new TiXmlElement("Scene"); // /Scene
		doc.LinkEndChild(rootElem);

		TiXmlElement* gameObjects = new TiXmlElement("GameObjects"); // /Scene/GameObjects
		rootElem->LinkEndChild(gameObjects);

		if (m_Viewport->GetParent() == NULL)
		{
			// If the Viewport is a child of another object then it will have it's SaveState method called anyways.
			m_Viewport->SaveState(gameObjects);
		}

		for (int i = 0; i < m_GameAssets.size(); ++i)
		{
			if (m_GameAssets[i]->GetParent() == NULL) // Must build in order of heirarchy
			{
				// Since the SceneManager is unaware of the type of each GameObject
				// (Ex. GameObject, SpriteObject), the current Xml element must be
				// passed to the GameObject itself so it can save its own data.
				// This also removes the need for inheriting the SceneManager.
				m_GameAssets[i]->SaveState(gameObjects);
			}
		}

		if (!doc.SaveFile(szPath))
		{
			return false;
		}

		return true;
	}

	bool SceneManager::LoadState(const char* szPath)
	{
		Log("[SceneManager] Loading scene state.");

		TiXmlDocument doc(szPath);
		if (!doc.LoadFile(TIXML_ENCODING_UTF8))
		{
			Log("[SceneManager] Could not load scene state. Error opening file.");
			return false;
		}

		bool result = true;
		TiXmlHandle hDoc(&doc);
		TiXmlElement* elem;
		TiXmlHandle hRoot(0);

		elem = hDoc.FirstChildElement().Element(); // /Scene
		hRoot = TiXmlHandle(elem);

		elem = hRoot.FirstChild("GameObjects").Element(); // /Scene/GameObjects

		if (elem)
		{
			loadChildObjects(elem);
		}

		return result;
	}

	SpriteObject* SceneManager::CreateSpriteObject(const char* szPath)
	{
		m_GameAssets.push_back(new SpriteObject(szPath, m_RenderSystem));
		return (SpriteObject*)m_GameAssets[m_GameAssets.size() - 1];
	}

	void SceneManager::FreeGameObject(SceneObject* object)
	{
		for (int i = 0; i < m_GameAssets.size(); ++i)
		{
			if (m_GameAssets[i] == object)
			{
				delete m_GameAssets.at(i);
				m_GameAssets.erase(m_GameAssets.begin() + i);
				return;
			}
		}
	}

	void SceneManager::Update(void)
	{
		long cTime = GetTickCount();

		long dTime = cTime - m_lastUpdateTime;
		m_lastUpdateTime = cTime;

		for (int i = 0; i < m_GameAssets.size(); ++i)
		{
			m_GameAssets[i]->Update(dTime);
		}

		for (int i = 0; i < m_GameAssets.size(); ++i)
		{
			if (m_GameAssets[i]->IsReadyForCollection())
			{
				this->FreeGameObject(m_GameAssets[i]);
			}
		}
	}

	void SceneManager::Draw(void)
	{
		long cTime = GetTickCount();

		long deltaTime = cTime - m_lastDrawTime;
		m_lastDrawTime = cTime;

		for (int i = 0; i < m_GameAssets.size(); ++i)
		{
			if (m_Viewport->IsOnScreen(m_GameAssets[i]))
			{
				m_GameAssets[i]->Draw(deltaTime, m_Viewport);
			}
		}
	}

	bool SceneManager::loadChildObjects(TiXmlElement* element, SceneObject* parent)
	{
		bool result = true;

		TiXmlElement* childElem = element->FirstChildElement();
		for (childElem; childElem; childElem = childElem->NextSiblingElement())
		{
			if (!loadObject(childElem, parent))
			{
				result = false;
			}
		}

		return result;
	}
	
	bool SceneManager::loadObject(TiXmlElement* element, SceneObject* parent)
	{
		if (!strcmp(element->Value(), "SpriteObject"))
		{
			if (!loadSpriteObjectState(element, parent))
			{
				Log("[SceneManager] SpriteObject failed to load correctly.");
				return false;
			}
			else
			{
				return true;
			}
		}

		else if (!strcmp(element->Value(), "Viewport"))
		{
			if (!loadViewportState(element, parent))
			{
				Log("[SceneManager] SpriteObject failed to load correctly.");
				return false;
			}
			else
			{
				return true;
			}
		}

		else
		{
			Log("[SceneManager] Unknown object type (%s) encountered while loading.", element->Value());
			return false;
		}
	}

	bool SceneManager::loadSpriteObjectState(TiXmlElement* element, SceneObject* parent)
	{
		TiXmlElement* childElem = NULL;
		TiXmlElement* spriteElem = NULL;
		SpriteObject* spriteObject;
		const char* resourcePath;

		spriteElem = element->FirstChildElement("Sprite");
		resourcePath = spriteElem->Attribute("resource");

		spriteObject = this->CreateSpriteObject(resourcePath);
		spriteObject->LoadState(element, parent);
		
		childElem = element->FirstChildElement("Children");
		if (childElem)
		{
			return loadChildObjects(childElem, spriteObject);
		}

		return true;
	}

	bool SceneManager::loadViewportState(TiXmlElement* element, SceneObject* parent)
	{
		m_Viewport->LoadState(element, parent);

		if (!element->NoChildren())
		{
			TiXmlElement* childElem = element->FirstChildElement("Children");
			return loadChildObjects(childElem, m_Viewport);
		}

		return true;
	}
}
