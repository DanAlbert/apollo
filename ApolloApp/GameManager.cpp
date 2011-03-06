#include "GameManager.h"

GameManager::GameManager(Apollo::RenderSystem* renderSystem) :
	SceneManager(renderSystem),
	listener(new PlayerListener(renderSystem->GetWindow()))
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

Player* GameManager::CreatePlayer(const char* path)
{
	m_GameAssets.push_back(new Player(path, m_RenderSystem, listener, this->m_Viewport));
	return (Player*)m_GameAssets[m_GameAssets.size() - 1];
}

void GameManager::Update(void)
{
	this->listener->Update();
	SceneManager::Update();
}

bool GameManager::loadChildObjects(
	TiXmlElement* element,
	Apollo::GameObject* parent)
{
	bool result = true;

	TiXmlElement* childElem = element->FirstChildElement();
	for (childElem; childElem; childElem = childElem->NextSiblingElement())
	{
		if (!strcmp(childElem->Value(), "Player"))
		{
			if (!loadPlayerState(childElem, parent))
			{
				Log("[GameManager] Player failed to load correctly.");
				result = false;
			}
		}

		else
		{
			if (!SceneManager::loadObject(childElem, parent))
			{
				result = false;
			}
		}
	}

	return result;
}

bool GameManager::loadPlayerState(
	TiXmlElement* element,
	Apollo::GameObject* parent)
{
	TiXmlElement* childElem = NULL;
	TiXmlElement* spriteElem = NULL;
	Player* player;
	const char* resourcePath;

	resourcePath = element->Attribute("resource");

	player = this->CreatePlayer(resourcePath);
	player->LoadState(element, parent);
	
	childElem = element->FirstChildElement("Children");
	if (childElem)
	{
		return loadChildObjects(childElem, player);
	}

	return true;
}
