#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Apollo.h"
#include "Color.h"
#include "Rectangle.h"
#include "RenderSystem.h"

namespace Apollo
{
	class APOLLO_API Texture
	{
	public:
		Texture(void);
		virtual ~Texture(void);

		virtual bool Release(void) = 0;

		virtual void Draw(
			float x,
			float y,
			float rotation,
			const Color color = Color::White) = 0;

		virtual void Draw(
			float x,
			float y,
			float rotation,
			Rectangle* sourceRect,
			const Color color = Color::White) = 0;

		virtual inline unsigned int	GetWidth(void)	const	{	return m_Width;		}
		virtual inline unsigned int	GetHeight(void)	const	{	return m_Height;	}

	protected:
		unsigned int		m_Width;
		unsigned int		m_Height;
	};
}

#endif // __TEXTURE_H__
