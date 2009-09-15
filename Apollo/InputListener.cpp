#include "InputListener.h"

namespace Apollo
{
	InputListener::InputListener(Window* window)
	{
		Initialize(window);
	}

	InputListener::~InputListener(void)
	{ 
		Release();
	}

	bool InputListener::Initialize(Window* window)
	{
		OIS::ParamList pl;
		std::ostringstream wnd;

		wnd << (size_t)window->GetWindowHandle();

		pl.insert(std::make_pair(std::string("WINDOW"), wnd.str()));

#ifdef _DEBUG
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));	// DISCL_EXCLUSIVE  to hide mouse
#endif

		Log("[InputHandler] Creating OIS input system.");
		m_InputManager = OIS::InputManager::createInputSystem(pl);

		if (m_InputManager->getNumberOfDevices(OIS::Type::OISKeyboard) > 0)
		{
			m_Keyboard = static_cast<OIS::Keyboard*>(m_InputManager->createInputObject(OIS::OISKeyboard, true));
			m_Keyboard->setEventCallback(this);
		}
		else
		{
			ErrorQuit("No keyboard detected.", ERR_APOLLO_INPUTLISTENER_NOKEYBD);
		}
		
		if (m_InputManager->getNumberOfDevices(OIS::Type::OISMouse) > 0)
		{
			m_Mouse = static_cast<OIS::Mouse*>(m_InputManager->createInputObject(OIS::OISMouse, true));
			m_Mouse->setEventCallback(this);

			RECT rect;

			GetClientRect(window->GetWindowHandle(), &rect);

			const OIS::MouseState &ms = m_Mouse->getMouseState();
			ms.width = rect.right - rect.left;
			ms.height = rect.bottom - rect.top;
		}
		else
		{
			ErrorQuit("No mouse detected.", ERR_APOLLO_INPUTLISTENER_NOMOUSE);
		}

		return true;
	}

	void InputListener::Release(void)
	{
		if( m_InputManager )
		{
			m_InputManager->destroyInputObject(m_Keyboard);
			m_InputManager->destroyInputObject(m_Mouse);

			OIS::InputManager::destroyInputSystem(m_InputManager);
		}
	}

	bool InputListener::Update(void)
	{
		if (m_Mouse)
		{
			m_Mouse->capture();
		}

		if (m_Keyboard)
		{
			m_Keyboard->capture();
		}

		return true;
	}
}