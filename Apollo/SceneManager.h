#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Apollo.h"

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

		SpriteObject*	CreateSpriteObject(const char* szPath);
		void			FreeSpriteObject(SpriteObject* sprite);

		void	Update(long dTime);
		void	Draw(long dTime);

	protected:
		RenderSystem*				m_RenderSystem;
		std::vector<GameObject*>	m_GameAssets;
	};
}

#endif // __SCENEMANAGER_H__
