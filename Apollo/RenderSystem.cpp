#include "RenderSystem.h"

#include "SceneManager.h"

namespace Apollo
{
	RenderSystem::RenderSystem(const char* configPath, const char* windowTitle)
	{
		m_SceneManager = NULL;

		Configuration cfg(configPath);

		if (!Create(
			windowTitle,
			cfg.GetXResolution(),
			cfg.GetYResolution(),
			cfg.GetBitDepth(),
			cfg.GetVRefreshRate(),
			cfg.GetMultiSamplingLevel(),
			cfg.GetVSync(),
			cfg.GetWindowed()))
		{
			
		}
	}

	RenderSystem::RenderSystem(
		const char* windowTitle,
		unsigned int width,
		unsigned int height,
		unsigned int bitDepth,
		unsigned int refreshRate,
		unsigned int multiSamplingLevel,
		bool vsync,
		bool windowed)
	{
		if (!Create(
			windowTitle,
			width,
			height,
			bitDepth,
			refreshRate,
			multiSamplingLevel,
			vsync,
			windowed))
		{
		}
	}

	RenderSystem::~RenderSystem(void)
	{
		Release();
	}

	bool RenderSystem::Create(
		const char* windowTitle,
		unsigned int width,
		unsigned int height,
		unsigned int bitDepth,
		unsigned int refreshRate,
		unsigned int multiSamplingLevel,
		bool vsync,
		bool windowed)
	{
		m_Direct3D = NULL;
		m_Device = NULL;
		m_SpriteHandler = NULL;
		m_Backbuffer = NULL;

		m_Window = new Window(windowTitle, width, height);

		m_Direct3D = Direct3DCreate9(D3D_SDK_VERSION);
		if (m_Direct3D == NULL)
		{
			ErrorQuit("Could not initialize Direct3D.", ERR_APOLLO_RENDERSYSTEM_NOD3D);
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

		// Set display format
		if (windowed)
		{
			D3DDISPLAYMODE d3ddm;
			if (FAILED(m_Direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
			{
				pp.BackBufferFormat = D3DFMT_UNKNOWN;
			}
			else
			{
				pp.BackBufferFormat = d3ddm.Format;
			}
		}
		else
		{
			// Should query the available modes before setting
			switch (bitDepth)
			{
			case 16:
				pp.BackBufferFormat = D3DFMT_R5G6B5;
				break;

			case 32:
				pp.BackBufferFormat = D3DFMT_X8R8G8B8;
				break;

			default:
				pp.BackBufferFormat = D3DFMT_X8R8G8B8;
				break;
			}

			unsigned int nAdapterModes = m_Direct3D->GetAdapterModeCount(
				D3DADAPTER_DEFAULT,
				pp.BackBufferFormat);

			if (!nAdapterModes)
			{
				ErrorQuit("The selected pixel format is not supported by the graphics adapter.",
					ERR_APOLLO_RENDERSYSTEM_PIXELFORMAT);
				return false;
			}

			D3DDISPLAYMODE* modes = new D3DDISPLAYMODE[nAdapterModes];

			bool foundMode = false;
			for (int i = 0; i < nAdapterModes; i++)
			{
				m_Direct3D->EnumAdapterModes(
					D3DADAPTER_DEFAULT,
					pp.BackBufferFormat,
					i,
					&modes[i]);

				if ((modes[i].Width == pp.BackBufferWidth) &&
					(modes[i].Height == pp.BackBufferHeight) &&
					(modes[i].RefreshRate == refreshRate))
				{
					pp.FullScreen_RefreshRateInHz = refreshRate;
					foundMode = true;
				}
			}

			if (!foundMode)
			{
				Log("[RenderSystem] Requested refresh rate not supported. Defaulting to %uHz.",
					modes[0].RefreshRate);
			}

			delete [] modes;
		}

		// Setup anti aliasing
		DWORD quality;
		if (SUCCEEDED(m_Direct3D->CheckDeviceMultiSampleType(
			D3DADAPTER_DEFAULT, 
			D3DDEVTYPE_HAL,
			pp.BackBufferFormat,
			windowed, 
			(D3DMULTISAMPLE_TYPE)multiSamplingLevel,
			&quality)))
		{
			pp.MultiSampleType = (D3DMULTISAMPLE_TYPE)multiSamplingLevel;
			pp.MultiSampleQuality = 0; // This should be documented, because I don't remember what it means.
		}

		// Setup VSync
		pp.PresentationInterval = vsync ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;	

		Log("[RenderSystem] Creating Direct3D device %dx%dx%u in %s mode.",
			width,
			height,
			bitDepth,
			(windowed ? "windowed" : "fullscreen"));

		m_Direct3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			m_Window->GetWindowHandle(),
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&pp,
			&m_Device);

		if (m_Device == NULL)
		{
			ErrorQuit("Could not create the Direct3D device.", ERR_APOLLO_RENDERSYSTEM_NODEV);
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

		Log("[RenderSystem] Creating Direct3D sprite handler.");
		D3DXCreateSprite(m_Device, &m_SpriteHandler);
		if (m_SpriteHandler == NULL)
		{
			ErrorQuit("Could not create the Direct3D sprite handler.", ERR_APOLLO_RENDERSYSTEM_NOSPRITE);
			return false;
		}
		
		Log("[RenderSystem] Retrieving Direct3D backbuffer.");
		m_Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_Backbuffer);
		if (m_Backbuffer == NULL)
		{
			ErrorQuit("Could not retrieve the Direct3D backbuffer.", ERR_APOLLO_RENDERSYSTEM_BACKBUFFER);
			return false;
		}

		return true;
	}

	void RenderSystem::Release(void)
	{
		ReleaseSceneManager();

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

	SceneManager* RenderSystem::GetSceneManager(void)
	{
		if (m_SceneManager == NULL)
		{
			m_SceneManager = new SceneManager(this);
		}

		return m_SceneManager;
	}

	void RenderSystem::ReleaseSceneManager(void)
	{
		if (m_SceneManager)
		{
			delete m_SceneManager;
			m_SceneManager = NULL;
		}
	}

	void RenderSystem::StartDrawing(void)
	{
		// start drawing
		m_Device->BeginScene();

		// clear the backbuffer
		m_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0f, 0);

		// start sprite handler
		m_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	}

	void RenderSystem::EndDrawing(void)
	{
		// stop
		m_SpriteHandler->End();

		// stop
		m_Device->EndScene();

		// flip
		m_Device->Present(NULL, NULL, NULL, NULL);
	}
}