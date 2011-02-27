#include "TextureAllocator.h"

namespace Apollo
{
	TextureAllocator::TextureAllocator(RenderSystem* renderSystem)
	{
		m_RenderSystem = renderSystem;
	}

	TextureAllocator::~TextureAllocator(void)
	{
		Release();
	}

	void TextureAllocator::Release(void)
	{
		stdext::hash_map<std::string, Texture*>::iterator it;
		for (it = m_Resources.begin(); it != m_Resources.end(); it = m_Resources.begin())
		{
			delete m_Resources[it->first];
			m_Resources.erase(it);
		}

		m_Resources.clear();
	}
}
