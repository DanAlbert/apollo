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
	}

	SceneManager::~SceneManager(void)
	{
		Release();
	}

	void SceneManager::Release(void)
	{
		m_GameAssets.clear();
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

	void SceneManager::Update(long dTime)
	{
		for (int i = 0; i < m_GameAssets.size(); ++i)
		{
			// Update all objects
			m_GameAssets[i]->Update(dTime);
		}
	}

	void SceneManager::Draw(long dTime)
	{
		for (int i = 0; i < m_GameAssets.size(); ++i)
		{
			// Draw all objects that are visible and on screen
			m_GameAssets[i]->Draw(dTime);
		}
	}
}