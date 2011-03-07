#ifndef CHARACTERDEF_H
#define CHARACTERDEF_H

#include "Apollo.h"

namespace Apollo
{
	class APOLLO_API CharacterDef
	{
	public:
		CharacterDef(void);
		CharacterDef(
			char value,
			unsigned int x,
			unsigned int y,
			unsigned int width,
			unsigned int height);
		~CharacterDef(void);

		inline const char GetValue(void) const;
		inline const unsigned int GetX(void) const;
		inline const unsigned int GetY(void) const;
		inline const unsigned int GetWidth(void) const;
		inline const unsigned int GetHeight(void) const;

	private:
		char value;
		unsigned int x;
		unsigned int y;
		unsigned int width;
		unsigned int height;
	};
}

#endif // CHARACTERDEF_H