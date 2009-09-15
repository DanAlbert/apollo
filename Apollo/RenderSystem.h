#ifndef __RENDERSYSTEM_H__
#define __RENDERSYSTEM_H__

#include "Apollo.h"

#include <d3d9.h>
#include <d3dx9.h>

#include "Configuration.h"
#include "Debug.h"
//#include "SceneManager.h"
#include "Window.h"

namespace Apollo
{
	class SceneManager;

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
			bool vsync,
			bool windowed);

		virtual ~RenderSystem(void);

		bool Create(
			const char* windowTitle,
			unsigned int width,
			unsigned int height,
			unsigned int bitDepth,
			unsigned int refreshRate,
			bool vsync,
			bool windowed);

		void Release(void);

		SceneManager*	GetSceneManager(void);
		void			ReleaseSceneManager(void);

		void StartDrawing(void);	// SceneManager should be linked into the render system
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

		// These two are only temporarily accessable for testing purposes
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

		SceneManager*		m_SceneManager;
	};
}

#endif // __RENDERSYSTEM_H__