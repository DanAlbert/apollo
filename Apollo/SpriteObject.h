#ifndef __SPRITEOBJECT_H__
#define __SPRITEOBJECT_H__

#include "Apollo.h"

#include "Debug.h"
#include "GameObject.h"
#include "RenderSystem.h"
#include "Sprite.h"

namespace Apollo
{
	class APOLLO_API SpriteObject : public GameObject
	{
	public:
		SpriteObject(const char* szPath, RenderSystem* renderSystem);
		virtual ~SpriteObject(void);

		virtual void Release(void);

		virtual void SaveState(TiXmlElement*& parentElement);
		virtual void LoadState(TiXmlElement* element, GameObject* parent = NULL);

		virtual void Update(long dTime);
		virtual void Draw(long dTime, GameObject* view);

	protected:
		Sprite*		m_Sprite;

		virtual void setSpriteState(int cFrame, int cFrameTime = 0);
	};
}

#endif // __SPRITEOBJECT_H__