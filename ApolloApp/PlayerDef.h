/**
 * @file PlayerDef.h
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
#ifndef PLAYERDEF_H
#define PLAYERDEF_H

#include <Debug.h>
#include <string>
#include <tinyxml.h>

class PlayerDef
{
public:
	PlayerDef(const char* path);
	~PlayerDef(void);

	const char*		GetSpritePath(void) const;
	const double	GetMaxSpeed(void) const;
	const double	GetBaseAcceleration(void) const;
	const double	GetMaxAngularSpeed(void) const;

	bool LoadFromFile(const char* path);
	void Release(void);

private:
	std::string spritePath;
	double maxSpeed;
	double baseAcceleration;
	double maxAngularSpeed;
};

#endif // PLAYERDEF_H
