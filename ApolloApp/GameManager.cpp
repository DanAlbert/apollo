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
		m_GameAssets.push_back(new Player(path, m_RenderSystem, listener));
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
	TiXmlElement* spriteElem = NULL;
	TiXmlElement* childElem = NULL;

	Player* player;

#pragma message("TODO: Load SpriteObject animation states.")
	const char* resourcePath;
	int active;
	int visible;
	int cFrame;		// Not yet implemented
	int animCount;	// Not yet implemented
	float x;		// Width and height do not need to be saved
	float y;		// because they are set when the resource loads
	float rotation;

	element->QueryIntAttribute("active", &active);
	element->QueryIntAttribute("visible", &visible);
	element->QueryFloatAttribute("x", &x);
	element->QueryFloatAttribute("y", &y);
	element->QueryFloatAttribute("rotation", &rotation);

	spriteElem = element->FirstChildElement("Sprite");

	resourcePath = spriteElem->Attribute("resource");
	spriteElem->QueryIntAttribute("cFrame", &cFrame);
	spriteElem->QueryIntAttribute("animCount", &animCount);

	player = this->CreatePlayer(resourcePath);
	player->SetParent(parent);
	player->SetActive(active);
	player->SetVisible(visible);
	player->SetPosition(x, y);
	player->SetRotation(rotation);

	player->SetSpriteState(cFrame, animCount);

	childElem = element->FirstChildElement("Children");

	if (childElem)
	{
		loadChildObjects(childElem, player);
	}

	return true;
}
