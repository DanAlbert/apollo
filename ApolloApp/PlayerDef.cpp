#include "PlayerDef.h"

PlayerDef::PlayerDef(const char* path) :
	moveSpeed(0),
	rotationSpeed(0)
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

const double PlayerDef::GetMoveSpeed(void) const
{
	return this->moveSpeed;
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
	this->moveSpeed = atof(elem->FirstChildElement("MoveSpeed")->GetText());
	this->rotationSpeed = atof(elem->FirstChildElement("RotationSpeed")->GetText());
	//elem->QueryDoubleAttribute("move-speed", &moveSpeed);
	//elem->QueryDoubleAttribute("rotation-speed", &rotationSpeed);
	
	return true;
}
