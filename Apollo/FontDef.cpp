/**
 * @file FontDef.cpp
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
 * An object representation of the data stored in a Font definition file.
 * 
 */
#include "FontDef.h"

namespace Apollo
{
	FontDef::FontDef(const char* path)
	{
		this->loadFromFile(path);
	}

	FontDef::~FontDef(void)
	{
	}

	const CharacterDef FontDef::operator[] (int index) const
	{
		return this->characters[index];
	}

	const char* FontDef::GetResourcePath(void) const
	{
		return this->resourcePath.c_str();
	}

	bool FontDef::loadFromFile(const char* path)
	{
		TiXmlDocument doc(path);
		if (!doc.LoadFile(TIXML_ENCODING_UTF8))
			return false;

		TiXmlHandle hDoc(&doc);
		TiXmlElement* elem;
		TiXmlHandle hRoot(0);

		// root
		elem = hDoc.FirstChildElement().Element(); // /Font
		hRoot = TiXmlHandle(elem);
		
		this->resourcePath = elem->Attribute("file");

		for (elem = hRoot.FirstChild("Character").Element(); elem; elem = elem->NextSiblingElement())
		{
			char value;
			int x;
			int y;
			int width;
			int height;
			int xOffset;
			int yOffset;
			int xAdvance;

			value = (char)atoi(elem->GetText());
			elem->QueryIntAttribute("x", &x);
			elem->QueryIntAttribute("y", &y);
			elem->QueryIntAttribute("width", &width);
			elem->QueryIntAttribute("height", &height);
			elem->QueryIntAttribute("x-offset", &xOffset);
			elem->QueryIntAttribute("y-offset", &yOffset);
			elem->QueryIntAttribute("x-advance", &xAdvance);

			this->characters[value] = CharacterDef(
				value,
				x,
				y,
				width,
				height,
				xOffset,
				yOffset,
				xAdvance);
		}

		return true;
	}
}
