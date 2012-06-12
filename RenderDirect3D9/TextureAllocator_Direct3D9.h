/**
 * @file TextureAllocator_Direct3D9.h
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
 * Implements a Direct3D9 texture allocator.
 * 
 */
#ifndef TEXTUREALLOCATOR_DIRECT3D9_H
#define TEXTUREALLOCATOR_DIRECT3D9_H

#include <d3d9.h>
#include <d3dx9.h>

#include <hash_map>

#include <Debug.h>
#include <TextureAllocator.h>

#include "RenderSystem_Direct3D9.h"
#include "Texture_Direct3D9.h"

class TextureAllocator_Direct3D9 : public Apollo::TextureAllocator
{
public:
	TextureAllocator_Direct3D9(RenderSystem_Direct3D9* renderSystem);
	~TextureAllocator_Direct3D9(void);

	Apollo::Texture* GetResource(const char* szPath);
};

#endif // TEXTUREALLOCATOR_DIRECT3D9_H
