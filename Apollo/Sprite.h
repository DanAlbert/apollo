/**
 * @file Sprite.h
 * @author Dan Albert <dan@gingerhq.net>
 * @date Last updated 06/18/2012
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
 * A collection of Textures that are drawn as an animation.
 * 
 */
#ifndef SPRITE_H
#define SPRITE_H

#include "Apollo.h"

#include <d3d9.h>
#include <d3dx9.h>

#include <vector>

#include "SpriteDef.h"
#include "Debug.h"
#include "RenderSystem.h"
#include "Texture.h"
#include "TextureAllocator.h"

namespace Apollo
{
	class SceneManager;

	class APOLLO_API Sprite
	{
	public:
		Sprite(const char* path, RenderSystem* renderSystem) throw(IOError);
		Sprite(const Sprite& s);	// Do not use until asset management is in place
		virtual ~Sprite(void) throw();

		Sprite& operator= (const Sprite& rhs);	// Do not use until asset management is in place

		virtual bool Load(const char* path, RenderSystem* renderSystem) throw(IOError);
		virtual void Release(void);

		virtual void Draw(float x, float y, long deltaTime);
		virtual void Draw(float x, float y, float rotation, long deltaTime);

		inline char*		GetResourcePath(void)		const	{	return m_ResourcePath;	}
		inline int			GetCurrentFrame(void)		const	{	return m_cFrame;		}
		inline int			GetCurrentFrameTime(void)	const	{	return m_animCount;		}
		inline unsigned int	GetMaxWidth(void)			const	{	return m_maxWidth;		}
		inline unsigned int	GetMaxHeight(void)			const	{	return m_maxHeight;		}

		inline void SetCurrentFrame(int cFrame)			{	m_cFrame = cFrame;	}
		inline void SetCurrentFrameTime(int cFrameTime)	{	m_animCount = cFrameTime;	}

	protected:
		Texture**		m_Textures;

		char*			m_ResourcePath;
		int				m_nFrames;		// Total number of frames in animation.
		int				m_cFrame;		// Current frame of animation.
		int				m_animTime;		// How many ticks each frame will be active.
		int				m_animCount;	// How many ticks the current frame has been active.
		unsigned int	m_maxWidth;
		unsigned int	m_maxHeight;

		virtual void updateAnimation(long deltaTime);
	};
}

#endif // SPRITE_H
