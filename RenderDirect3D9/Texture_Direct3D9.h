/**
 * @file Texture_Direct3D9.h
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
 * Implements a Direct3D9 texture.
 * 
 */
#ifndef TEXTURE_DIRECT3D9_H
#define TEXTURE_DIRECT3D9_H

#include <d3d9.h>
#include <d3dx9.h>

#include <Debug.h>
#include <Texture.h>

#include "RenderSystem_Direct3D9.h"

class Texture_Direct3D9 : public Apollo::Texture
{
public:
	Texture_Direct3D9(const char* path, RenderSystem_Direct3D9* renderSystem) throw(Apollo::IOError);
	Texture_Direct3D9(const Texture_Direct3D9& t);
	~Texture_Direct3D9(void);

	Apollo::Texture& operator= (const Apollo::Texture& rhs);

	bool Release(void);

	void Draw(
		float x,
		float y,
		float rotation,
		const Apollo::Color color = Apollo::Color::White);

	void Draw(
		float x,
		float y,
		float rotation,
		Apollo::Rectangle* sourceRect,
		const Apollo::Color color = Apollo::Color::White);

	inline unsigned int	GetWidth(void)	const	{	return m_Width;		}
	inline unsigned int	GetHeight(void)	const	{	return m_Height;	}

protected:
	ID3DXSprite*		m_SpriteHandler;
	IDirect3DTexture9*	m_Resource;

	char*				m_ResourcePath;

	unsigned int		m_Width;
	unsigned int		m_Height;

	void loadFromFile(const char* path, IDirect3DDevice9* device) throw(Apollo::IOError);
};

#endif // TEXTURE_DIRECT3D9_H
