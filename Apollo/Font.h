/**
 * @file Font.h
 * @author Dan Albert <dan@gingerhq.net>
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
#ifndef FONT_H
#define FONT_H

#include "Apollo.h"
#include "Color.h"
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

		void DrawText(const char* text, float x, float y, Color color = Color::White) const;

	private:
		Texture* texture;
		FontDef fontDef;

		void loadResource(RenderSystem* renderSystem);
		void drawCharacter(char character, float x, float y, Color color = Color::White) const;
	};
}

#endif // FONT_H
