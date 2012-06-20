/**
 * @file SceneObject.h
 * @author Dan Albert <dan@gingerhq.net>
 * @date Last updated 06/19/2012
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
 * An object that exists in the scene.
 * 
 * Scene Objects have a position, a size and a rotation. They also exists in a
 * heirarchy. Each object may have any number of child objects, and one or zero
 * parent objects. Objects may be inactive, which disables their Update() step,
 * or invisible, which diasbles their Draw() step.
 * 
 */
#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "Apollo.h"

#include <tinyxml.h>
#include <vector>

#include "Debug.h"

namespace Apollo
{
	class APOLLO_API SceneObject
	{
	public:
		SceneObject(void);
		virtual ~SceneObject(void);

		SceneObject& operator= (const SceneObject& rhs);

		virtual void	Release(bool releaseChildren = true);

		// This should be made private, calling classes made friend
		virtual void	SaveState(TiXmlElement*& element, bool elementIsParent = true) = 0;
		virtual void	LoadState(TiXmlElement* element, SceneObject* parent = NULL);

		virtual void	Update(long dTime)					= 0;
		virtual void	Draw(long dTime, SceneObject* view)	= 0;

		// Accessors //
		inline bool			GetActive(void)		const	{	return m_Active;	}
		inline bool			GetVivible(void)	const	{	return m_Visible;	}
		inline float		GetXPosition(void)	const	{	return m_XPosition;	}
		inline float		GetYPosition(void)	const	{	return m_YPosition;	}
		inline float		GetRotation(void)	const	{	return m_Rotation;	}
		inline unsigned int	GetWidth(void)		const	{	return m_Width;		}
		inline unsigned int	GetHeight(void)		const	{	return m_Height;	}
		inline SceneObject*	GetParent(void)		const	{	return m_Parent;	}

		float GetRelativeXPosition(void);
		float GetRelativeYPosition(void);

		// Modifiers //
		void SetActive(bool active);
		void SetVisible(bool visible);
		
		void SetPosition(float x, float y);
		void SetRelativePosition(float x, float y);
		void Move(float x, float y);

		void SetRotation(float rotation);
		void Rotate(float rotation);

		void SetParent(SceneObject* parent);
		void RemoveParent(void);

	protected:
		bool			m_Active;
		bool			m_Visible;
		float			m_XPosition;
		float			m_YPosition;
		float			m_Rotation;
		unsigned int	m_Width;
		unsigned int	m_Height;

		SceneObject*				m_Parent;
		std::vector<SceneObject*>	m_Children;

		void addChild(SceneObject* child);		// DO NOT CALL DIRECTLY
		void removeChild(SceneObject* child);	// ONLY TO BE CALLED BY SetParent() AND RemoveParent()
	};
}

#endif // SCENEOBJECT_H
