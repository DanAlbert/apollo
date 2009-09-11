#include "Texture.h"

namespace Apollo
{
	Texture::Texture(const char* szPath, RenderSystem* renderSystem)
	{
		m_SpriteHandler = renderSystem->GetSpriteHandler();

		m_Resource = NULL;
		m_ResourcePath = NULL;

		m_Width = 0;
		m_Height = 0;

		if (!LoadFromFile(szPath, renderSystem->GetDevice()))
		{
			Release();
			return;
		}

		m_ResourcePath = (char*)malloc(sizeof(char) * (strlen(szPath) + 1));
		if (!m_ResourcePath)
		{
			Log("[Texture] Error allocating memory for resource path (%s). Object may not be able to reload.", szPath);
		}

		memset(m_ResourcePath, 0, sizeof(char) * (strlen(szPath) + 1));
		memcpy(m_ResourcePath, szPath, sizeof(char) * strlen(szPath));
	}

	Texture::Texture(const Texture& t)
	{
		m_SpriteHandler = t.m_SpriteHandler;
		m_Resource = t.m_Resource;

		m_Width = t.m_Width;
		m_Height = t.m_Height;

		m_ResourcePath = (char*)malloc(sizeof(char) * (strlen(t.m_ResourcePath) + 1));
		if (!m_ResourcePath)
		{
			Log("[Texture]Error allocating memory for resource path (%s). Object may not be able to reload.", t.m_ResourcePath);
		}

		memset(m_ResourcePath, 0, sizeof(char) * (strlen(t.m_ResourcePath) + 1));
		memcpy(m_ResourcePath, t.m_ResourcePath, sizeof(char) * strlen(t.m_ResourcePath));
	}

	Texture::~Texture(void)
	{
		Release();
	}

	Texture& Texture::operator= (const Texture& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		Release();

		m_SpriteHandler = rhs.m_SpriteHandler;
		m_Resource = rhs.m_Resource;
		m_Width = rhs.m_Width;
		m_Height = rhs.m_Height;

		m_ResourcePath = (char*)malloc(sizeof(char) * (strlen(rhs.m_ResourcePath) + 1));
		if (!m_ResourcePath)
		{
			Log("[Texture] Error allocating memory for resource path (%s). Object may not be able to reload.", rhs.m_ResourcePath);
		}

		memset(m_ResourcePath, 0, sizeof(char) * (strlen(rhs.m_ResourcePath) + 1));
		memcpy(m_ResourcePath, rhs.m_ResourcePath, sizeof(char) * strlen(rhs.m_ResourcePath));

		return *this;
	}

	bool Texture::Release(void)
	{
		if (m_Resource)
		{
			m_Resource->Release();
			m_Resource = NULL;
		}

		if (m_ResourcePath)
		{
			free(m_ResourcePath);
			m_ResourcePath = NULL;
		}

		return true;
	}

	bool Texture::LoadFromFile(const char* szPath, IDirect3DDevice9* lpDevice)
	{
		HRESULT hr;
		D3DXIMAGE_INFO info;

		hr = D3DXGetImageInfoFromFile(szPath, &info);
		if (hr != D3D_OK)
		{
			Log("[Texture] Error loading image info from %s.", szPath);
			return false;
		}

		m_Width = info.Width;
		m_Height = info.Height;

		hr = D3DXCreateTextureFromFileEx(lpDevice,
			szPath,
			m_Width,
			m_Height,
			1,
			D3DPOOL_DEFAULT,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(0xff, 0x00, 0xff),
			&info,
			NULL,
			&m_Resource);
		if (hr != D3D_OK)
		{
			Log("[Texture] Error loading texture from %s.", szPath);
			return false;
		}

		return true;
	}

	void Texture::Draw(float x, float y, float rotation)
	{
		D3DXMATRIX transform;
		D3DXVECTOR3 position(x, y, 0.0f);
		
		D3DXVECTOR2 center(m_Width / 2, m_Height / 2);
		D3DXMatrixTransformation2D(&transform, NULL, 0.0, NULL, &center, rotation, &D3DXVECTOR2(position));
		
		m_SpriteHandler->SetTransform(&transform);
		m_SpriteHandler->Draw(m_Resource,
			NULL,
			NULL,
			NULL,
			D3DCOLOR_XRGB(0xff, 0xff, 0xff));
	}
}
