/**
 * @file InputListener.cpp
 * @author Dan Albert <dan@gingerhq.net>
 * @date Last updated 06/19/2012
 *
 * @section LICENSE
 * 
 * Apollo 2D Rendering Engine
 * Copyright (C) 2012 Dan Albert
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * @section DESCRIPTION
 * 
 * Defines a basic OIS input listener which ignores all input.
 * 
 * Since any interpretation of input is dependent on the intended use of the
 * engine by the client application, any additional functionality would be
 * impossible to predict. As such, client applications must extend this class
 * to provide the necessary functionality.
 * 
 */
#include "InputListener.h"

namespace Apollo
{
	InputListener::InputListener(Window* window)
	{
		Initialize(window);
	}

	InputListener::~InputListener(void) throw()
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
			ErrorQuit(ERR_APOLLO_INPUTLISTENER_NOKEYBD);
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
			ErrorQuit(ERR_APOLLO_INPUTLISTENER_NOMOUSE);
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
