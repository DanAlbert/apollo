/**
 * @file GameObject.cpp
 * @author Dan Albert <dan@gingerhq.net>
 * @date Last updated 06/11/2012
 * @version 0.2.53
 *
 * @section LICENSE
 * 
 * Apollo 2D Rendering Engine
 * Copyright (C) 2011 Dan Albert
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
 * Defines a sprite object with basic kinematic properties that wraps at screen
 * edges.
 * 
 */
#include "GameObject.h"

GameObject::GameObject(Apollo::Viewport* viewport) :
	viewport(viewport)
{
}

GameObject::GameObject(
	const char* path,
	Apollo::RenderSystem* renderSystem,
	Apollo::Viewport* viewport) :
		viewport(viewport),
		velocity()
{
	this->loadFromFile(path, renderSystem);
}

GameObject::~GameObject(void)
{
}

void GameObject::SaveState(TiXmlElement*& element, bool elementIsParent)
{
	TiXmlElement* elem;

	if (elementIsParent)
	{
		elem = new TiXmlElement("GameObject");
		element->LinkEndChild(elem);
	}
	else
	{
		elem = element;
	}
	
	elem->SetDoubleAttribute("velocity.x", this->velocity.x);
	elem->SetDoubleAttribute("velocity.y", this->velocity.y);
	elem->SetDoubleAttribute("angular-velocity", this->angularVelocity);

	SpriteObject::SaveState(elem, false);
}


void GameObject::LoadState(TiXmlElement* element, Apollo::SceneObject* parent)
{
	element->QueryDoubleAttribute("velocity.x", &this->velocity.x);
	element->QueryDoubleAttribute("velocity.y", &this->velocity.y);
	element->QueryDoubleAttribute("angular-velocity", &this->angularVelocity);
	Apollo::SpriteObject::LoadState(element, parent);
}

void GameObject::Update(long dTime)
{
	if (this->m_Active)
	{
		this->updateRotation(dTime);
		this->updatePosition(dTime);
		this->wrapScreenEdges();
	}

	Apollo::SpriteObject::Update(dTime);
}

void GameObject::updatePosition(long dTime)
{
	this->Move(this->velocity.x * dTime, this->velocity.y * dTime);
}

void GameObject::updateRotation(long dTime)
{
	this->Rotate(this->angularVelocity * dTime);
}

void GameObject::wrapScreenEdges(void)
{
	if ((this->m_XPosition + this->m_Width) < this->viewport->GetXPosition())
	{
		this->m_XPosition = this->viewport->GetXPosition() + this->viewport->GetWidth();
	}
	else if (this->m_XPosition > (this->viewport->GetXPosition() + this->viewport->GetWidth()))
	{
		this->m_XPosition = this->viewport->GetXPosition() - this->m_Width;
	}

	if ((this->m_YPosition + this->m_Height) < this->viewport->GetYPosition())
	{
		this->m_YPosition = this->viewport->GetYPosition() + this->viewport->GetHeight();
	}
	else if (this->m_YPosition > (this->viewport->GetYPosition() + this->viewport->GetHeight()))
	{
		this->m_YPosition = this->viewport->GetYPosition() - this->m_Height;
	}
}
