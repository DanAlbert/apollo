/**
 * @file RenderSystem.cpp
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
 * Defines an interface for a rendering API.
 * 
 * An implementing render system should be implemented in a plugin.
 * 
 * A render system is an interface to a rendering API such as Direct3D9 or
 * OpenGL. Specific render systems are implemented as pluigins. An implementing
 * class is responsible for initializing the render target (in most cases, a
 * window), initializing rendering components (Direct3D, OpenGL or software
 * renderer), as well as initialization and management of graphics resources
 * such as textures.
 * 
 */
#include "RenderSystem.h"

#include "Texture.h"
#include "TextureAllocator.h"

namespace Apollo
{
	typedef RenderSystem *(*CreateRenderSystem)(
		const char* configPath,
		const char* windowTitle);

	HMODULE library = 0;

	void freeLibrary(void)
	{
		FreeLibrary(library);
	}

	RenderSystem::RenderSystem(void)
	{
	}

	RenderSystem::~RenderSystem(void)
	{
		Release();
	}

	RenderSystem* RenderSystem::Create(const char* path)
	{
		library = LoadLibrary(path);
		if (library)
		{
			Log("Loaded %s.", path);
			atexit(freeLibrary);

			CreateRenderSystem ctor= (CreateRenderSystem)GetProcAddress(library, "CreateRenderSystem");
			if (!ctor)
			{
				ErrorQuit(ERR_APOLLO_RENDERSYSTEM_LOADPROC);
			}
		
			return ctor("apollo.ini", "Apollo 2D Rendering Engine");
		}
		else
		{
			ErrorQuit(ERR_APOLLO_RENDERSYSTEM_LOADLIB);
		}
		return NULL;
	}

	void RenderSystem::Release(void)
	{
		if (this->m_TextureAllocator)
		{
			delete this->m_TextureAllocator;
			this->m_TextureAllocator = NULL;
		}

		if (m_Window)
		{
			//m_Window->Release();
			delete this->m_Window;
			this->m_Window = NULL;
		}
	}

	Texture* RenderSystem::LoadTexture(const char* path) const
	{
		return this->m_TextureAllocator->GetResource(path);
	}
}
