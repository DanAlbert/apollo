/**
 * @file Texture.h
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
 * An interface for render system textures.
 * 
 * An implementing class for a specific render system (ex. Direct3D9) should be
 * in a render system plugin.
 * 
 * A texture is an image that may be drawn to the screen. Textures have width,
 * and height. Any portion of the original texture may be drawn to the screen,
 * and the texture may been drawn rotated, and are drawn with an alpha channel.
 * 
 */
#ifndef TEXTURE_H
#define TEXTURE_H

#include "Apollo.h"
#include "Color.h"
#include "Rectangle.h"
#include "RenderSystem.h"

namespace Apollo
{
	class APOLLO_API Texture
	{
	public:
		Texture(void);
		virtual ~Texture(void);

		virtual bool Release(void) = 0;

		virtual void Draw(
			float x,
			float y,
			float rotation,
			const Color color = Color::White) = 0;

		virtual void Draw(
			float x,
			float y,
			float rotation,
			Rectangle* sourceRect,
			const Color color = Color::White) = 0;

		virtual inline unsigned int	GetWidth(void)	const	{	return m_Width;		}
		virtual inline unsigned int	GetHeight(void)	const	{	return m_Height;	}

	protected:
		unsigned int		m_Width;
		unsigned int		m_Height;
	};
}

#endif // TEXTURE_H
