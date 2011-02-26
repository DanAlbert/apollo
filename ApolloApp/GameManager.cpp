#include "GameManager.h"

GameManager::GameManager(Apollo::RenderSystem* renderSystem) :
	SceneManager(renderSystem)
{
}

GameManager::GameManager(const GameManager& gm) :
	SceneManager(gm)
{
}

GameManager::~GameManager(void)
{
	this->Release();
}

bool GameManager::SaveState(const char* path)
{
	return SceneManager::SaveState(path);
}

bool GameManager::LoadState(const char* path)
{
	return SceneManager::LoadState(path);
}

Player* GameManager::CreatePlayer(
	const char* path,
	PlayerListener* listener)
{
		m_GameAssets.push_back(new Player(path, m_RenderSystem, listener));
		return (Player*)m_GameAssets[m_GameAssets.size() - 1];
}

bool GameManager::loadChildObjects(
	TiXmlElement* element,
	Apollo::GameObject* parent)
{
	return SceneManager::loadChildObjects(element, parent);
}

bool GameManager::loadPlayerState(
	TiXmlElement* element,
	Apollo::GameObject* parent)
{
	return false;
}
