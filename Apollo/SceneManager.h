#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Apollo.h"

#include <tinyxml.h>
#include <vector>

#include "GameObject.h"
#include "SpriteObject.h"
#include "Viewport.h"

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

		virtual bool SaveState(const char* szPath);
		virtual bool LoadState(const char* szPath);

		SpriteObject*	CreateSpriteObject(const char* szPath);
		void			FreeSpriteObject(SpriteObject* sprite);

		void	Update(void);
		void	Draw(void);

		inline Viewport*	GetViewport(void)	const	{	return m_Viewport;	}

	protected:
		RenderSystem*				m_RenderSystem;
		Viewport*					m_Viewport;
		std::vector<GameObject*>	m_GameAssets;

		long m_lastUpdateTime;
		long m_lastDrawTime;

		virtual bool loadChildObjects(TiXmlElement* element, GameObject* parent = NULL);
		virtual bool loadSpriteObjectState(TiXmlElement* element, GameObject* parent = NULL);
		virtual bool loadViewportState(TiXmlElement* element);	// Needs to be able to be a child of an object
	};
}

#endif // __SCENEMANAGER_H__
