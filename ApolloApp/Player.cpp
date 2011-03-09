#include "Player.h"

Player::Player(
	const char* path,
	Apollo::RenderSystem* renderSystem,
	PlayerListener* playerListener,
	Apollo::Viewport* viewport) :
		playerListener(playerListener),
		GameObject(viewport)
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
	
	elem->SetAttribute("resource", this->resourcePath.c_str());

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
	}
	
	GameObject::Update(dTime);
}

void Player::loadFromFile(const char* path, Apollo::RenderSystem* renderSystem)
{
	PlayerDef def(path);

	this->resourcePath = path;

	this->maxSpeed = def.GetMaxSpeed();
	this->baseAcceleration = def.GetBaseAcceleration();
	this->maxAngularSpeed = def.GetMaxAngularSpeed();
	SpriteObject::loadFromFile(def.GetSpritePath(), renderSystem);
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