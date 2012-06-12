/**
 * @file RenderSystem_Direct3D9.h
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
 * Implements a Direct3D9 render system.
 * 
 */
#ifndef RENDERSYSTEM_DIRECT3D9_H
#define RENDERSYSTEM_DIRECT3D9_H

#include <d3d9.h>
#include <d3dx9.h>

#include <RenderSystem.h>
#include <Window.h>

// Class prototypes
//class Texture;
//class TextureAllocator;

class RenderSystem_Direct3D9 : public Apollo::RenderSystem
{
public:
	RenderSystem_Direct3D9(
		const char* configPath,
		const char* windowTitle = "Apollo 2D Rendering Engine");

	RenderSystem_Direct3D9(
		const char* windowTitle,
		unsigned int width,
		unsigned int height,
		unsigned int bitDepth,
		unsigned int refreshRate,
		unsigned int multiSamplingLevel,
		bool vsync,
		bool windowed);

	~RenderSystem_Direct3D9(void);

	bool Initialize(
		const char* windowTitle,
		unsigned int width,
		unsigned int height,
		unsigned int bitDepth,
		unsigned int refreshRate,
		unsigned int multiSamplingLevel,
		bool vsync,
		bool windowed);

	void Release(void);

	void StartDrawing(void);
	void EndDrawing(void);

	inline unsigned int	GetWidth(void) const
	{
		D3DSURFACE_DESC desc;
		m_Backbuffer->GetDesc(&desc);
		return desc.Width;
	}

	inline unsigned int	GetHeight(void) const
	{
		D3DSURFACE_DESC desc;
		m_Backbuffer->GetDesc(&desc);
		return desc.Height;
	}

	inline IDirect3DDevice9*	GetDevice(void)			const	{	return m_Device;		}
	inline ID3DXSprite*			GetSpriteHandler(void)	const	{	return m_SpriteHandler;	}
		
	// Modifiers //

private:
	IDirect3D9*			m_Direct3D;
	IDirect3DDevice9*	m_Device;
	ID3DXSprite*		m_SpriteHandler;
	IDirect3DSurface9*	m_Backbuffer;

	bool setupDisplayFormat(D3DPRESENT_PARAMETERS& pp, unsigned int bitDepth);
	bool setupRefreshRate(D3DPRESENT_PARAMETERS& pp, unsigned int refreshRate);
	bool setupAntiAliasing(D3DPRESENT_PARAMETERS& pp, unsigned int level);
};

#endif // RENDERSYSTEM_DIRECT3D9_H
