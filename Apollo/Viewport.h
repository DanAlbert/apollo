/**
 * @file Viewport.h
 * @author Dan Albert <dan@gingerhq.net>
 * @date Last updated 06/19/2012
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
#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "Apollo.h"

#include "Debug.h"
#include "SceneObject.h"

namespace Apollo
{
	class APOLLO_API Viewport : public SceneObject
	{
	public:
		Viewport(unsigned int width, unsigned int height);
		virtual ~Viewport(void);

		virtual void SaveState(TiXmlElement*& element, bool elementIsParent = true);

		inline virtual void Update(long dTime)					{	return;	}	// Nothing to update
		inline virtual void Draw(long dTime, SceneObject* view)	{	return;	}	// Nothing to draw

		bool IsOnScreen(SceneObject* object);

		void Resize(unsigned int width, unsigned int height);
	};
}

#endif // VIEWPORT_H
