#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Apollo.h"

#include <d3d9.h>
#include <d3dx9.h>

#include <vector>

#include "AnimDef.h"
#include "Debug.h"

namespace Apollo
{
	class APOLLO_API Sprite
	{
	public:
		Sprite(const char* szPath, IDirect3DDevice9* lpDevice, ID3DXSprite* spriteHandler);
		Sprite(const Sprite& s);	// Do not use until asset management is in place
		virtual ~Sprite(void);

		Sprite& operator= (const Sprite& rhs);	// Do not use until asset management is in place

		virtual bool LoadFromFile(const char* szPath, IDirect3DDevice9* lpDevice);
		virtual void Free(void);

		virtual void Draw(D3DXVECTOR3 position, int index = 0);
		virtual void Draw(float x, float y, int index = 0);

	protected:
		ID3DXSprite*		m_SpriteHandler;
		IDirect3DTexture9**	m_Textures;

		int m_nFrames;		// Total number of frames in animation.
		int m_cFrame;		// Current frame of animation.
		int m_animTime;		// How many ticks each frame will be active.
		int m_animCount;	// How many ticks the current frame has been active.
	};
}

#endif // __SPRITE_H__