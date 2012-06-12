/**
 * @file SceneManager.h
 * @author Dan Albert <dan@gingerhq.net>
 * @date Last updated 06/11/2012
 * @version 0.2.53
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
 * Manages all of the objects in the scene.
 * 
 * Manages all Scene Objects allocated to this manager, and handles the
 * viewport for the scene. Responsible for saving and loading the scene as well
 * as updating and drawing objects when appropriate.
 * 
 */
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Apollo.h"

#include <tinyxml.h>
#include <vector>

#include "SceneObject.h"
#include "SpriteObject.h"
#include "TextureAllocator.h"
#include "Viewport.h"

// should be created by the render system
// should handle loading and management of all sprites
// should handle creation and drawing of all objects

namespace Apollo
{
	class APOLLO_API SceneManager
	{
	public:
		SceneManager(RenderSystem* renderSystem);
		virtual ~SceneManager(void);

		void	Release(void);

		virtual bool SaveState(const char* szPath);
		virtual bool LoadState(const char* szPath);

		SpriteObject*	CreateSpriteObject(const char* szPath);
		void			FreeGameObject(SceneObject* sprite);

		void	Update(void);
		void	Draw(void);

		inline Viewport*			GetViewport(void)	const	{	return m_Viewport;			}

	protected:
		RenderSystem*				m_RenderSystem;
		Viewport*					m_Viewport;
		std::vector<SceneObject*>	m_GameAssets;

		long m_lastUpdateTime;
		long m_lastDrawTime;

		virtual bool loadChildObjects(TiXmlElement* element, SceneObject* parent = NULL);
		virtual bool loadObject(TiXmlElement* element, SceneObject* parent = NULL);
		virtual bool loadSpriteObjectState(TiXmlElement* element, SceneObject* parent = NULL);
		virtual bool loadViewportState(TiXmlElement* element, SceneObject* parent = NULL);	// Needs to be able to be a child of an object
	};
}

#endif // SCENEMANAGER_H
