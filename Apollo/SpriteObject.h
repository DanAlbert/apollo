/**
 * @file SpriteObject.h
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
 * Defines an scene object that is represented by a Sprite.
 * 
 */
#ifndef SPRITEOBJECT_H
#define SPRITEOBJECT_H

#include "Apollo.h"

#include "Debug.h"
#include "SceneObject.h"
#include "RenderSystem.h"
#include "Sprite.h"

namespace Apollo
{
	class APOLLO_API SpriteObject : public SceneObject
	{
	public:
		SpriteObject(const char* path, RenderSystem* renderSystem);
		virtual ~SpriteObject(void);

		virtual void Release(void);

		virtual void SaveState(TiXmlElement*& element, bool elementIsParent = true);
		virtual void LoadState(TiXmlElement* element, SceneObject* parent = NULL);

		virtual void Update(long dTime);
		virtual void Draw(long dTime, SceneObject* view);

	protected:
		Sprite*		m_Sprite;

		SpriteObject(void);

		virtual void loadFromFile(const char* path, RenderSystem* renderSystem);

		virtual void setSpriteState(int cFrame, int cFrameTime = 0);
	};
}

#endif // SPRITEOBJECT_H
