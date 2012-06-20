/**
 * @file CharacterDef.h
 * @author Dan Albert <dan@gingerhq.net>
 * @date Last updated 06/19/2012
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
 * An object representation of individual character data in a Font
 * definition file.
 * 
 */
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
			unsigned int height,
			int xOffset,
			int yOffset,
			int xAdvance);
		~CharacterDef(void);

		inline const char GetValue(void) const;
		inline const unsigned int GetX(void) const;
		inline const unsigned int GetY(void) const;
		inline const unsigned int GetWidth(void) const;
		inline const unsigned int GetHeight(void) const;
		inline const int GetXOffset(void) const;
		inline const int GetYOffset(void) const;
		inline const int GetXAdvance(void) const;

	private:
		char value;
		unsigned int x;
		unsigned int y;
		unsigned int width;
		unsigned int height;
		int xOffset;
		int yOffset;
		int xAdvance;
	};
}

#endif // CHARACTERDEF_H
