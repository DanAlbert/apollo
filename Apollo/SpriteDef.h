#ifndef __ANIMDEF_H__
#define __ANIMDEF_H__

#include "Apollo.h"

#include <tinyxml.h>

namespace Apollo
{
	class APOLLO_API SpriteDef
	{
	public:
		SpriteDef(const char* szPath);
		~SpriteDef(void);

		inline const char*	GetFrame(int i) const;
		inline const int	GetNFrames(void) const;
		inline const int	GetFrameTime(void) const;

		bool LoadFromFile(const char* szPath);
		void Release(void);

	protected:
		char**	m_Frames;
		int		m_nFrames;
		int		m_frameTime;
	};
}

#endif // __ANIMDEF_H__
