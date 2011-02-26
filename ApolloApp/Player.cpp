#include "Player.h"

Player::Player(
	const char* path,
	Apollo::RenderSystem* renderSystem,
	PlayerListener* playerListener) :
		playerListener(playerListener)
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
		if (this->playerListener->GetPlayerMoveForward() && !this->playerListener->GetPlayerMoveBackward())
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
		}

		if (this->playerListener->GetPlayerRotateLeft() && !this->playerListener->GetPlayerRotateRight())
		{
			this->Rotate(-this->rotationSpeed * dTime);
		}

		else if (this->playerListener->GetPlayerRotateRight() && !this->playerListener->GetPlayerRotateLeft())
		{
			this->Rotate(this->rotationSpeed * dTime);
		}
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
