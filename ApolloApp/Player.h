/**
 * @file Player.h
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
 * Defines a game object that responds to player input.
 * 
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <Vector2.h>
#include <Viewport.h>
#include "GameObject.h"
#include "PlayerDef.h"
#include "PlayerListener.h"

class Player : public GameObject
{
public:
	Player(
		const char* path,
		Apollo::RenderSystem* renderSystem,
		PlayerListener* playerListener,
		Apollo::Viewport* viewport);

	virtual ~Player(void);

	void SaveState(TiXmlElement*& element, bool elementIsParent = true);
	void LoadState(TiXmlElement* element, Apollo::SceneObject* parent = NULL);
	
	void Update(long dTime);

private:
	PlayerListener* playerListener;

	std::string resourcePath;

	double maxSpeed;
	double baseAcceleration;
	double maxAngularSpeed;

	void loadFromFile(const char* path, Apollo::RenderSystem* renderSystem);
	void updateAngularVelocity(long dTime);
	void updateVelocity(long dTime);
};

#endif // PLAYER_H
