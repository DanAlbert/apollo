#ifndef PLAYERDEF_H
#define PLAYERDEF_H

#include <Debug.h>
#include <string>
#include <tinyxml.h>

class PlayerDef
{
public:
	PlayerDef(const char* path);
	~PlayerDef(void);

	const char*		GetSpritePath(void) const;
	const double	GetMaxSpeed(void) const;
	const double	GetBaseAcceleration(void) const;
	const double	GetRotationSpeed(void) const;

	bool LoadFromFile(const char* path);
	void Release(void);

private:
	std::string spritePath;
	double maxSpeed;
	double baseAcceleration;
	double rotationSpeed;
};

#endif // PLAYERDEF_H