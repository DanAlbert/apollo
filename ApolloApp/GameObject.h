/**
 * @file GameObject.h
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
 * Defines a sprite object with basic kinematic properties that wraps at screen
 * edges.
 * 
 */
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SpriteObject.h>
#include <Vector2.h>
#include <Viewport.h>

class GameObject : public Apollo::SpriteObject
{
public:
	GameObject(
		const char* path,
		Apollo::RenderSystem* renderSystem,
		Apollo::Viewport* viewport);

	virtual ~GameObject(void);

	void SaveState(TiXmlElement*& element, bool elementIsParent = true);
	void LoadState(TiXmlElement* element, Apollo::SceneObject* parent = NULL);
	
	void Update(long dTime);

protected:
	Apollo::Viewport* viewport;
	
	Apollo::Vector2 velocity;
	double angularVelocity;

	GameObject(Apollo::Viewport* viewport);

	void updatePosition(long dTime);
	void updateRotation(long dTime);
	void wrapScreenEdges(void);
};

#endif // GAMEOBJECT_H
