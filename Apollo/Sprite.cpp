#include "Sprite.h"

namespace Apollo
{
	/*Sprite::Sprite(const char* szPath, IDirect3DDevice9* lpDevice, ID3DXSprite* spriteHandler)
	{
		m_SpriteHandler = spriteHandler;

		m_Textures = NULL;

		m_nFrames = 1;

		if (!LoadFromFile(szPath, lpDevice))
		{
			Free();
			return;
		}
	}*/

	Sprite::Sprite(const char* szPath, RenderSystem* renderSystem)
	{
		m_SpriteHandler = renderSystem->GetSpriteHandler();

		m_Textures = NULL;

		SpriteDef def(szPath);
		m_nFrames = def.GetNFrames();
		m_animTime = def.GetFrameTime();
		m_cFrame = 0;
		m_animCount = 0;

		if (!Load(&def, renderSystem->GetDevice()))
		{
			Free();
			return;
		}
	}

	Sprite::Sprite(const Sprite& s)
	{
		m_SpriteHandler = s.m_SpriteHandler;
		m_Textures = s.m_Textures;
		m_nFrames = s.m_nFrames;
		m_animTime = s.m_animTime;
		m_cFrame = 0;
		m_animCount = 0;		
	}

	Sprite::~Sprite(void)
	{
		Free();
	}


	Sprite& Sprite::operator =(const Sprite& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		Free();

		m_SpriteHandler = rhs.m_SpriteHandler;
		m_Textures = rhs.m_Textures;
		m_nFrames = rhs.m_nFrames;
		m_animTime = rhs.m_animTime;
		m_cFrame = rhs.m_cFrame;
		m_animCount = rhs.m_animCount;

		return *this;
	}

	bool Sprite::LoadFromFile(const char* szPath, IDirect3DTexture9*& texture, IDirect3DDevice9* lpDevice)
	{
		HRESULT hr;
		D3DXIMAGE_INFO info;
		unsigned int width;
		unsigned int height;

		hr = D3DXGetImageInfoFromFile(szPath, &info);
		if (hr != D3D_OK)
		{
			Log("[Sprite] Error loading image info from %s.", szPath);
			return false;
		}

		width = info.Width;
		height = info.Height;

		hr = D3DXCreateTextureFromFileEx(lpDevice,
			szPath,
			width,
			height,
			1,
			D3DPOOL_DEFAULT,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(0xff, 0x00, 0xff),
			&info,
			NULL,
			&texture);
		if (hr != D3D_OK)
		{
			Log("[Sprite] Error loading sprite from %s.", szPath);
			return false;
		}

		return true;
	}

	bool Sprite::Load(SpriteDef* animDef, IDirect3DDevice9* lpDevice)
	{
		Free();	// Free any existing resources

		m_Textures = new IDirect3DTexture9*[m_nFrames];
		memset(m_Textures, 0, m_nFrames * sizeof(IDirect3DTexture9*));

		for (int i = 0; i < m_nFrames; ++i)
		{
			LoadFromFile(animDef->GetFrame(i), m_Textures[i], lpDevice);
		}

		return true;
	}

	void Sprite::Free(void)
	{
		if (m_Textures)
		{
			for (int i = 0; i < m_nFrames; ++i)
			{
				if (m_Textures[i])
				{
					m_Textures[i]->Release();
				}
			}
			
			delete [] m_Textures;
			m_Textures = NULL;
		}
	}

	/*void Sprite::Draw(D3DXVECTOR3 position, int index)
	{
		m_SpriteHandler->Draw(m_Textures[index],
			NULL,
			NULL,
			&position,
			D3DCOLOR_XRGB(0xff, 0xff, 0xff));
	}

	void Sprite::Draw(float x, float y, int index)
	{
		D3DXVECTOR3 position(x, y, 0.0f);
		Draw(position, index);
	}*/

	void Sprite::Draw(D3DXVECTOR3 position, long dTime)
	{
		m_animCount += dTime;

		if (m_animCount > m_animTime)
		{
			++m_cFrame;
			
			if (m_cFrame >= m_nFrames)
			{
				m_cFrame = 0;
			}

			m_animCount = 0;
		}

		m_SpriteHandler->Draw(m_Textures[m_cFrame],
			NULL,
			NULL,
			&position,
			D3DCOLOR_XRGB(0xff, 0xff, 0xff));
	}

	void Sprite::Draw(float x, float y, long dTime)
	{
		D3DXVECTOR3 position(x, y, 0.0f);
		Draw(position, dTime);
	}
}
