/**
 * @file RenderSystem_Direct3D9.cpp
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
#include "RenderSystem_Direct3D9.h"

#include <Configuration.h>
#include <Debug.h>

#include "TextureAllocator_Direct3D9.h"

RenderSystem_Direct3D9::RenderSystem_Direct3D9(const char* configPath, const char* windowTitle) :
	m_Direct3D(NULL),
	m_Device(NULL),
	m_SpriteHandler(NULL),
	m_Backbuffer(NULL)
{
	try
	{
		Apollo::Configuration cfg(configPath);

		Initialize(
			windowTitle,
			cfg.GetXResolution(),
			cfg.GetYResolution(),
			cfg.GetBitDepth(),
			cfg.GetVRefreshRate(),
			cfg.GetMultiSamplingLevel(),
			cfg.GetVSync(),
			cfg.GetWindowed());
	}
	catch (const Apollo::IOError& e)
	{
		ErrorQuit(e);
	}
}

RenderSystem_Direct3D9::RenderSystem_Direct3D9(
	const char* windowTitle,
	unsigned int width,
	unsigned int height,
	unsigned int bitDepth,
	unsigned int refreshRate,
	unsigned int multiSamplingLevel,
	bool vsync,
	bool windowed) :
		m_Direct3D(NULL),
		m_Device(NULL),
		m_SpriteHandler(NULL),
		m_Backbuffer(NULL)
{
	Initialize(
		windowTitle,
		width,
		height,
		bitDepth,
		refreshRate,
		multiSamplingLevel,
		vsync,
		windowed);
}

RenderSystem_Direct3D9::~RenderSystem_Direct3D9(void)
{
	Release();
}

bool RenderSystem_Direct3D9::Initialize(
	const char* windowTitle,
	unsigned int width,
	unsigned int height,
	unsigned int bitDepth,
	unsigned int refreshRate,
	unsigned int multiSamplingLevel,
	bool vsync,
	bool windowed)
{
	HRESULT result;

	m_Window = new Apollo::Window(windowTitle, width, height);

	m_Direct3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_Direct3D == NULL)
	{
		ErrorQuit(ERR_APOLLO_RENDERSYSTEM_NOD3D);
		return false;
	}

	D3DPRESENT_PARAMETERS pp;
	ZeroMemory(&pp, sizeof(pp));
	pp.Windowed = windowed;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.BackBufferCount = 1;
	pp.BackBufferWidth = width;
	pp.BackBufferHeight = height;
	pp.hDeviceWindow = m_Window->GetWindowHandle();

	if (!setupDisplayFormat(pp, bitDepth))
	{
		return false;
	}
		
	if (!windowed)
	{
		setupRefreshRate(pp, refreshRate);
	}

	// Setup VSync
	pp.PresentationInterval = vsync ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;	
		
	setupAntiAliasing(pp, multiSamplingLevel);

	Log("[RenderSystem_Direct3D9] Creating Direct3D device %dx%dx%u@%uHz in %s mode.",
		width,
		height,
		((pp.BackBufferFormat == D3DFMT_X8R8G8B8) ||
		(pp.BackBufferFormat == D3DFMT_A8R8G8B8) ||
		(pp.BackBufferFormat == D3DFMT_A2R10G10B10)) ? 32 : 16,
		pp.FullScreen_RefreshRateInHz,
		(windowed ? "windowed" : "fullscreen"));

	result = m_Direct3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_Window->GetWindowHandle(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&pp,
		&m_Device);
	if (result != D3D_OK)
	{
		ErrorQuit(ERR_APOLLO_RENDERSYSTEM_NODEV);
		return false;
	}

	// Texture filtering stuff that doesn't seem to be working.
	// Go go dadget documentation!
	/*for (int i = 0; i < 8; i++)
	{
		m_Device->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		m_Device->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		m_Device->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}*/

	Log("[RenderSystem_Direct3D9] Creating Direct3D sprite handler.");
	D3DXCreateSprite(m_Device, &m_SpriteHandler);
	if (m_SpriteHandler == NULL)
	{
		ErrorQuit(ERR_APOLLO_RENDERSYSTEM_NOSPRITE);
		return false;
	}
		
	Log("[RenderSystem_Direct3D9] Retrieving Direct3D backbuffer.");
	m_Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_Backbuffer);
	if (m_Backbuffer == NULL)
	{
		ErrorQuit(ERR_APOLLO_RENDERSYSTEM_BACKBUFFER);
		return false;
	}

	this->m_TextureAllocator = new TextureAllocator_Direct3D9(this);

	return true;
}

void RenderSystem_Direct3D9::Release(void)
{
	if (m_Backbuffer)
	{
		m_Backbuffer->Release();
		m_Backbuffer = NULL;
	}

	if (m_SpriteHandler)
	{
		m_SpriteHandler->Release();
		m_SpriteHandler = NULL;
	}

	if (m_Device)
	{
		m_Device->Release();
		m_Device = NULL;
	}

	if (m_Direct3D)
	{
		m_Direct3D->Release();
		m_Direct3D = NULL;
	}

	if (m_Window)
	{
		m_Window->Release();
		m_Window = NULL;
	}
}

