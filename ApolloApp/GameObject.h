/**
 * @file GameObject.h
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
 * Defines a sprite object with basic kinematic properties that wraps at screen
 * edges.
 * 
 */
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Apollo/Geometry.h>
#include <Apollo/SpriteObject.h>
#include <Apollo/Vector2.h>
#include <Apollo/Viewport.h>

class GameObject : public Apollo::SpriteObject
{
public:
	GameObject(
		const char* path,
		Apollo::RenderSystem* renderSystem,
		Apollo::Viewport* viewport);

	virtual ~GameObject(void);

	inline const Apollo::Geometry& GetGeometry(void) const throw()
	{
		Apollo::Transformation t;
		t.rotation = this->GetRotation();
		t.scale = Apollo::Scale(1.0f, 1.0f);
		t.translation = Apollo::Translation(this->GetXPosition(), this->GetYPosition());
		this->geometry->SetTransform(t);
		return *this->geometry;
	}

	virtual bool InCollisionGroup(const char* group) const throw();

	void SaveState(TiXmlElement*& element, bool elementIsParent = true);
	void LoadState(TiXmlElement* element, Apollo::SceneObject* parent = NULL);
	
	virtual void Update(long dTime);
	virtual void Draw(long dTime, Apollo::SceneObject* view);

	bool CollidesWith(const GameObject& other) const throw();
	virtual bool HandleCollision(const GameObject& other) throw();

protected:
	std::string resourcePath;
	Apollo::Viewport* viewport;

	Apollo::Geometry* geometry;
	
	Apollo::Vector2 velocity;
	double angularVelocity;

	GameObject(Apollo::RenderSystem* renderSystem, Apollo::Viewport* viewport);

	void loadFromFile(const char* path) throw(Apollo::IOError);

	void updatePosition(long dTime);
	void updateRotation(long dTime);
	
	void drawBoundingBox(void) const;
	void drawBorders(void) const;

	void wrapScreenEdges(void);
};

#endif // GAMEOBJECT_H
