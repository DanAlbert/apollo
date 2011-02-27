#ifndef TEXTUREALLOCATOR_DIRECT3D9_H
#define TEXTUREALLOCATOR_DIRECT3D9_H

#include <d3d9.h>
#include <d3dx9.h>

#include <hash_map>

#include <Debug.h>
#include <TextureAllocator.h>

#include "RenderSystem_Direct3D9.h"
#include "Texture_Direct3D9.h"

class TextureAllocator_Direct3D9 : public Apollo::TextureAllocator
{
public:
	TextureAllocator_Direct3D9(RenderSystem_Direct3D9* renderSystem);
	~TextureAllocator_Direct3D9(void);

	Apollo::Texture* GetResource(const char* szPath);

protected:
	//stdext::hash_map<std::string, Apollo::Texture*> m_Resources;
};

#endif // TEXTUREALLOCATOR_DIRECT3D9_H
