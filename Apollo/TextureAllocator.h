/**
 * @file TextureAllocator.h
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
 * A container interface for managing texture allocation.
 * 
 * Deriving classes should be implemented in a render system plugin.
 * 
 * Ensures that each texture is only loaded into memory once, and that the
 * texture is released when there are no more references to it (not yet
 * implemented).
 * 
 */
#ifndef TEXTUREALLOCATOR_H
#define TEXTUREALLOCATOR_H

#include "Apollo.h"

#include <hash_map>

#include "Debug.h"
#include "RenderSystem.h"
#include "Texture.h"

namespace Apollo
{
	class APOLLO_API TextureAllocator
	{
	public:
		TextureAllocator(RenderSystem* renderSystem);
		virtual ~TextureAllocator(void);

		void Release(void);

		virtual Texture* GetResource(const char* szPath) = 0;

	protected:
		stdext::hash_map<std::string, Texture*> m_Resources;
		
		RenderSystem* m_RenderSystem;
	};
}

#endif // TEXTUREALLOCATOR_H
