/**
 * @file EntityDef.h
 * @author Dan Albert <dan@gingerhq.net>
 *
 * @section LICENSE
 * 
 * Apollo 2D Rendering Engine
 * Copyright (C) 2011 Dan Albert
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
 * An object representation of the data stored in an entity definition file.
 * 
 */
#ifndef ENTITYDEF_H
#define ENTITYDEF_H

#include <string>
#include <tinyxml.h>

#include <Apollo/Debug.h>
#include <Apollo/IOError.h>

#include "Physics/Geometry.h"

class EntityDef
{
public:
	EntityDef(const char* path) throw(Apollo::IOError);
	~EntityDef(void) throw();

	inline const char* GetSpritePath(void) const throw()
	{
		return this->spritePath.c_str();
	}

	inline const VertexList& GetVertexList(void) const throw()
	{
		return this->vertexList;
	}

	void LoadFromFile(const char* path) throw(Apollo::IOError);

private:
	VertexList vertexList;
	std::string spritePath;

	void loadGeometry(const TiXmlElement* elem) throw(Apollo::IOError);
};

#endif // ENTITYDEF_H
