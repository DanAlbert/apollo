#ifndef __ANIMDEF_H__
#define __ANIMDEF_H__

#include "Apollo.h"

namespace Apollo
{
	class APOLLO_API AnimDef
	{
	public:
		AnimDef(const char* szPath);
		~AnimDef(void);

		bool LoadFromFile(const char* szPath);
		void Free(void);

	protected:
		char**	m_Frames;
		int		m_nFrames;
		int		m_frameTime;
	};
}

#endif // __ANIMDEF_H__