void RenderSystem_Direct3D9::StartDrawing(void)
{
	// start drawing
	m_Device->BeginScene();

	// clear the backbuffer
	m_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0f, 0);

	// start sprite handler
	m_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
}

void RenderSystem_Direct3D9::EndDrawing(void)
{
	// stop
	m_SpriteHandler->End();

	// stop
	m_Device->EndScene();

	// flip
	m_Device->Present(NULL, NULL, NULL, NULL);
}

bool RenderSystem_Direct3D9::setupDisplayFormat(D3DPRESENT_PARAMETERS& pp, unsigned int bitDepth)
{
	D3DFORMAT formats32[] = {
		D3DFMT_X8R8G8B8,
		D3DFMT_A8B8G8R8,
		D3DFMT_A2R10G10B10
	};

	D3DFORMAT formats16[] = {
		D3DFMT_R5G6B5,
		D3DFMT_X1R5G5B5,
		D3DFMT_A1R5G5B5
	};
		
	if (pp.Windowed)
	{
		D3DDISPLAYMODE d3ddm;
		if (FAILED(m_Direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		{
			pp.BackBufferFormat = D3DFMT_UNKNOWN;
			return true;
		}
		else
		{
			pp.BackBufferFormat = d3ddm.Format;
			return true;
		}
	}
	else
	{
		switch (bitDepth)
		{
		case 32:
			for (int i = 0; i < (sizeof(formats32) / sizeof(D3DFORMAT)); i++)
			{
				unsigned int nModes = m_Direct3D->GetAdapterModeCount(
					D3DADAPTER_DEFAULT,
					formats32[i]);

				for (int j = 0; j < nModes; j++)
				{
					D3DDISPLAYMODE mode;
					HRESULT result = m_Direct3D->EnumAdapterModes(
						D3DADAPTER_DEFAULT,
						formats32[i],
						j,
						&mode);

					if (FAILED(result))
					{
						// Invalid format, move on to next format
						break;
					}

					if ((mode.Width == pp.BackBufferWidth) && (mode.Height == pp.BackBufferHeight))
					{
						pp.BackBufferFormat = formats32[i];
						return true;
					}
				}
			}

			// If we reached this point, there were no valid 32 bit formats for the
			// requested screen resolution. Keep going to try to find a 16 bit solution.

		case 16:
			for (int i = 0; i < (sizeof(formats16) / sizeof(D3DFORMAT)); i++)
			{
				unsigned int nModes = m_Direct3D->GetAdapterModeCount(
					D3DADAPTER_DEFAULT,
					formats16[i]);

				for (int j = 0; j < nModes; j++)
				{
					D3DDISPLAYMODE mode;
					HRESULT result = m_Direct3D->EnumAdapterModes(
						D3DADAPTER_DEFAULT,
						formats16[i],
						j,
						&mode);

					if (FAILED(result))
					{
						// Invalid format, move on to next format
						break;
					}

					if ((mode.Width == pp.BackBufferWidth) && (mode.Height == pp.BackBufferHeight))
					{
						pp.BackBufferFormat = formats16[i];
						return true;
					}
				}
			}

			ErrorQuit(ERR_APOLLO_RENDERSYSTEM_PIXELFORMAT);
		}
	}

	return false;
}

bool RenderSystem_Direct3D9::setupRefreshRate(D3DPRESENT_PARAMETERS& pp, unsigned int refreshRate)
{
	unsigned int nModes = m_Direct3D->GetAdapterModeCount(
		D3DADAPTER_DEFAULT,
		pp.BackBufferFormat);

	D3DDISPLAYMODE fallback;

	for (int i = 0; i < nModes; i++)
	{
		D3DDISPLAYMODE mode;
		m_Direct3D->EnumAdapterModes(
			D3DADAPTER_DEFAULT,
			pp.BackBufferFormat,
			i,
			&mode);

		if ((mode.Width == pp.BackBufferWidth) &&
			(mode.Height == pp.BackBufferHeight) &&
			(mode.RefreshRate == refreshRate))
		{
			pp.FullScreen_RefreshRateInHz = refreshRate;
			return true;
		}
			
		if ((mode.Width == pp.BackBufferWidth) &&
			(mode.Height == pp.BackBufferHeight))
		{
			fallback = mode;
		}
	}
		
	Log("[RenderSystem_Direct3D9] Requested refresh rate not supported. Defaulting to %uHz.",
		refreshRate,
		fallback.RefreshRate);
	pp.FullScreen_RefreshRateInHz = fallback.RefreshRate;
		
	return false;
}

bool RenderSystem_Direct3D9::setupAntiAliasing(D3DPRESENT_PARAMETERS& pp, unsigned int level)
{
	// Setup anti aliasing
	DWORD quality;
	if (SUCCEEDED(m_Direct3D->CheckDeviceMultiSampleType(
		D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL,
		pp.BackBufferFormat,
		pp.Windowed, 
		(D3DMULTISAMPLE_TYPE)level,
		&quality)))
	{
		pp.MultiSampleType = (D3DMULTISAMPLE_TYPE)level;
		pp.MultiSampleQuality = 0;
		Log("[RenderSystem_Direct3D9] Set multisampling level to %u.", level);
		return true;
	}

	Log("[RenderSystem_Direct3D9] Unable to set multisampling level to %u.", level);
	return false;
}
