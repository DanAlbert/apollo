/**
 * @file PlayerDef.cpp
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
 * An object representation of the data stored in a Player definition file.
 * 
 */
#include "PlayerDef.h"

PlayerDef::PlayerDef(const char* path) throw(Apollo::IOError):
	maxSpeed(0.0f),
	baseAcceleration(0.0f),
	maxAngularSpeed(0.0f)
{
	this->loadFromFile(path);
}

PlayerDef::~PlayerDef(void)
{
}

const char* PlayerDef::GetEntityPath(void) const
{
	return this->entityPath.c_str();
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

const long PlayerDef::GetShotInterval(void) const
{
	return this->shotInterval;
}

void PlayerDef::loadFromFile(const char* path)
{
	TiXmlDocument doc(path);
	if (!doc.LoadFile(TIXML_ENCODING_UTF8))
	{
		Log("[PlayerDef] Error loading Player info from %s.", path);
		throw Apollo::IOError(ERR_APOLLOAPP_PLAYERDEF_LOAD);
	}

	TiXmlHandle hDoc(&doc);
	TiXmlElement* elem;
	TiXmlHandle hRoot(0);

	TiXmlElement* entityElem;
	TiXmlElement* maxSpeedElem;
	TiXmlElement* baseAccelerationElem;
	TiXmlElement* maxAngularSpeedElem;

	// root
	elem = hDoc.FirstChildElement().Element(); // /Player
	hRoot = TiXmlHandle(elem);
	
	entityElem = elem->FirstChildElement("Entity");
	if (entityElem)
	{
		this->entityPath = entityElem->GetText();
	}
	else
	{
		Log("[PlayerDef] Element \"Entity\" does not exist in Player definition.");
		throw Apollo::IOError(ERR_APOLLOAPP_PLAYERDEF_MISSINGELEM);
	}

	maxSpeedElem = elem->FirstChildElement("MaxSpeed");
	if (maxSpeedElem)
	{
		this->maxSpeed = atof(maxSpeedElem->GetText());
	}
	else
	{
		Log("[PlayerDef] Element \"MaxSpeed\" does not exist in Player definition.");
		throw Apollo::IOError(ERR_APOLLOAPP_PLAYERDEF_MISSINGELEM);
	}

	baseAccelerationElem = elem->FirstChildElement("BaseAcceleration");
	if (baseAccelerationElem)
	{
		this->baseAcceleration = atof(baseAccelerationElem->GetText());
	}
	else
	{
		Log("[PlayerDef] Element \"BaseAcceleration\" does not exist in Player definition.");
		throw Apollo::IOError(ERR_APOLLOAPP_PLAYERDEF_MISSINGELEM);
	}

	maxAngularSpeedElem = elem->FirstChildElement("MaxAngularSpeed");
	if (maxAngularSpeedElem)
	{
		this->maxAngularSpeed = atof(maxAngularSpeedElem->GetText());
	}
	else
	{
		Log("[PlayerDef] Element \"MaxAngularSpeed\" does not exist in Player definition.");
		throw Apollo::IOError(ERR_APOLLOAPP_PLAYERDEF_MISSINGELEM);
	}

	maxAngularSpeedElem = elem->FirstChildElement("ShotInterval");
	if (maxAngularSpeedElem)
	{
		this->shotInterval = atol(maxAngularSpeedElem->GetText());
	}
	else
	{
		Log("[PlayerDef] Element \"ShotInterval\" does not exist in Player definition.");
		throw Apollo::IOError(ERR_APOLLOAPP_PLAYERDEF_MISSINGELEM);
	}
}
