#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Apollo.h"

#include <tinyxml.h>
#include <vector>

#include "GameObject.h"
#include "SpriteObject.h"

// should be created by the render system
// should handle loading and management of all sprites
// should handle creation and drawing of all objects

namespace Apollo
{
	class APOLLO_API SceneManager
	{
	public:
		SceneManager(RenderSystem* renderSystem);
		virtual ~SceneManager(void);

		void	Release(void);

		virtual void SaveState(const char* szPath);
		virtual void LoadState(const char* szPath);

		SpriteObject*	CreateSpriteObject(const char* szPath);
		void			FreeSpriteObject(SpriteObject* sprite);

		void	Update(void);
		void	Draw(void);

	protected:
		RenderSystem*				m_RenderSystem;
		std::vector<GameObject*>	m_GameAssets;

		long m_lastUpdateTime;
		long m_lastDrawTime;
	};
}

#endif // __SCENEMANAGER_H__
