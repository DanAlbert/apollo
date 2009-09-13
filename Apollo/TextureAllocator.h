#ifndef __TEXTUREALLOCATOR_H__
#define __TEXTUREALLOCATOR_H__

#include "Apollo.h"

#include <d3d9.h>
#include <d3dx9.h>

#include <hash_map>

#include "Debug.h"
#include "RenderSystem.h"
#include "Texture.h"

namespace Apollo
{
	class APOLLO_API TextureAllocator
	{
	public:
		TextureAllocator(RenderSystem* renderSystem);
		virtual ~TextureAllocator(void);

		void Release(void);

		Texture* GetResource(const char* szPath);

	protected:
		stdext::hash_map<std::string, Texture*> m_Resources;
		
		RenderSystem* m_RenderSystem;
	};
}

#endif // __TEXTUREALLOCATOR_H__
