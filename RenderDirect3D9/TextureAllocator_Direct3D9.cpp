/**
 * @file TextureAllocator_Direct3D9.cpp
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
 * Implements a Direct3D9 texture allocator.
 * 
 */
#include "TextureAllocator_Direct3D9.h"

TextureAllocator_Direct3D9::TextureAllocator_Direct3D9(RenderSystem_Direct3D9* renderSystem) :
	TextureAllocator(renderSystem)
{
}

TextureAllocator_Direct3D9::~TextureAllocator_Direct3D9(void)
{
	Release();
}

Apollo::Texture* TextureAllocator_Direct3D9::GetResource(const char* szPath) throw(Apollo::IOError)
{
	if (m_Resources.find(szPath) == m_Resources.end())
	{
		Apollo::Texture* texture = new Texture_Direct3D9(
			szPath,
			static_cast<RenderSystem_Direct3D9*>(m_RenderSystem));

		m_Resources[szPath] = texture;
	}
		
	return m_Resources[szPath];
}
