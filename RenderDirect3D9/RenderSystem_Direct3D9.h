#ifndef RENDERSYSTEM_DIRECT3D9_H
#define RENDERSYSTEM_DIRECT3D9_H

#include <d3d9.h>
#include <d3dx9.h>

#include <RenderSystem.h>
#include <Window.h>

// Class prototypes
//class Texture;
//class TextureAllocator;

class RenderSystem_Direct3D9 : public Apollo::RenderSystem
{
public:
	RenderSystem_Direct3D9(
		const char* configPath,
		const char* windowTitle = "Apollo 2D Rendering Engine");

	RenderSystem_Direct3D9(
		const char* windowTitle,
		unsigned int width,
		unsigned int height,
		unsigned int bitDepth,
		unsigned int refreshRate,
		unsigned int multiSamplingLevel,
		bool vsync,
		bool windowed);

	~RenderSystem_Direct3D9(void);

	bool Initialize(
		const char* windowTitle,
		unsigned int width,
		unsigned int height,
		unsigned int bitDepth,
		unsigned int refreshRate,
		unsigned int multiSamplingLevel,
		bool vsync,
		bool windowed);

	void Release(void);

	void StartDrawing(void);
	void EndDrawing(void);

	inline unsigned int	GetWidth(void) const
	{
		D3DSURFACE_DESC desc;
		m_Backbuffer->GetDesc(&desc);
		return desc.Width;
	}

	inline unsigned int	GetHeight(void) const
	{
		D3DSURFACE_DESC desc;
		m_Backbuffer->GetDesc(&desc);
		return desc.Height;
	}

	inline IDirect3DDevice9*	GetDevice(void)			const	{	return m_Device;		}
	inline ID3DXSprite*			GetSpriteHandler(void)	const	{	return m_SpriteHandler;	}
		
	// Modifiers //

private:
	IDirect3D9*			m_Direct3D;
	IDirect3DDevice9*	m_Device;
	ID3DXSprite*		m_SpriteHandler;
	IDirect3DSurface9*	m_Backbuffer;

	bool setupDisplayFormat(D3DPRESENT_PARAMETERS& pp, unsigned int bitDepth);
	bool setupRefreshRate(D3DPRESENT_PARAMETERS& pp, unsigned int refreshRate);
	bool setupAntiAliasing(D3DPRESENT_PARAMETERS& pp, unsigned int level);
};

#endif // RENDERSYSTEM_DIRECT3D9_H
