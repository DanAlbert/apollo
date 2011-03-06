#include "Player.h"

Player::Player(
	const char* path,
	Apollo::RenderSystem* renderSystem,
	PlayerListener* playerListener,
	Apollo::Viewport* viewport) :
		playerListener(playerListener),
		viewport(viewport),
		velocity()
{
	this->loadFromFile(path, renderSystem);
}

Player::~Player(void)
{
}

void Player::SaveState(TiXmlElement*& parentElement)
{
	TiXmlElement* elem = new TiXmlElement("Player");
	parentElement->LinkEndChild(elem);

	elem->SetAttribute("resource", this->resourcePath.c_str());
	elem->SetAttribute("active", m_Active);
	elem->SetAttribute("visible", m_Visible);
	elem->SetDoubleAttribute("x", m_XPosition);
	elem->SetDoubleAttribute("y", m_YPosition);
	elem->SetDoubleAttribute("rotation", m_Rotation);

	TiXmlElement* spriteElem = new TiXmlElement("Sprite");
	elem->LinkEndChild(spriteElem);

	spriteElem->SetAttribute("resource", m_Sprite->GetResourcePath());
	spriteElem->SetAttribute("cFrame", m_Sprite->GetCurrentFrame());
	spriteElem->SetAttribute("animCount", m_Sprite->GetCurrentFrameTime());

	if (m_Children.size() > 0)
	{
		TiXmlElement* childElem = new TiXmlElement("Children");
		elem->LinkEndChild(childElem);

		for (int i = 0; i < m_Children.size(); ++i)
		{
			m_Children[i]->SaveState(childElem);
		}
	}
}

void Player::Update(long dTime)
{
	if (this->m_Active)
	{
		this->updateRotation(dTime);
		this->updateVelocity(dTime);
		this->updatePosition(dTime);
		this->wrapScreenEdges();
	}
}

void Player::loadFromFile(const char* path, Apollo::RenderSystem* renderSystem)
{
	PlayerDef def(path);

	this->resourcePath = path;

	this->moveSpeed = def.GetMoveSpeed();
	this->rotationSpeed = def.GetRotationSpeed();
	SpriteObject::loadFromFile(def.GetSpritePath(), renderSystem);
}

void Player::updatePosition(long dTime)
{
	this->Move(this->velocity.x * dTime, this->velocity.y * dTime);

	/*if (this->playerListener->GetPlayerMoveForward() && !this->playerListener->GetPlayerMoveBackward())
	{
		float x = 0.0f;
		float y = 0.0f;
		float angle = this->GetRotation();
				
		x = sin(angle);
		y = -cos(angle);
		this->Move(x * this->moveSpeed * dTime, y * this->moveSpeed * dTime);
	}

	else if (this->playerListener->GetPlayerMoveBackward() && !this->playerListener->GetPlayerMoveForward())
	{
		float x = 0.0f;
		float y = 0.0f;
		float angle = this->GetRotation();
				
		x = -sin(angle);
		y = cos(angle);
		this->Move(x * this->moveSpeed * dTime, y * this->moveSpeed * dTime);
	}*/
}

void Player::updateVelocity(long dTime)
{
	if (this->playerListener->GetPlayerMoveForward() && !this->playerListener->GetPlayerMoveBackward())
	{
		float x = 0.0f;
		float y = 0.0f;
		float angle = this->GetRotation();
				
		x = sin(angle);
		y = -cos(angle);

		this->velocity += Apollo::Vector2(0.001f * dTime * x, 0.001f * dTime * y);
	}

	else if (this->playerListener->GetPlayerMoveBackward() && !this->playerListener->GetPlayerMoveForward())
	{
		float x = 0.0f;
		float y = 0.0f;
		float angle = this->GetRotation();
				
		x = sin(angle);
		y = -cos(angle);

		this->velocity += Apollo::Vector2(0.001f * dTime * x, 0.001f * dTime * y);
	}
	
	if (abs(this->velocity.GetMagnitude()) > 0.175)
	{
		this->velocity *= (0.175f * this->velocity.GetMagnitude());
	}
}

void Player::updateRotation(long dTime)
{
	if (this->playerListener->GetPlayerRotateLeft() && !this->playerListener->GetPlayerRotateRight())
	{
		this->Rotate(-this->rotationSpeed * dTime);
	}

	else if (this->playerListener->GetPlayerRotateRight() && !this->playerListener->GetPlayerRotateLeft())
	{
		this->Rotate(this->rotationSpeed * dTime);
	}
}

void Player::wrapScreenEdges(void)
{
	if ((this->m_XPosition + this->m_Width) < this->viewport->GetXPosition())
	{
		this->m_XPosition = this->viewport->GetXPosition() + this->viewport->GetWidth();
	}
	else if (this->m_XPosition > (this->viewport->GetXPosition() + this->viewport->GetWidth()))
	{
		this->m_XPosition = this->viewport->GetXPosition() - this->m_Width;
	}

	if ((this->m_YPosition + this->m_Height) < this->viewport->GetYPosition())
	{
		this->m_YPosition = this->viewport->GetYPosition() + this->viewport->GetHeight();
	}
	else if (this->m_YPosition > (this->viewport->GetYPosition() + this->viewport->GetHeight()))
	{
		this->m_YPosition = this->viewport->GetYPosition() - this->m_Height;
	}
}