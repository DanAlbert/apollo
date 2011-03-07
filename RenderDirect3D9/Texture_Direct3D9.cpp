#include "Texture_Direct3D9.h"

Texture_Direct3D9::Texture_Direct3D9(const char* path, RenderSystem_Direct3D9* renderSystem) :
	m_SpriteHandler(renderSystem->GetSpriteHandler()),
	m_Resource(NULL),
	m_ResourcePath(NULL)
{
	m_SpriteHandler = renderSystem->GetSpriteHandler();

	if (!loadFromFile(path, renderSystem->GetDevice()))
	{
		Release();
		return;
	}

	m_ResourcePath = (char*)malloc(sizeof(char) * (strlen(path) + 1));
	if (!m_ResourcePath)
	{
		Log("[Texture_Direct3D9] Error allocating memory for resource path (%s). Object may not be able to reload.", path);
	}

	memset(m_ResourcePath, 0, sizeof(char) * (strlen(path) + 1));
	memcpy(m_ResourcePath, path, sizeof(char) * strlen(path));
}

Texture_Direct3D9::~Texture_Direct3D9(void)
{
	Release();
}

bool Texture_Direct3D9::Release(void)
{
	if (m_Resource)
	{
		m_Resource->Release();
		m_Resource = NULL;
	}

	if (m_ResourcePath)
	{
		delete [] m_ResourcePath;
		m_ResourcePath = NULL;
	}

	return true;
}

void Texture_Direct3D9::Draw(float x, float y, float rotation)
{
	D3DXMATRIX transform;
	D3DXVECTOR3 position(x, y, 0.0f);
		
	D3DXVECTOR2 center(m_Width / 2.0f, m_Height / 2.0f);
	D3DXMatrixTransformation2D(&transform, NULL, 0.0, NULL, &center, rotation, &D3DXVECTOR2(position));
		
	m_SpriteHandler->SetTransform(&transform);
	m_SpriteHandler->Draw(m_Resource,
		NULL,
		NULL,
		NULL,
		D3DCOLOR_XRGB(0xff, 0xff, 0xff));
}

void Texture_Direct3D9::Draw(float x, float y, float rotation, Apollo::Rectangle* sourceRect)
{
	D3DXMATRIX transform;
	D3DXVECTOR3 position(x, y, 0.0f);
		
	D3DXVECTOR2 center(m_Width / 2.0f, m_Height / 2.0f);
	D3DXMatrixTransformation2D(&transform, NULL, 0.0, NULL, &center, rotation, &D3DXVECTOR2(position));
	
	RECT rect;
	rect.left = sourceRect->x;
	rect.right = sourceRect->x + sourceRect->width;
	rect.top = sourceRect->y;
	rect.bottom = sourceRect->y + sourceRect->height;

	m_SpriteHandler->SetTransform(&transform);
	m_SpriteHandler->Draw(m_Resource,
		&rect,
		NULL,
		NULL,
		D3DCOLOR_XRGB(0xff, 0xff, 0xff));
}

bool Texture_Direct3D9::loadFromFile(const char* path, IDirect3DDevice9* device)
{
	HRESULT hr;
	D3DXIMAGE_INFO info;

	hr = D3DXGetImageInfoFromFile(path, &info);
	if (hr != D3D_OK)
	{
		Log("[Texture_Direct3D9] Error loading image info from %s.", path);
		return false;
	}

	m_Width = info.Width;
	m_Height = info.Height;

	hr = D3DXCreateTextureFromFileEx(device,
		path,
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
		Log("[Texture_Direct3D9] Error loading texture from %s.", path);
		return false;
	}

	return true;
}
