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

		m_Viewport->SaveState(rootElem);

		TiXmlElement* gameObjects = new TiXmlElement("GameObjects"); // /Scene/GameObjects
		rootElem->LinkEndChild(gameObjects);

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

		elem = hRoot.FirstChild("Viewport").Element(); // /Scene/Viewport
		if (!loadViewportState(elem))
		{
			Log("[SceneManager] SpriteObject failed to load correctly.");
			result = false;
		}

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

	void SceneManager::FreeSpriteObject(SpriteObject* object)
	{
		for (int i = 0; i < m_GameAssets.size(); ++i)
		{
			if (m_GameAssets[i] == object)
			{
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
			// Update all objects
			m_GameAssets[i]->Update(dTime);
		}
	}

	void SceneManager::Draw(void)
	{
		long cTime = GetTickCount();

		long dTime = cTime - m_lastDrawTime;
		m_lastDrawTime = cTime;

		for (int i = 0; i < m_GameAssets.size(); ++i)
		{
			// Draw all objects that are visible and on screen
			if (m_Viewport->IsOnScreen(m_GameAssets[i]))
			{
				m_GameAssets[i]->Draw(dTime, m_Viewport);
			}
		}
	}

	bool SceneManager::loadChildObjects(TiXmlElement* element, GameObject* parent)
	{
		bool result = true;

		TiXmlElement* childElem = element->FirstChildElement();
		for (childElem; childElem; childElem = childElem->NextSiblingElement())
		{
			if (!strcmp(childElem->Value(), "SpriteObject"))
			{
				if (!loadSpriteObjectState(childElem, parent))
				{
					Log("[SceneManager] SpriteObject failed to load correctly.");
					result = false;
				}
			}

			else
			{
				Log("[SceneManager] Unknown object type (%s) encountered while loading.", childElem->Value());
				result = false;
			}
		}

		return result;
	}

	bool SceneManager::loadSpriteObjectState(TiXmlElement* element, GameObject* parent)
	{
		TiXmlElement* spriteElem = NULL;
		TiXmlElement* childElem = NULL;

		SpriteObject* spriteObject;

#pragma message("TODO: Load SpriteObject animation states.")
		const char* resourcePath;
		int active;
		int visible;
		int cFrame;		// Not yet implemented
		int animCount;	// Not yet implemented
		float x;		// Width and height do not need to be saved
		float y;		// because they are set when the resource loads

		element->QueryIntAttribute("active", &active);
		element->QueryIntAttribute("visible", &visible);
		element->QueryFloatAttribute("x", &x);
		element->QueryFloatAttribute("y", &y);

		spriteElem = element->FirstChildElement("Sprite");

		resourcePath = spriteElem->Attribute("resource");
		spriteElem->QueryIntAttribute("cFrame", &cFrame);
		spriteElem->QueryIntAttribute("animCount", &animCount);

		spriteObject = this->CreateSpriteObject(resourcePath);
		spriteObject->SetParent(parent);
		spriteObject->SetActive(active);
		spriteObject->SetVisible(visible);
		spriteObject->SetPosition(x, y);

		childElem = element->FirstChildElement("Children");

		if (childElem)
		{
			loadChildObjects(childElem, spriteObject);
		}

		return true;
	}

	bool SceneManager::loadViewportState(TiXmlElement* element)
	{
		TiXmlElement* childElem = NULL;

		float x;
		float y;
		int width;
		int height;

		element->QueryFloatAttribute("x", &x);
		element->QueryFloatAttribute("y", &y);
		element->QueryIntAttribute("width", &width);
		element->QueryIntAttribute("height", &height);

		m_Viewport->Resize(width, height);
		m_Viewport->SetPosition(x, y);

		if (!element->NoChildren())
		{
			childElem = element->FirstChildElement("Children");
			loadChildObjects(childElem, m_Viewport);
		}

		return true;
	}
}