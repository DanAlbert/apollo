/**
 * @file Laser.cpp
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
 * Defines a laser object.
 * 
 */
#include "Laser.h"

const char Laser::ENTITY_PATH[] = "Resources/Entities/Laser.xml";
const double Laser::MAX_SPEED = 0.2f;

Laser::Laser(
	Apollo::RenderSystem* renderSystem,
	GameManager* gameManager) :
		GameObject(renderSystem, gameManager)
{
	GameObject::loadFromFile(Laser::ENTITY_PATH);
	this->velocity = Apollo::Vector2(0.1f, 0.0f);
}

Laser::~Laser(void)
{
}

bool Laser::InCollisionGroup(const char* group) const throw()
{
	if (strcmp(group, "laser") == 0)
	{
		return true;
	}
	else if (strcmp(group, "weapon") == 0)
	{
		return true;
	}
	else
	{
		return GameObject::InCollisionGroup(group);
	}
}

void Laser::SaveState(TiXmlElement*& element, bool elementIsParent)
{
	TiXmlElement* elem;

	if (elementIsParent)
	{
		elem = new TiXmlElement("Laser");
		element->LinkEndChild(elem);
	}
	else
	{
		elem = element;
	}

	elem->SetAttribute("resource", this->m_Sprite->GetResourcePath());
	
	GameObject::SaveState(elem, false);
}


void Laser::LoadState(TiXmlElement* element, Apollo::SceneObject* parent)
{
	GameObject::LoadState(element, parent);
}

void Laser::Update(long dTime)
{
	if (this->active)
	{
		float x = sin(this->m_Rotation) * Laser::MAX_SPEED;
		float y = -cos(this->m_Rotation) * Laser::MAX_SPEED;

		this->velocity = Apollo::Vector2(x, y);
	}

	GameObject::Update(dTime);
}

void Laser::HandleCollision(const GameObject& other) throw()
{
	if (other.InCollisionGroup("asteroid") ||
		other.InCollisionGroup("laser"))
	{
		GameObject::HandleCollision(other);
		this->MarkForCollection();
	}

	GameObject::HandleCollision(other);
}
