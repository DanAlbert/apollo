/**
 * @file GameObject.cpp
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
 * Defines a sprite object with basic kinematic properties that wraps at screen
 * edges.
 * 
 */
#include "GameObject.h"

#include "EntityDef.h"

GameObject::GameObject(Apollo::RenderSystem* renderSystem, Apollo::Viewport* viewport) :
	SpriteObject(renderSystem),
	viewport(viewport),
	angularVelocity(0.0f)
{
}

GameObject::GameObject(
	const char* path,
	Apollo::RenderSystem* renderSystem,
	Apollo::Viewport* viewport) :
		Apollo::SpriteObject(renderSystem),
		viewport(viewport),
		velocity(),
		angularVelocity(0.0f)
{
	this->loadFromFile(path);
}

GameObject::~GameObject(void)
{
}

bool GameObject::InCollisionGroup(const char* group) const throw()
{
	return false;
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
	
	if (!this->resourcePath.empty() && (elem->Attribute("resource") == NULL))
	{
		elem->SetAttribute("resource", this->resourcePath.c_str());
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
	if (this->active)
	{
		this->updateRotation(dTime);
		this->updatePosition(dTime);
		this->wrapScreenEdges();
	}

	Apollo::SpriteObject::Update(dTime);
}

void GameObject::Draw(long dTime, Apollo::SceneObject* view)
{
	SpriteObject::Draw(dTime, view);
	//this->drawBoundingBox();
	//this->drawBorders();
}

bool GameObject::CollidesWith(const GameObject& other) const throw()
{
	return this->GetGeometry().CollidesWith(other.GetGeometry());
}

bool GameObject::HandleCollision(const GameObject& other) throw()
{
	return false;
}

void GameObject::loadFromFile(const char* path) throw(Apollo::IOError)
{
	EntityDef def(path);

	this->geometry = new Apollo::Geometry(def.GetVertexList());
	SpriteObject::loadFromFile(def.GetSpritePath());
	
	this->resourcePath = path;
}

void GameObject::updatePosition(long dTime)
{
	this->Move(this->velocity.x * dTime, this->velocity.y * dTime);
}

void GameObject::updateRotation(long dTime)
{
	this->Rotate(this->angularVelocity * dTime);
}

void GameObject::drawBoundingBox(void) const
{
	Apollo::BoundingBox bb = this->GetGeometry().GetBoundingBox();
	for (int i = 0; i < 4; i++)
	{
		this->renderSystem->DrawLine(
			bb.points[i],
			bb.points[(i + 1) % 4]);
	}
}

void GameObject::drawBorders(void) const
{
	Apollo::Geometry geo = this->GetGeometry().Transformed();
	for (int i = 0; i < geo.GetNumVerticies(); i++)
	{
		Apollo::Vertex a = geo[i];
		Apollo::Vertex b = geo[(i + 1) % geo.GetNumVerticies()];
		
		this->renderSystem->DrawLine(a, b);
	}
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
