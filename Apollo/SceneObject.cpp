/**
 * @file SceneObject.cpp
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
 * An object that exists in the scene.
 * 
 * Scene Objects have a position, a size and a rotation. They also exists in a
 * heirarchy. Each object may have any number of child objects, and one or zero
 * parent objects. Objects may be inactive, which disables their Update() step,
 * or invisible, which diasbles their Draw() step.
 * 
 */
#include "SceneObject.h"

namespace Apollo
{
	SceneObject::SceneObject(void)
	{
		active = true;
		visible = true;
		m_XPosition = 0.0f;
		m_YPosition = 0.0f;
		m_Rotation = 0.0f;
		m_Width = 0;
		m_Height = 0;
		m_Parent = NULL;
	}

	SceneObject::~SceneObject(void)
	{
		Release();
	}

	SceneObject& SceneObject::operator =(const SceneObject& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		Release();

		active = rhs.active;
		visible = rhs.visible;
		m_XPosition = rhs.m_XPosition;
		m_YPosition = rhs.m_YPosition;
		m_Parent = rhs.m_Parent;
		m_Children = rhs.m_Children;

		return *this;
	}

	void SceneObject::Release(bool releaseChildren)
	{
		RemoveParent();

		for (int i = 0; i < m_Children.size(); ++i)
		{
			if (releaseChildren)
			{
				m_Children[i]->Release(releaseChildren);
			}
			else
			{
				m_Children[i]->RemoveParent();
			}
		}
	}

	void SceneObject::SaveState(TiXmlElement*& element, bool elementIsParent)
	{
		TiXmlElement* elem;

		if (elementIsParent)
		{
			Log("[SceneObject] Warning: Saving bare SceneObject.");
			elem = new TiXmlElement("SceneObject");
			element->LinkEndChild(elem);
		}
		else
		{
			elem = element;
		}
		
		elem->SetAttribute("active", active);
		elem->SetAttribute("visible", visible);
		elem->SetDoubleAttribute("x", m_XPosition);
		elem->SetDoubleAttribute("y", m_YPosition);
		elem->SetDoubleAttribute("rotation", m_Rotation);

		if (m_Children.size() > 0)
		{
			TiXmlElement* childElem = new TiXmlElement("Children");
			elem->LinkEndChild(childElem);

			for (int i = 0; i < m_Children.size(); ++i)
			{
				m_Children[i]->SaveState(childElem);
			}
		}
	}

	void SceneObject::LoadState(TiXmlElement* element, SceneObject* parent)
	{
		int active;
		int visible;
		float x;
		float y;
		float rotation;

		element->QueryIntAttribute("active", &active);
		element->QueryIntAttribute("visible", &visible);
		element->QueryFloatAttribute("x", &x);
		element->QueryFloatAttribute("y", &y);
		element->QueryFloatAttribute("rotation", &rotation);
		
		this->SetParent(parent);
		this->SetActive(active);
		this->SetVisible(visible);
		this->SetPosition(x, y);
		this->SetRotation(rotation);
	}

	float SceneObject::GetRelativeXPosition(void)
	{
		if (m_Parent == NULL)
		{
			return m_XPosition;
		}
		else
		{
			return m_XPosition - m_Parent->GetRelativeXPosition();
		}
	}

	float SceneObject::GetRelativeYPosition(void)
	{
		if (m_Parent == NULL)
		{
			return m_YPosition;
		}
		else
		{
			return m_YPosition - m_Parent->GetRelativeYPosition();
		}
	}

	void SceneObject::SetActive(bool active)
	{
		active = active;

		for (int i = 0; i < m_Children.size(); ++i)
		{
			m_Children[i]->SetActive(active);
		}
	}

	void SceneObject::SetVisible(bool visible)
	{
		visible = visible;

		for (int i = 0; i < m_Children.size(); ++i)
		{
			m_Children[i]->SetVisible(visible);
		}
	}

	void SceneObject::SetPosition(float x, float y)
	{
		float dX = x - m_XPosition;
		float dY = y - m_YPosition;

		m_XPosition = x;
		m_YPosition = y;

		for (int i = 0; i < m_Children.size(); ++i)
		{
			m_Children[i]->Move(dX, dY);
		}
	}

	void SceneObject::SetRelativePosition(float x, float y)
	{
		float dX = x - GetRelativeXPosition();
		float dY = y - GetRelativeYPosition();

		Move(dX, dY); // Will this cause a problem if the parent is moved before the children?

		for (int i = 0; i < m_Children.size(); ++i)
		{
			m_Children[i]->Move(dX, dY);
		}
	}

	void SceneObject::Move(float x, float y)
	{
		m_XPosition += x;
		m_YPosition += y;

		for (int i = 0; i < m_Children.size(); ++i)
		{
			m_Children[i]->Move(x, y);
		}
	}

	void SceneObject::SetRotation(float rotation)
	{
		m_Rotation = rotation;
	}

	void SceneObject::Rotate(float rotation)
	{
		m_Rotation += rotation;
	}

	void SceneObject::SetParent(SceneObject* parent)
	{
		if (parent)
		{
			RemoveParent();
			parent->addChild(this);
			m_Parent = parent;
		}
	}

	void SceneObject::RemoveParent(void)
	{
		if (m_Parent != NULL)
		{
			m_Parent->removeChild(this);
			m_Parent = NULL;
		}
	}

	void SceneObject::addChild(SceneObject* child)
	{
		m_Children.push_back(child);
	}

	void SceneObject::removeChild(SceneObject* child)
	{
		for (int i = 0; i < m_Children.size(); ++i)
		{
			if (m_Children[i] == child)
			{
				m_Children.erase(m_Children.begin() + i);
				return;
			}
		}
	}
}
