/**
 * @file RenderSystem.h
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
#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "Apollo.h"

#include "Color.h"
#include "Configuration.h"
#include "Debug.h"
#include "Vector2.h"
#include "Window.h"

namespace Apollo
{
	// Class prototypes
	class Texture;
	class TextureAllocator;

	class APOLLO_API RenderSystem
	{
	public:
		RenderSystem(void);
		virtual ~RenderSystem(void);

		static RenderSystem* Create(const char* path);

		virtual bool Initialize(
			const char* windowTitle,
			unsigned int width,
			unsigned int height,
			unsigned int bitDepth,
			unsigned int refreshRate,
			unsigned int multiSamplingLevel,
			bool vsync,
			bool windowed) = 0;

		void Release(void);

		Texture* LoadTexture(const char* path) const;

		virtual void StartDrawing(void) = 0;
		virtual void EndDrawing(void) = 0;

		virtual void DrawLine(const Vector2& a, const Vector2& b, const Color& color = Color::White) = 0;

		// Accessors //
		inline Window*	GetWindow(void)	{	return m_Window;	}
		virtual unsigned int	GetWidth(void) const = 0;
		virtual unsigned int	GetHeight(void) const = 0;
		
		// Modifiers //

	protected:
		Window*				m_Window;
		TextureAllocator*	m_TextureAllocator;
	};
}

#endif // RENDERSYSTEM_H
