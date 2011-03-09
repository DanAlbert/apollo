#ifndef ASTEROID_H
#define ASTEROID_H

#include "GameObject.h"

class Asteroid : public GameObject
{
public:
	Asteroid(
		const char* path,
		Apollo::RenderSystem* renderSystem,
		Apollo::Viewport* viewport);

	virtual ~Asteroid(void);

	void SaveState(TiXmlElement*& element, bool elementIsParent = true);
	void LoadState(TiXmlElement* element, Apollo::SceneObject* parent = NULL);
	
	void Update(long dTime);
};

#endif // ASTEROID_H
