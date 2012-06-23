/**
 * @file PlayerDef.h
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
#ifndef PLAYERDEF_H
#define PLAYERDEF_H

#include <string>
#include <tinyxml.h>

#include <Apollo/Debug.h>
#include <Apollo/IOError.h>

class PlayerDef
{
public:
	PlayerDef(const char* path) throw(Apollo::IOError);
	~PlayerDef(void);

	const char*		GetEntityPath(void) const;
	const double	GetMaxSpeed(void) const;
	const double	GetBaseAcceleration(void) const;
	const double	GetMaxAngularSpeed(void) const;
	const long		GetShotInterval(void) const;

	void Release(void);

private:
	std::string entityPath;
	double maxSpeed;
	double baseAcceleration;
	double maxAngularSpeed;
	long shotInterval;
	
	void loadFromFile(const char* path) throw(Apollo::IOError);
};

#endif // PLAYERDEF_H
