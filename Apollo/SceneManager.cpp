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

	void SceneManager::SaveState(const char* szPath)
	{
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

		doc.SaveFile(szPath);
	}

	void SceneManager::LoadState(const char* szPath)
	{
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
}