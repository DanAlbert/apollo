/**
 * @file Viewport.cpp
 * @author Dan Albert
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
 * Defines a rendering viewport.
 * 
 * A viewport defines a subsection of a scene to render. The size of the
 * viewport defines how much of the scene (in pixels) will be rendered.
 * 
 */
#include "Viewport.h"

namespace Apollo
{
	Viewport::Viewport(unsigned int width, unsigned int height)
	{
		m_Width = width;
		m_Height = height;
	}

	Viewport::~Viewport(void)
	{
		Release();
	}

	void Viewport::SaveState(TiXmlElement*& element, bool elementIsParent)
	{
		TiXmlElement* elem;

		if (elementIsParent)
		{
			elem = new TiXmlElement("Viewport");
			element->LinkEndChild(elem);
		}
		else
		{
			elem = element;
		}

		SceneObject::SaveState(elem, false);
	}

	bool Viewport::IsOnScreen(SceneObject* object)
	{
		if (((object->GetXPosition() + object->GetWidth()) > this->GetXPosition()) &&	// Within left bound
			(object->GetXPosition() < (this->GetXPosition() + this->GetWidth())) &&		// Within right bound
			((object->GetYPosition() + object->GetHeight()) > this->GetYPosition()) &&	// Within upper bound
			(object->GetYPosition() < (this->GetYPosition() + this->GetHeight())))		// Within lower bound
		{
			return true;
		}
		
		else
		{
			return false;
		}
	}

	void Viewport::Resize(unsigned int width, unsigned int height)
	{
		m_Width = width;
		m_Height = height;
	}
}
