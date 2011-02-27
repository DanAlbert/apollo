#ifndef __INPUTLISTENER_H__
#define __INPUTLISTENER_H__

#include "Apollo.h"

#include <OIS.h>

#include <string>
#include <sstream>

#include "Window.h"

namespace Apollo
{
	class APOLLO_API InputListener : public OIS::MouseListener, public OIS::KeyListener
	{
	public:
		InputListener(Window* window);
		virtual ~InputListener(void);

		bool Initialize(Window* window);
		
		void Release(void);

		bool Update(void);

		bool mouseMoved(const OIS::MouseEvent& e)							{	return true;	}
		bool mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)	{	return true;	}
		bool mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)	{	return true;	}

		bool keyPressed(const OIS::KeyEvent& e)			{	return true;	}
		bool keyReleased(const OIS::KeyEvent& e)		{	return true;	}

	protected:
		OIS::InputManager*	m_InputManager;
		OIS::Keyboard*		m_Keyboard;
		OIS::Mouse*			m_Mouse;
	};
}

#endif // __INPUTLISTENER_H__
