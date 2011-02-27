#include "RenderSystem.h"

#include "Texture.h"
#include "TextureAllocator.h"

namespace Apollo
{
	RenderSystem::RenderSystem(void)
	{
	}

	RenderSystem::~RenderSystem(void)
	{
		Release();
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