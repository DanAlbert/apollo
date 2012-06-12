/**
 * @file FontDef.h
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
