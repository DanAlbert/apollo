/**
 * @file CharacterDef.cpp
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
 * An object representation of individual character data in a Font
 * definition file.
 * 
 */
#include "CharacterDef.h"

namespace Apollo
{
	CharacterDef::CharacterDef(void) :
			value(0),
			x(0),
			y(0),
			width(0),
			height(0)
	{
	}

	CharacterDef::CharacterDef(
		char value,
		unsigned int x,
		unsigned int y,
		unsigned int width,
		unsigned int height,
		int xOffset,
		int yOffset,
		int xAdvance) :
			value(value),
			x(x),
			y(y),
			width(width),
			height(height),
			xOffset(xOffset),
			yOffset(yOffset),
			xAdvance(xAdvance)
	{
	}

	CharacterDef::~CharacterDef(void)
	{
	}

	inline const char CharacterDef::GetValue(void) const
	{
		return this->value;
	}

	inline const unsigned int CharacterDef::GetX(void) const
	{
		return this->x;
	}

	inline const unsigned int CharacterDef::GetY(void) const
	{
		return this->y;
	}

	inline const unsigned int CharacterDef::GetWidth(void) const
	{
		return this->width;
	}

	inline const unsigned int CharacterDef::GetHeight(void) const
	{
		return this->height;
	}

	inline const int CharacterDef::GetXOffset(void) const
	{
		return this->xOffset;
	}

	inline const int CharacterDef::GetYOffset(void) const
	{
		return this->yOffset;
	}

	inline const int CharacterDef::GetXAdvance(void) const
	{
		return this->xAdvance;
	}
}
