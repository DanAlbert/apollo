#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "Apollo.h"

#include "Configuration.h"
#include "Debug.h"
#include "Window.h"

namespace Apollo
{
	// Class prototypes
	class Texture;
	class TextureAllocator;

	class APOLLO_API RenderSystem
	{
	public:
		RenderSystem(void);
		virtual ~RenderSystem(void);

		static RenderSystem* Create(const char* path);

		virtual bool Initialize(
			const char* windowTitle,
			unsigned int width,
			unsigned int height,
			unsigned int bitDepth,
			unsigned int refreshRate,
			unsigned int multiSamplingLevel,
			bool vsync,
			bool windowed) = 0;

		void Release(void);

		Texture* LoadTexture(const char* path) const;

		virtual void StartDrawing(void) = 0;
		virtual void EndDrawing(void) = 0;

		// Accessors //
		inline Window*	GetWindow(void)	{	return m_Window;	}
		virtual unsigned int	GetWidth(void) const = 0;
		virtual unsigned int	GetHeight(void) const = 0;
		
		// Modifiers //

	protected:
		Window*				m_Window;
		TextureAllocator*	m_TextureAllocator;
	};
}

#endif // RENDERSYSTEM_H