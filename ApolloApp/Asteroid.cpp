/**
 * @file Asteroid.cpp
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
 * Defines an asteroid game object.
 * 
 */
#include "Asteroid.h"

#include "GameManager.h"

const char* Asteroid::paths[Size::Invalid] =
{
	"Resources/Entities/SmallAsteroid.xml",
	"Resources/Entities/MediumAsteroid.xml",
	"Resources/Entities/LargeAsteroid.xml"
};

Asteroid::Asteroid(
	const Size size,
	Apollo::RenderSystem* renderSystem,
	GameManager* gameManager)
	throw(Apollo::InvalidArgumentError) :
		GameObject(renderSystem, gameManager),
		size(size)
{
	if (size == Invalid)
	{
		throw Apollo::InvalidArgumentError(ERR_APOLLOAPP_ASTEROID_INVALIDSIZE);
	}

	GameObject::loadFromFile(this->paths[size]);
	this->velocity = Apollo::Vector2(((rand() % 100) - 50) / 1000.0f, ((rand() % 100) - 50) / 1000.0f);
	this->angularVelocity = ((rand() % 100) - 50) / 10000.0f;
}

Asteroid::Asteroid(
	const Size size,
	Apollo::RenderSystem* renderSystem,
	GameManager* gameManager,
	double x,
	double y)
	throw(Apollo::InvalidArgumentError) :
		GameObject(renderSystem, gameManager),
		size(size)
{
	if (size == Invalid)
	{
		throw Apollo::InvalidArgumentError(ERR_APOLLOAPP_ASTEROID_INVALIDSIZE);
	}

	GameObject::loadFromFile(this->paths[size]);
	this->velocity = Apollo::Vector2(((rand() % 100) - 50) / 1000.0f, ((rand() % 100) - 50) / 1000.0f);
	this->angularVelocity = ((rand() % 100) - 50) / 10000.0f;
	this->SetPosition(x, y);
}

Asteroid::Asteroid(
	const char* path,
	Apollo::RenderSystem* renderSystem,
	GameManager* gameManager)
	throw(Apollo::InvalidArgumentError) :
		GameObject(renderSystem, gameManager)
{
	if (strcmp(path, this->paths[Size::Large]) == 0)
	{
		this->size = Size::Large;
	}
	else if (strcmp(path, this->paths[Size::Medium]) == 0)
	{
		this->size = Size::Medium;
	}
	else if (strcmp(path, this->paths[Size::Small]) == 0)
	{
		this->size = Size::Small;
	}
	else
	{
		throw Apollo::InvalidArgumentError(ERR_APOLLOAPP_ASTEROID_INVALIDSIZE);
	}

	GameObject::loadFromFile(path);
	this->velocity = Apollo::Vector2(((rand() % 100) - 50) / 1000.0f, ((rand() % 100) - 50) / 1000.0f);
	this->angularVelocity = ((rand() % 100) - 50) / 10000.0f;
}

Asteroid::~Asteroid(void)
{
}

bool Asteroid::InCollisionGroup(const char* group) const throw()
{
	if (strcmp(group, "asteroid") == 0)
	{
		return true;
	}
	else if (strcmp(group, "large asteroid") == 0)
	{
		return true;
	}
	else
	{
		return GameObject::InCollisionGroup(group);
	}
}

void Asteroid::SaveState(TiXmlElement*& element, bool elementIsParent)
{
	TiXmlElement* elem;

	if (elementIsParent)
	{
		elem = new TiXmlElement("Asteroid");
		element->LinkEndChild(elem);
	}
	else
	{
		elem = element;
	}
	
	GameObject::SaveState(elem, false);
}


void Asteroid::LoadState(TiXmlElement* element, Apollo::SceneObject* parent)
{
	GameObject::LoadState(element, parent);
}

void Asteroid::Update(long dTime)
{
	if (this->active)
	{
		// Asteroid stuff
	}

	GameObject::Update(dTime);
}

void Asteroid::HandleCollision(const GameObject& other) throw()
{
	if (other.InCollisionGroup("weapon"))
	{
		GameObject::HandleCollision(other);
		this->MarkForCollection();
		switch (this->size)
		{
		case Size::Large:
			this->gameManager->CreateAsteroid(Size::Medium, this->GetXPosition(), this->GetYPosition());
			this->gameManager->CreateAsteroid(Size::Medium, this->GetXPosition(), this->GetYPosition());
			break;
		case Size::Medium:
			this->gameManager->CreateAsteroid(Size::Small, this->GetXPosition(), this->GetYPosition());
			this->gameManager->CreateAsteroid(Size::Small, this->GetXPosition(), this->GetYPosition());
			break;
		case Size::Small:
		default:
			break;
		}
		
	}

	return GameObject::HandleCollision(other);
}

const Asteroid::Size Asteroid::stringToSize(const char* str) throw()
{
	if (str == NULL)
	{
		return Size::Invalid;
	}
	else if (ToLower(str) == "small")
	{
		return Size::Small;
	}
	else if (ToLower(str) == "medium")
	{
		return Size::Medium;
	}
	else if (ToLower(str) == "large")
	{
		return Size::Large;
	}
	else
	{
		return Size::Invalid;
	}
}
