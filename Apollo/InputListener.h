/**
 * @file InputListener.h
 * @author Dan Albert <dan@gingerhq.net>
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
#ifndef INPUTLISTENER_H
#define INPUTLISTENER_H

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
		virtual ~InputListener(void) throw();

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

#endif // INPUTLISTENER_H
