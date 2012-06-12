/**
 * @file PlayerDef.cpp
 * @author Dan Albert <dan@gingerhq.net>
 * @date Last updated 06/11/2012
 * @version 0.2.53
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
 * An object representation of the data stored in a Player definition file.
 * 
 */
#include "PlayerDef.h"

PlayerDef::PlayerDef(const char* path) :
	maxSpeed(0.0f),
	baseAcceleration(0.0f),
	maxAngularSpeed(0.0f)
{
	if (!LoadFromFile(path))
	{
		Log("[PlayerDef] Error loading Player info from %s.", path);
	}
}

PlayerDef::~PlayerDef(void)
{
}

const char* PlayerDef::GetSpritePath(void) const
{
	return this->spritePath.c_str();
}

const double PlayerDef::GetMaxSpeed(void) const
{
	return this->maxSpeed;
}

const double PlayerDef::GetBaseAcceleration(void) const
{
	return this->baseAcceleration;
}

const double PlayerDef::GetMaxAngularSpeed(void) const
{
	return this->maxAngularSpeed;
}

bool PlayerDef::LoadFromFile(const char* path)
{
	TiXmlDocument doc(path);
	if (!doc.LoadFile(TIXML_ENCODING_UTF8))
		return false;

	TiXmlHandle hDoc(&doc);
	TiXmlElement* elem;
	TiXmlHandle hRoot(0);

	TiXmlElement* spritePathElem;
	TiXmlElement* maxSpeedElem;
	TiXmlElement* baseAccelerationElem;
	TiXmlElement* maxAngularSpeedElem;

	// root
	elem = hDoc.FirstChildElement().Element(); // /Player
	hRoot = TiXmlHandle(elem);
	
	spritePathElem = elem->FirstChildElement("Sprite");
	if (spritePathElem)
	{
		this->spritePath = spritePathElem->GetText();
	}
	else
	{
		ErrorMessage("Element \"Sprite\" does not exist in Player definition.");
	}

	maxSpeedElem = elem->FirstChildElement("MaxSpeed");
	if (maxSpeedElem)
	{
		this->maxSpeed = atof(maxSpeedElem->GetText());
	}
	else
	{
		ErrorMessage("Element \"MaxSpeed\" does not exist in Player definition.");
	}

	baseAccelerationElem = elem->FirstChildElement("BaseAcceleration");
	if (baseAccelerationElem)
	{
		this->baseAcceleration = atof(baseAccelerationElem->GetText());
	}
	else
	{
		ErrorMessage("Element \"BaseAcceleration\" does not exist in Player definition.");
	}

	maxAngularSpeedElem = elem->FirstChildElement("MaxAngularSpeed");
	if (maxAngularSpeedElem)
	{
		this->maxAngularSpeed = atof(maxAngularSpeedElem->GetText());
	}
	else
	{
		ErrorMessage("Element \"MaxAngularSpeed\" does not exist in Player definition.");
	}
	
	return true;
}
