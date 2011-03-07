#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__

#include "Apollo.h"

#include "Debug.h"
#include "SceneObject.h"

namespace Apollo
{
	class APOLLO_API Viewport : public SceneObject
	{
	public:
		Viewport(unsigned int width, unsigned int height);
		virtual ~Viewport(void);

		virtual void SaveState(TiXmlElement*& parentElement);
		virtual void LoadState(TiXmlElement* element, SceneObject* parent = NULL);

		inline virtual void Update(long dTime)					{	return;	}	// Nothing to update
		inline virtual void Draw(long dTime, SceneObject* view)	{	return;	}	// Nothing to draw

		bool IsOnScreen(SceneObject* object);

		void Resize(unsigned int width, unsigned int height);
	};
}

#endif // __VIEWPORT_H__