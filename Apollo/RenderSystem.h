#ifndef __RENDERSYSTEM_H__
#define __RENDERSYSTEM_H__

#include "Apollo.h"

#include <d3d9.h>
#include <d3dx9.h>

#include "Debug.h"
#include "Window.h"

namespace Apollo
{
	class APOLLO_API RenderSystem
	{
	public:
		RenderSystem(
			const char* windowTitle = "Apollo 2D Rendering Engine",
			unsigned int width = 800,
			unsigned int height = 600,
			unsigned int bitDepth = 32,
			unsigned int refreshRate = 60,
			bool vsync = true,
			bool windowed = true);

		virtual ~RenderSystem(void);

		void Release(void);

		void StartDrawing(void);	// SceneManager should be linked into the render system
		void EndDrawing(void);		// so that drawing can be a single method

		// Accessors //
		inline Window*	GetWindow(void)	{	return m_Window;	}

		// These two are only temporarily accessable for testing purposes
		inline IDirect3DDevice9*	GetDevice(void)			const	{	return m_Device;		}
		inline ID3DXSprite*			GetSpriteHandler(void)	const	{	return m_SpriteHandler;	}

		//inline HWND					GetWindowHandle(void)	const	{	return m_Window;		}
		//inline IDirect3DSurface9*	GetBackbuffer(void)		const	{	return m_Backbuffer;	}
		//inline unsigned short		GetWidth(void)			const	{	return m_usWidth;		}
		//inline unsigned short		GetHeight(void)			const	{	return m_usHeight;		}
		
		// Modifiers //

	protected:
		Window*				m_Window;
		IDirect3D9*			m_Direct3D;
		IDirect3DDevice9*	m_Device;
		ID3DXSprite*		m_SpriteHandler;
		IDirect3DSurface9*	m_Backbuffer;
	};
}

#endif // __RENDERSYSTEM_H__