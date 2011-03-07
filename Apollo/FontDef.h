#ifndef FONTDEF_H
#define FONTDEF_H

#include "Apollo.h"

#include <string>
#include <tinyxml.h>

#include "CharacterDef.h"

namespace Apollo
{
	class APOLLO_API FontDef
	{
	public:
		FontDef(const char* path);
		~FontDef(void);

		const CharacterDef operator[] (int index) const;

		const char* GetResourcePath(void) const;

	private:
		std::string resourcePath;
		CharacterDef characters[256];
		bool loadFromFile(const char* path);
	};
}

#endif // FONTDEF_H