#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Apollo.h"

#include <d3d9.h>
#include <d3dx9.h>

#include <vector>

#include "SpriteDef.h"
#include "Debug.h"
#include "RenderSystem.h"
#include "Texture.h"
#include "TextureAllocator.h"

namespace Apollo
{
	extern class SceneManager;

	class APOLLO_API Sprite
	{
	public:
		Sprite(const char* szPath, RenderSystem* renderSystem);
		Sprite(const Sprite& s);	// Do not use until asset management is in place
		virtual ~Sprite(void);

		Sprite& operator= (const Sprite& rhs);	// Do not use until asset management is in place

		virtual bool Load(SpriteDef* animDef, RenderSystem* renderSystem);
		virtual void Release(void);

		virtual void Draw(float x, float y, long deltaTime);
		virtual void Draw(float x, float y, float rotation, long deltaTime);

		inline char*		GetResourcePath(void)		const	{	return m_ResourcePath;	}
		inline int			GetCurrentFrame(void)		const	{	return m_cFrame;		}
		inline int			GetCurrentFrameTime(void)	const	{	return m_animCount;		}
		inline unsigned int	GetMaxWidth(void)			const	{	return m_maxWidth;		}
		inline unsigned int	GetMaxHeight(void)			const	{	return m_maxHeight;		}

	protected:
		Texture**		m_Textures;

		char*			m_ResourcePath;	// Will not update if a new image is loaded
										// Should be resolved with changes due to the
										// asset management system

		int				m_nFrames;		// Total number of frames in animation.
		int				m_cFrame;		// Current frame of animation.
		int				m_animTime;		// How many ticks each frame will be active.
		int				m_animCount;	// How many ticks the current frame has been active.
		unsigned int	m_maxWidth;
		unsigned int	m_maxHeight;

		virtual void updateAnimation(long deltaTime);
	};
}

#endif // __SPRITE_H__