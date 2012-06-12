/**
 * @file Font.cpp
 * @author Dan Albert <dan@gingerhq.net>
 * @date Last updated 06/11/2012
 * @version 0.2.53
 *
 * @section LICENSE
 * 
 * Apollo 2D Rendering Engine
 * Copyright (C) 2012 Dan Albert
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * @section DESCRIPTION
 * 
 * A system used for drawing text to the screen.
 * 
 */
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
	
	unsigned int Font::TextWidth(const char* text) const
	{
		unsigned int width = 0;
		for (text; *text; text++)
		{
			width += fontDef[*text].GetXAdvance();
		}

		return width;
	}

	void Font::DrawText(const char* text, float x, float y, Color color) const
	{
		for (text; *text; text++)
		{
			this->drawCharacter(*text, x, y, color);
			x += fontDef[*text].GetXAdvance();
		}
	}

	void Font::loadResource(RenderSystem* renderSystem)
	{
		this->texture = renderSystem->LoadTexture(this->fontDef.GetResourcePath());
	}

	void Font::drawCharacter(char character, float x, float y, Color color) const
	{
		Rectangle rect(
			this->fontDef[character].GetX(),
			this->fontDef[character].GetY(),
			this->fontDef[character].GetWidth(),
			this->fontDef[character].GetHeight());

		int xOffset = this->fontDef[character].GetXOffset();
		int yOffset = this->fontDef[character].GetYOffset();

		texture->Draw(
			x + xOffset,
			y + yOffset,
			0.0f,
			&rect,
			color);
	}
}
