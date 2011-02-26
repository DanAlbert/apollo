/**
 * @file Player.h
 * @author Dan Albert
 * @date Created 23/02/2011
 * @date Last updated 23/02/2011
 * @version 1.0
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
 * Defines a sprite object that responds to player input.
 * 
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <SpriteObject.h>
#include "PlayerListener.h"

#ifndef PI
#define PI 3.1415926353
#endif // PI

#define PLAYER_MOVE_SPEED		0.175f
#define PLAYER_ROTATION_SPEED	(PI / 90.0f) / 8.0f

class Player : public Apollo::SpriteObject
{
public:
	Player(
		const char* path,
		Apollo::RenderSystem* renderSystem,
		PlayerListener* playerListener);

	virtual ~Player(void);

	virtual void SaveState(TiXmlElement*& parentElement);

	virtual void Update(long dTime);

private:
	PlayerListener* playerListener;

	double moveSpeed;
	double rotationSpeed;
};

#endif // PLAYER_H
