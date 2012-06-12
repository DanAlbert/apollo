/**
 * @file PlayerListener.h
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
 * A custom input listener that maps cursor keys to player movement.
 * 
 */
#ifndef PLAYERLISTENER_H
#define PLAYERLISTENER_H

#include <InputListener.h>

class PlayerListener : public Apollo::InputListener
{
public:
	PlayerListener(Apollo::Window* window);
	virtual ~PlayerListener(void);

	bool keyPressed(const OIS::KeyEvent& e);
	bool keyReleased(const OIS::KeyEvent& e);

	bool GetPlayerMoveForward(void)		const	{	return playerMoveForward;	}
	bool GetPlayerMoveBackward(void)	const	{	return playerMoveBackward;	}
	bool GetPlayerRotateLeft(void)		const	{	return playerRotateLeft;	}
	bool GetPlayerRotateRight(void)		const	{	return playerRotateRight;	}

protected:
	bool playerMoveForward;
	bool playerMoveBackward;
	bool playerRotateLeft;
	bool playerRotateRight;
};

#endif // PLAYERLISTENER_H
