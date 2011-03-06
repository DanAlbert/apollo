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

	// root
	elem = hDoc.FirstChildElement().Element(); // /Player
	hRoot = TiXmlHandle(elem);
	
	this->spritePath = elem->FirstChildElement("Sprite")->GetText();
	this->maxSpeed = atof(elem->FirstChildElement("MaxSpeed")->GetText());
	this->baseAcceleration = atof(elem->FirstChildElement("BaseAcceleration")->GetText());
	this->rotationSpeed = atof(elem->FirstChildElement("RotationSpeed")->GetText());
	//elem->QueryDoubleAttribute("move-speed", &moveSpeed);
	//elem->QueryDoubleAttribute("rotation-speed", &rotationSpeed);
	
	return true;
}
