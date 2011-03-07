#include "PlayerDef.h"

PlayerDef::PlayerDef(const char* path) :
	maxSpeed(0.0f),
	baseAcceleration(0.0f),
	rotationSpeed(0.0f)
{
	if (!LoadFromFile(path))
	{
		Log("[PlayerDef] Error loading Player info from %s.", path);
	}
}

PlayerDef::~PlayerDef(void)
{
}

const char* PlayerDef::GetSpritePath(void) const
{
	return this->spritePath.c_str();
}

const double PlayerDef::GetMaxSpeed(void) const
{
	return this->maxSpeed;
}

const double PlayerDef::GetBaseAcceleration(void) const
{
	return this->baseAcceleration;
}

const double PlayerDef::GetRotationSpeed(void) const
{
	return this->rotationSpeed;
}

bool PlayerDef::LoadFromFile(const char* path)
{
	TiXmlDocument doc(path);
	if (!doc.LoadFile(TIXML_ENCODING_UTF8))
		return false;

	TiXmlHandle hDoc(&doc);
	TiXmlElement* elem;
	TiXmlHandle hRoot(0);

	TiXmlElement* spritePathElem;
	TiXmlElement* maxSpeedElem;
	TiXmlElement* baseAccelerationElem;
	TiXmlElement* rotationSpeedElem;

	// root
	elem = hDoc.FirstChildElement().Element(); // /Player
	hRoot = TiXmlHandle(elem);
	
	spritePathElem = elem->FirstChildElement("Sprite");
	if (spritePathElem)
	{
		this->spritePath = spritePathElem->GetText();
	}
	else
	{
		ErrorMessage("Element \"Sprite\" does not exist in Player definition.");
	}

	maxSpeedElem = elem->FirstChildElement("MaxSpeed");
	if (maxSpeedElem)
	{
		this->maxSpeed = atof(maxSpeedElem->GetText());
	}
	else
	{
		ErrorMessage("Element \"MaxSpeed\" does not exist in Player definition.");
	}

	baseAccelerationElem = elem->FirstChildElement("BaseAcceleration");
	if (baseAccelerationElem)
	{
		this->baseAcceleration = atof(baseAccelerationElem->GetText());
	}
	else
	{
		ErrorMessage("Element \"BaseAcceleration\" does not exist in Player definition.");
	}

	rotationSpeedElem = elem->FirstChildElement("RotationSpeed");
	if (rotationSpeedElem)
	{
		this->rotationSpeed = atof(rotationSpeedElem->GetText());
	}
	else
	{
		ErrorMessage("Element \"RotationSpeed\" does not exist in Player definition.");
	}
	
	return true;
}
