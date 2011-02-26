#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "Apollo.h"

#include <d3d9.h>
#include <d3dx9.h>

#include "Configuration.h"
#include "Debug.h"
#include "Window.h"

namespace Apollo
{
	extern class SceneManager;

	class APOLLO_API RenderSystem
	{
	public:
		RenderSystem(const char* configPath, const char* windowTitle = "Apollo 2D Rendering Engine");
		RenderSystem(
			const char* windowTitle,
			unsigned int width,
			unsigned int height,
			unsigned int bitDepth,
			unsigned int refreshRate,
			unsigned int multiSamplingLevel,
			bool vsync,
			bool windowed);

		virtual ~RenderSystem(void);

		bool Create(
			const char* windowTitle,
			unsigned int width,
			unsigned int height,
			unsigned int bitDepth,
			unsigned int refreshRate,
			unsigned int multiSamplingLevel,
			bool vsync,
			bool windowed);

		void Release(void);

		SceneManager*	GetSceneManager(void);
		void			ReleaseSceneManager(void);

		void StartDrawing(void);	// TODO: SceneManager should be linked into the render system
		void EndDrawing(void);		// so that drawing can be a single method

		// Accessors //
		inline Window*	GetWindow(void)	{	return m_Window;	}

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

		// TODO: These two are only temporarily accessable for testing purposes
		inline IDirect3DDevice9*	GetDevice(void)			const	{	return m_Device;		}
		inline ID3DXSprite*			GetSpriteHandler(void)	const	{	return m_SpriteHandler;	}

		//inline HWND					GetWindowHandle(void)	const	{	return m_Window;		}
		//inline IDirect3DSurface9*	GetBackbuffer(void)		const	{	return m_Backbuffer;	}
		
		// Modifiers //

	protected:
		Window*				m_Window;
		IDirect3D9*			m_Direct3D;
		IDirect3DDevice9*	m_Device;
		ID3DXSprite*		m_SpriteHandler;
		IDirect3DSurface9*	m_Backbuffer;

		// TODO: Why are this a part of the RenderSystem?
		// Consider killing this.
		SceneManager*		m_SceneManager;

		bool setupDisplayFormat(D3DPRESENT_PARAMETERS& pp, unsigned int bitDepth);
		bool setupRefreshRate(D3DPRESENT_PARAMETERS& pp, unsigned int refreshRate);
		bool setupAntiAliasing(D3DPRESENT_PARAMETERS& pp, unsigned int level);
	};
}

#endif // RENDERSYSTEM_H