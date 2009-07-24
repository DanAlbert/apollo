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
		TiXmlDocument doc(szPath);
		if (!doc.LoadFile(TIXML_ENCODING_UTF8))
		{
			return false;
		}

		TiXmlHandle hDoc(&doc);
		TiXmlElement* elem;
		TiXmlHandle hRoot(0);

		elem = hDoc.FirstChildElement().Element(); // /Scene
		hRoot = TiXmlHandle(elem);
		
		elem = hRoot.FirstChild("GameObjects").Element(); // /Scene/GameObjects
		elem = elem->FirstChildElement(); // /Scene/GameObjects/GameObject

		for (elem; elem; elem = elem->NextSiblingElement())
		{
			if (!strcmp(elem->Value(), "SpriteObject"))
			{
				if (!loadSpriteObjectState(elem))
				{
					Log("[SceneManager] SpriteObject failed to load correctly.");
				}
			}

			else
			{
				Log("[SceneManager] Unknown object type (%s) encountered while loading.", elem->Value());
			}
		}

		return true;
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
			m_GameAssets[i]->Draw(dTime);
		}
	}

	bool SceneManager::loadSpriteObjectState(TiXmlElement* element, GameObject* parent)
	{
		TiXmlElement* spriteElem = element->FirstChildElement("Sprite");
		TiXmlElement* childElem = NULL;
		
		if (!element->NoChildren())
		{
			childElem = element->FirstChildElement("Children");
		}

		SpriteObject* spriteObject;

		const char* resourcePath;
		int active;
		int visible;
		int cFrame;		// Not yet implemented
		int animCount;	// Not yet implemented
		float x;
		float y;

		element->QueryIntAttribute("active", &active);
		element->QueryIntAttribute("visible", &visible);
		element->QueryFloatAttribute("x", &x);
		element->QueryFloatAttribute("y", &y);

		resourcePath = spriteElem->Attribute("resource");
		spriteElem->QueryIntAttribute("cFrame", &cFrame);
		spriteElem->QueryIntAttribute("animCount", &animCount);

		spriteObject = this->CreateSpriteObject(resourcePath);
		spriteObject->SetParent(parent);
		spriteObject->SetActive(active);
		spriteObject->SetVisible(visible);
		spriteObject->SetPosition(x, y);

		if (childElem)
		{
			childElem = childElem->FirstChildElement();
			for (childElem; childElem; childElem = childElem->NextSiblingElement())
			{
				if (!strcmp(childElem->Value(), "SpriteObject"))
				{
					if (!loadSpriteObjectState(childElem, spriteObject))
					{
						Log("[SceneManager] SpriteObject failed to load correctly.");
					}
				}

				else
				{
					Log("[SceneManager] Unknown object type (%s) encountered while loading.", childElem->Value());
				}
			}
		}

		return true;
	}
}