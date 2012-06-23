/**
 * @file PlayerListener.cpp
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
 * A custom input listener that maps cursor keys to player movement.
 * 
 */
#include "PlayerListener.h"

PlayerListener::PlayerListener(Apollo::Window* window) :
	InputListener(window),
	playerMoveForward(false),
	playerMoveBackward(false),
	playerRotateLeft(false),
	playerRotateRight(false),
	playerShoot(false)
{
}

PlayerListener::~PlayerListener(void) throw()
{
}

bool PlayerListener::keyPressed(const OIS::KeyEvent& e)
{
	switch (e.key)
	{
	case OIS::KeyCode::KC_UP:
		this->playerMoveForward = true;
		break;
	case OIS::KeyCode::KC_DOWN:
		this->playerMoveBackward = true;
		break;
	case OIS::KeyCode::KC_LEFT:
		this->playerRotateLeft = true;
		break;
	case OIS::KeyCode::KC_RIGHT:
		this->playerRotateRight = true;
		break;
	case OIS::KeyCode::KC_SPACE:
		this->playerShoot = true;
		break;
	default:
		break;
	}

	return true;
}

bool PlayerListener::keyReleased(const OIS::KeyEvent& e)
{
	switch (e.key)
	{
	case OIS::KeyCode::KC_UP:
		this->playerMoveForward = false;
		break;
	case::OIS::KeyCode::KC_DOWN:
		this->playerMoveBackward = false;
		break;
	case OIS::KeyCode::KC_LEFT:
		this->playerRotateLeft = false;
		break;
	case OIS::KeyCode::KC_RIGHT:
		this->playerRotateRight = false;
		break;
	case OIS::KeyCode::KC_SPACE:
		this->playerShoot = false;
		break;
	default:
		break;
	}

	return true;
}
