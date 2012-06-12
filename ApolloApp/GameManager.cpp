/**
 * @file GameManager.cpp
 * @author Dan Albert <dan@gingerhq.net>
 * @date Last updated 06/11/2012
 * @version 0.2.53
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
 * Defines a custom scene manager.
 *
 * Has facilities for saving and loading application specific game objects and
 * also handles the Player object.
 * 
 */
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

Asteroid* GameManager::CreateAsteroid(const char* path)
{
	m_GameAssets.push_back(new Asteroid(path, m_RenderSystem, this->m_Viewport));
	return (Asteroid*)m_GameAssets[m_GameAssets.size() - 1];
}

void GameManager::Update(void)
{
	this->listener->Update();
	SceneManager::Update();
}

bool GameManager::loadChildObjects(
	TiXmlElement* element,
	Apollo::SceneObject* parent)
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
		
		else if (!strcmp(childElem->Value(), "Asteroid"))
		{
			if (!loadAsteroidState(childElem, parent))
			{
				Log("[GameManager] Asteroid failed to load correctly.");
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
	Apollo::SceneObject* parent)
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

bool GameManager::loadAsteroidState(
	TiXmlElement* element,
	Apollo::SceneObject* parent)
{
	TiXmlElement* childElem = NULL;
	TiXmlElement* spriteElem = NULL;
	Asteroid* asteroid;
	const char* resourcePath;

	resourcePath = element->Attribute("resource");

	if (resourcePath)
	{
		asteroid = this->CreateAsteroid(resourcePath);
		asteroid->LoadState(element, parent);
	
		childElem = element->FirstChildElement("Children");
		if (childElem)
		{
			return loadChildObjects(childElem, asteroid);
		}

		return true;
	}
	else
	{
		return false;
	}
}
