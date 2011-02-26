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
	const double	GetMoveSpeed(void) const;
	const double	GetRotationSpeed(void) const;

	bool LoadFromFile(const char* path);
	void Release(void);

private:
	std::string spritePath;
	double moveSpeed;
	double rotationSpeed;
};

#endif // PLAYERDEF_H