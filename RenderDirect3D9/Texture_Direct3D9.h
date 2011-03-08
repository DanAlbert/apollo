#ifndef TEXTURE_DIRECT3D9_H
#define TEXTURE_DIRECT3D9_H

#include <d3d9.h>
#include <d3dx9.h>

#include <Debug.h>
#include <Texture.h>

#include "RenderSystem_Direct3D9.h"

class Texture_Direct3D9 : public Apollo::Texture
{
public:
	Texture_Direct3D9(const char* path, RenderSystem_Direct3D9* renderSystem);
	Texture_Direct3D9(const Texture_Direct3D9& t);
	~Texture_Direct3D9(void);

	Apollo::Texture& operator= (const Apollo::Texture& rhs);

	bool Release(void);

	void Draw(
		float x,
		float y,
		float rotation,
		const Apollo::Color color = Apollo::Color::White);

	void Draw(
		float x,
		float y,
		float rotation,
		Apollo::Rectangle* sourceRect,
		const Apollo::Color color = Apollo::Color::White);

	inline unsigned int	GetWidth(void)	const	{	return m_Width;		}
	inline unsigned int	GetHeight(void)	const	{	return m_Height;	}

protected:
	ID3DXSprite*		m_SpriteHandler;
	IDirect3DTexture9*	m_Resource;

	char*				m_ResourcePath;

	unsigned int		m_Width;
	unsigned int		m_Height;

	bool loadFromFile(const char* path, IDirect3DDevice9* device);
};

#endif // TEXTURE_DIRECT3D9_H
