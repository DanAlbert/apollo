/**
 * @file GameManager.h
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
 * Defines a custom scene manager.
 *
 * Has facilities for saving and loading application specific game objects and
 * also handles the Player object.
 * 
 */
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <Apollo/SceneManager.h>

#include "Asteroid.h"
#include "Laser.h"
#include "Player.h"

class GameManager : public Apollo::SceneManager
{
public:
	GameManager(Apollo::RenderSystem* renderSystem);
	~GameManager(void);

	bool SaveState(const char* path);
	bool LoadState(const char* path);

	Player*	CreatePlayer(const char* path);
	Asteroid* CreateAsteroid(const char* path);
	Asteroid* CreateAsteroid(const Asteroid::Size size);
	Asteroid* CreateAsteroid(const Asteroid::Size size, double x, double y);
	Laser* CreateLaser();

	void Update(void);

private:
	PlayerListener* listener;

	bool loadChildObjects(TiXmlElement* element, Apollo::SceneObject* parent = NULL) override;
	bool loadPlayerState(TiXmlElement* element, Apollo::SceneObject* parent = NULL);
	bool loadAsteroidState(TiXmlElement* element, Apollo::SceneObject* parent = NULL);
	bool loadLaserState(TiXmlElement* element, Apollo::SceneObject* parent = NULL);

	void checkCollisions(void) throw();
};

#endif // GAMEMANAGER_H
