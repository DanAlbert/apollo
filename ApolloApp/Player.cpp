/**
 * @file Player.cpp
 * @author Dan Albert <dan@gingerhq.net>
 * @date Last updated 06/19/2012
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
#include "Player.h"

#include "GameManager.h"

Player::Player(
	const char* path,
	Apollo::RenderSystem* renderSystem,
	PlayerListener* playerListener,
	GameManager* gameManager) throw(Apollo::IOError):
		playerListener(playerListener),
		GameObject(renderSystem, gameManager->GetViewport()),
		gameManager(gameManager),
		lastShot(0)
{
	this->loadFromFile(path, renderSystem);
}

Player::~Player(void)
{
}

void Player::SaveState(TiXmlElement*& element, bool elementIsParent)
{
	TiXmlElement* elem;

	if (elementIsParent)
	{
		elem = new TiXmlElement("Player");
		element->LinkEndChild(elem);
	}
	else
	{
		elem = element;
	}
	
	if (!this->resourcePath.empty() && (elem->Attribute("resource") == NULL))
	{
		elem->SetAttribute("resource", this->resourcePath.c_str());
	}

	GameObject::SaveState(elem, false);
}


void Player::LoadState(TiXmlElement* element, Apollo::SceneObject* parent)
{
	GameObject::LoadState(element, parent);
}

void Player::Update(long dTime)
{
	if (this->m_Active)
	{
		this->updateAngularVelocity(dTime);
		this->updateVelocity(dTime);
		this->updateAttack(dTime);
	}
	
	GameObject::Update(dTime);
}

void Player::loadFromFile(const char* path, Apollo::RenderSystem* renderSystem) throw(Apollo::IOError)
{
	PlayerDef def(path);

	this->resourcePath = path;

	this->maxSpeed = def.GetMaxSpeed();
	this->baseAcceleration = def.GetBaseAcceleration();
	this->maxAngularSpeed = def.GetMaxAngularSpeed();
	this->shotInterval = def.GetShotInterval();

	GameObject::loadFromFile(def.GetEntityPath());
}

void Player::updateVelocity(long dTime)
{
	if (this->playerListener->GetPlayerMoveForward() && !this->playerListener->GetPlayerMoveBackward())
	{
		float x = sin(this->m_Rotation);
		float y = -cos(this->m_Rotation);

		this->velocity += Apollo::Vector2(
			this->baseAcceleration * dTime * x,
			this->baseAcceleration * dTime * y);
	}

	else if (this->playerListener->GetPlayerMoveBackward() && !this->playerListener->GetPlayerMoveForward())
	{
		float x = -sin(this->m_Rotation);
		float y = cos(this->m_Rotation);

		this->velocity += Apollo::Vector2(
			this->baseAcceleration * dTime * x,
			this->baseAcceleration * dTime * y);
	}
	
	if (abs(this->velocity.GetMagnitude()) > this->maxSpeed)
	{
		this->velocity *= (this->maxSpeed / this->velocity.GetMagnitude());
	}
}

void Player::updateAngularVelocity(long dTime)
{
	if (this->playerListener->GetPlayerRotateLeft() && !this->playerListener->GetPlayerRotateRight())
	{
		this->angularVelocity = -this->maxAngularSpeed;
	}

	else if (this->playerListener->GetPlayerRotateRight() && !this->playerListener->GetPlayerRotateLeft())
	{
		this->angularVelocity = this->maxAngularSpeed;
	}

	else
	{
		this->angularVelocity = 0.0f;
	}
}

void Player::updateAttack(long dTime)
{
	this->lastShot += dTime;
	
	if (this->playerListener->GetPlayerShoot() && (this->lastShot > this->shotInterval))
	{
		this->lastShot = 0;
		Laser* laser = this->gameManager->CreateLaser();
		laser->SetPosition(this->GetRelativeXPosition(), this->GetRelativeYPosition());
		laser->SetRotation(this->GetRotation());
	}
}
