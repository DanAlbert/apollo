/**
 * @file Texture.cpp
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
#include "Texture.h"

namespace Apollo
{
	Texture::Texture(void) :
		m_Width(0),
		m_Height(0)
	{
	}

	Texture::~Texture(void)
	{
	}
}
