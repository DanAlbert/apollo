#include "RenderSystem.h"

#include "Texture.h"
#include "TextureAllocator.h"

namespace Apollo
{
	typedef RenderSystem *(*CreateRenderSystem)(
		const char* configPath,
		const char* windowTitle);

	HMODULE library = 0;

	void freeLibrary(void)
	{
		FreeLibrary(library);
	}

	RenderSystem::RenderSystem(void)
	{
	}

	RenderSystem::~RenderSystem(void)
	{
		Release();
	}

	RenderSystem* RenderSystem::Create(const char* path)
	{
		library = LoadLibrary(path);
		if (library)
		{
			Log("Loaded %s.", path);
			atexit(freeLibrary);

			CreateRenderSystem ctor= (CreateRenderSystem)GetProcAddress(library, "CreateRenderSystem");
			if (!ctor)
			{
				ErrorQuit("Failed to load CreateRenderSystem().", ERR_APOLLO_RENDERSYSTEM_LOADPROC);
			}
		
			return ctor("apollo.ini", "Apollo 2D Rendering Engine");
		}
		else
		{
			ErrorQuit("Failed to load RenderSystem library.", ERR_APOLLO_RENDERSYSTEM_LOADLIB);
		}
		return NULL;
	}

	void RenderSystem::Release(void)
	{
		if (this->m_TextureAllocator)
		{
			delete this->m_TextureAllocator;
			this->m_TextureAllocator = NULL;
		}

		if (m_Window)
		{
			//m_Window->Release();
			delete this->m_Window;
			this->m_Window = NULL;
		}
	}

	Texture* RenderSystem::LoadTexture(const char* path) const
	{
		return this->m_TextureAllocator->GetResource(path);
	}
}