#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Apollo.h"

// should be created by the render system
// should handle loading and management of all sprites
// should handle creation and drawing of all objects

namespace Apollo
{
	class APOLLO_API SceneManager
	{
	public:
		SceneManager(void);
		virtual ~SceneManager(void);
	};
}

#endif // __SCENEMANAGER_H__
