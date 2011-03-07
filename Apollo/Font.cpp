#include "Font.h"
#include "TextureAllocator.h"

namespace Apollo
{
	Font::Font(const char* path, RenderSystem* renderSystem) :
		fontDef(path)
	{
		loadResource(renderSystem);
	}

	Font::~Font(void)
	{
	}

	void Font::DrawText(const char* text, float x, float y) const
	{
		for (text; *text; text++)
		{
			this->drawCharacter(*text, x, y);
			x += fontDef[*text].GetWidth();
		}
	}

	void Font::loadResource(RenderSystem* renderSystem)
	{
		this->texture = renderSystem->LoadTexture(this->fontDef.GetResourcePath());
	}

	void Font::drawCharacter(char character, float x, float y) const
	{
		Rectangle rect(
			this->fontDef[character].GetX(),
			this->fontDef[character].GetY(),
			this->fontDef[character].GetWidth(),
			this->fontDef[character].GetHeight());

		texture->Draw(x, y, 0.0f, &rect);
	}
}
