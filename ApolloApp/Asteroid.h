/**
 * @file Asteroid.h
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
 * Defines an asteroid game object.
 * 
 */
#ifndef ASTEROID_H
#define ASTEROID_H

#include <Apollo/InvalidArgumentError.h>

#include "GameObject.h"

class Asteroid : public GameObject
{
public:
	enum Size
	{
		Small,
		Medium,
		Large,
		Invalid
	};
	
	Asteroid(
		const Size size,
		Apollo::RenderSystem* renderSystem,
		GameManager* gameManager) throw(Apollo::InvalidArgumentError);
	
	Asteroid(
		const Size size,
		Apollo::RenderSystem* renderSystem,
		GameManager* gameManager,
		double x,
		double y) throw(Apollo::InvalidArgumentError);
	
	Asteroid(
		const char* path,
		Apollo::RenderSystem* renderSystem,
		GameManager* gameManager) throw(Apollo::InvalidArgumentError);

	virtual ~Asteroid(void);

	bool InCollisionGroup(const char* group) const throw();

	void SaveState(TiXmlElement*& element, bool elementIsParent = true);
	void LoadState(TiXmlElement* element, Apollo::SceneObject* parent = NULL);
	
	void Update(long dTime);

	void HandleCollision(const GameObject& other) throw();

	static const Size stringToSize(const char* str) throw();

private:
	Size size;
	static const char* paths[Size::Invalid];
};

#endif // ASTEROID_H
