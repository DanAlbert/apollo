#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SceneManager.h>

#include "Player.h"

class GameManager : public Apollo::SceneManager
{
public:
	GameManager(Apollo::RenderSystem* renderSystem);
	~GameManager(void);
		
	bool SaveState(const char* path);
	bool LoadState(const char* path);

	Player*	CreatePlayer(const char* path);

	void Update(void);

private:
	PlayerListener* listener;

	bool loadChildObjects(TiXmlElement* element, Apollo::GameObject* parent = NULL) override;
	bool loadPlayerState(TiXmlElement* element, Apollo::GameObject* parent = NULL);
};

#endif // GAMEMANAGER_H
