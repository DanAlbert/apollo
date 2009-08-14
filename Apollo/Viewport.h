#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__

#include "Apollo.h"

#include "Debug.h"
#include "GameObject.h"

namespace Apollo
{
	// Viewport should be a derived class of game object so that objects
	// may be children of the Viewport so they appear to remain stationary
	// as the screen moves. Are there any parts of the Game Object that
	// the Viewport should not inherit? Draw? Update?
	class APOLLO_API Viewport : public GameObject
	{
	public:
		Viewport(unsigned int width, unsigned int height);
		virtual ~Viewport(void);

		virtual void SaveState(TiXmlElement*& parentElement);

		inline virtual void Update(long dTime)					{	return;	}	// Nothing to update
		inline virtual void Draw(long dTime, GameObject* view)	{	return;	}	// Nothing to draw

		bool IsOnScreen(GameObject* object);

		void Resize(unsigned int width, unsigned int height);
	};
}

#endif // __VIEWPORT_H__