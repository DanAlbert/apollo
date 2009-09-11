#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Apollo.h"

#include <d3d9.h>
#include <d3dx9.h>

#include "Debug.h"
#include "RenderSystem.h"

namespace Apollo
{
	class APOLLO_API Texture
	{
	public:
		Texture(const char* szPath, RenderSystem* renderSystem);
		Texture(const Texture& t);
		virtual ~Texture(void);

		Texture& operator= (const Texture& rhs);

		virtual bool Release(void);

		virtual bool LoadFromFile(const char* szPath, IDirect3DDevice9* lpDevice);

		virtual void Draw(float x, float y, float rotation);

		virtual inline unsigned int	GetWidth(void)	const	{	return m_Width;		}
		virtual inline unsigned int	GetHeight(void)	const	{	return m_Height;	}

	protected:
		ID3DXSprite*		m_SpriteHandler;
		IDirect3DTexture9*	m_Resource;

		char*				m_ResourcePath;

		unsigned int		m_Width;
		unsigned int		m_Height;
	};
}

#endif // __TEXTURE_H__
