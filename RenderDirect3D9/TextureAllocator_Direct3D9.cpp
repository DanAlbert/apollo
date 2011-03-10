#include "TextureAllocator_Direct3D9.h"

TextureAllocator_Direct3D9::TextureAllocator_Direct3D9(RenderSystem_Direct3D9* renderSystem) :
	TextureAllocator(renderSystem)
{
}

TextureAllocator_Direct3D9::~TextureAllocator_Direct3D9(void)
{
	Release();
}

Apollo::Texture* TextureAllocator_Direct3D9::GetResource(const char* szPath)
{
	if (m_Resources.find(szPath) == m_Resources.end())
	{
		m_Resources[szPath] = new Texture_Direct3D9(
			szPath,
			static_cast<RenderSystem_Direct3D9*>(m_RenderSystem));
	}
		
	return m_Resources[szPath];
}
