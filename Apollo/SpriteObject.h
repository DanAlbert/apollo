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

		void Release(void);

		void Update(long dTime);
		void Draw(long dTime);

	protected:
		Sprite* m_Sprite;
	};
}

#endif // __SPRITEOBJECT_H__