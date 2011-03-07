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
		unsigned int height) :
			value(value),
			x(x),
			y(y),
			width(width),
			height(height)
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
}
