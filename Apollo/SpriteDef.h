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

		inline const char*	GetFrame(int i)		{	return m_Frames[i];	}
		inline int			GetNFrames(void)	{	return m_nFrames;	}
		inline int			GetFrameTime(void)	{	return m_frameTime;	}

		bool LoadFromFile(const char* szPath);
		void Free(void);

	protected:
		char**	m_Frames;
		int		m_nFrames;
		int		m_frameTime;
	};
}

#endif // __ANIMDEF_H__
