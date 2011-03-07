#ifndef FONT_H
#define FONT_H

#include "Apollo.h"
#include "FontDef.h"
#include "RenderSystem.h"

namespace Apollo
{
	class APOLLO_API Font
	{
	public:
		Font(const char* path, RenderSystem* renderSystem);
		~Font(void);

		unsigned int TextWidth(const char* text) const;

		void DrawText(const char* text, float x, float y) const;

	private:
		Texture* texture;
		FontDef fontDef;

		void loadResource(RenderSystem* renderSystem);
		void drawCharacter(char character, float x, float y) const;
	};
}

#endif // FONT_H
