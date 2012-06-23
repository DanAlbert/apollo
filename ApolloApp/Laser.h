/**
 * @file Laser.h
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
 * Defines a laser object.
 * 
 */
#ifndef LASER_H
#define LASER_H

#include "GameObject.h"

class Laser : public GameObject
{
public:
	Laser(
		Apollo::RenderSystem* renderSystem,
		Apollo::Viewport* viewport);

	virtual ~Laser(void);

	bool InCollisionGroup(const char* group) const throw();

	void SaveState(TiXmlElement*& element, bool elementIsParent = true);
	void LoadState(TiXmlElement* element, Apollo::SceneObject* parent = NULL);
	
	void Update(long dTime);

	bool HandleCollision(const GameObject& other) throw();

private:
	static const char ENTITY_PATH[];
	static const double MAX_SPEED;
};

#endif // LASER_H
