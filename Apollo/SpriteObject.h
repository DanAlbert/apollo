#ifndef __SPRITEOBJECT_H__
#define __SPRITEOBJECT_H__

#include "Apollo.h"

#include "Debug.h"
#include "SceneObject.h"
#include "RenderSystem.h"
#include "Sprite.h"

namespace Apollo
{
	class APOLLO_API SpriteObject : public SceneObject
	{
	public:
		SpriteObject(const char* path, RenderSystem* renderSystem);
		virtual ~SpriteObject(void);

		virtual void Release(void);

		virtual void SaveState(TiXmlElement*& element, bool elementIsParent = true);
		virtual void LoadState(TiXmlElement* element, SceneObject* parent = NULL);

		virtual void Update(long dTime);
		virtual void Draw(long dTime, SceneObject* view);

	protected:
		Sprite*		m_Sprite;

		SpriteObject(void);

		virtual void loadFromFile(const char* path, RenderSystem* renderSystem);

		virtual void setSpriteState(int cFrame, int cFrameTime = 0);
	};
}

#endif // __SPRITEOBJECT_H__