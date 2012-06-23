/**
 * @file EntityDef.cpp
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
#include "EntityDef.h"

EntityDef::EntityDef(const char* path) throw(Apollo::IOError) :
	vertexList()
{
	this->LoadFromFile(path);
}

EntityDef::~EntityDef(void) throw()
{
}

void EntityDef::LoadFromFile(const char* path) throw(Apollo::IOError)
{
	TiXmlDocument doc(path);
	if (!doc.LoadFile(TIXML_ENCODING_UTF8))
	{
		Log("[EntityDef] Error loading Entity info from %s.", path);
		throw Apollo::IOError(ERR_APOLLOAPP_ENTITYDEF_LOAD);
	}

	TiXmlHandle hDoc(&doc);
	TiXmlElement* elem;
	TiXmlHandle hRoot(0);
	
	TiXmlElement* spriteElem;
	TiXmlElement* geometryElem;

	// root
	elem = hDoc.FirstChildElement().Element(); // /Entity
	hRoot = TiXmlHandle(elem);
	
	spriteElem = elem->FirstChildElement("Sprite");
	if (spriteElem)
	{
		this->spritePath = spriteElem->GetText();
	}
	else
	{
		Log("Element \"Sprite\" does not exist in Entity definition.");
		throw Apollo::IOError(ERR_APOLLOAPP_ENTITYDEF_MISSINGELEM);
	}

	geometryElem = elem->FirstChildElement("Geometry");
	if (geometryElem)
	{
		this->loadGeometry(geometryElem);
	}
	else
	{
		Log("Element \"Geometry\" does not exist in Entity definition.");
		throw Apollo::IOError(ERR_APOLLOAPP_ENTITYDEF_MISSINGELEM);
	}
}

void EntityDef::loadGeometry(const TiXmlElement* elem) throw(Apollo::IOError)
{
	for (elem = elem->FirstChildElement("Vertex"); elem; elem = elem->NextSiblingElement())
	{
		double x;
		double y;

		if (elem->QueryDoubleAttribute("x", &x) != TIXML_SUCCESS)
		{
			throw Apollo::IOError(ERR_APOLLOAPP_ENTITYDEF_MISSINGATTR);
		}
		
		if (elem->QueryDoubleAttribute("y", &y) != TIXML_SUCCESS)
		{
			throw Apollo::IOError(ERR_APOLLOAPP_ENTITYDEF_MISSINGATTR);
		}

		this->vertexList.push_back(Vertex(x, y));
	}
}
