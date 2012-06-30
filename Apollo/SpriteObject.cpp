/**
 * @file SpriteObject.cpp
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
 * Defines an scene object that is represented by a Sprite.
 * 
 */
#include "SpriteObject.h"

namespace Apollo
{
	// Private constructor for derived classes
	SpriteObject::SpriteObject(RenderSystem* renderSystem) :
		m_Sprite(NULL),
		renderSystem(renderSystem)
	{
	}

	SpriteObject::SpriteObject(const char* path, RenderSystem* renderSystem) throw(IOError) :
		m_Sprite(NULL),
		renderSystem(renderSystem)
	{
		try
		{
			loadFromFile(path);
		}
		catch (const IOError& e)
		{
			ErrorQuit(e);
		}
	}

	SpriteObject::~SpriteObject(void) throw()
	{
		Release();
	}

	void SpriteObject::Release(void)
	{
		if (m_Sprite != NULL)
		{
			delete m_Sprite;
			m_Sprite = NULL;
		}
	}

	void SpriteObject::SaveState(TiXmlElement*& element, bool elementIsParent)
	{
		TiXmlElement* elem;

		if (elementIsParent)
		{
			elem = new TiXmlElement("SpriteObject");
			element->LinkEndChild(elem);
		}
		else
		{
			elem = element;
		}
		
		TiXmlElement* spriteElem = new TiXmlElement("Sprite");
		elem->LinkEndChild(spriteElem);

		spriteElem->SetAttribute("resource", m_Sprite->GetResourcePath());
		spriteElem->SetAttribute("cFrame", m_Sprite->GetCurrentFrame());
		spriteElem->SetAttribute("animCount", m_Sprite->GetCurrentFrameTime());

		SceneObject::SaveState(elem, false);
	}

	void SpriteObject::LoadState(TiXmlElement* element, SceneObject* parent)
	{
		TiXmlElement* spriteElem = NULL;
		
		int cFrame;
		int animCount;
		
		spriteElem = element->FirstChildElement("Sprite");

		spriteElem->QueryIntAttribute("cFrame", &cFrame);
		spriteElem->QueryIntAttribute("animCount", &animCount);

		spriteElem = element->FirstChildElement("Sprite");

		this->setSpriteState(cFrame, animCount);
		SceneObject::LoadState(element, parent);
	}

	void SpriteObject::Update(long dTime)
	{
		if (active)
		{
		}
	}

	void SpriteObject::Draw(long dTime, SceneObject* view)
	{
		if (visible)
		{
			if (m_Sprite)
			{
				m_Sprite->Draw(
					m_XPosition - view->GetXPosition(),
					m_YPosition - view->GetYPosition(),
					m_Rotation,
					dTime);
			}
		}
	}

	void SpriteObject::loadFromFile(const char* path) throw(IOError)
	{
		this->m_Sprite = new Sprite(path, this->renderSystem);

		this->m_Width = m_Sprite->GetMaxWidth();
		this->m_Height = m_Sprite->GetMaxHeight();
	}

	void SpriteObject::setSpriteState(int cFrame, int cFrameTime)
	{
		this->m_Sprite->SetCurrentFrame(cFrame);
		this->m_Sprite->SetCurrentFrameTime(cFrameTime);
	}
}
