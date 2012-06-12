/**
 * @file Window.h
 * @author Dan Albert <dan@gingerhq.net>
 * @date Last updated 06/11/2012
 * @version 0.2.53
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
 * Defines an wrapper for a Win32 window.
 * 
 */
#ifndef WINDOW_H
#define WINDOW_H

#include "Apollo.h"

#include <Windows.h>

#include "Debug.h"

namespace Apollo
{
	/// Window handler class
	/** Handles window creation, resizing, and clean up. */
	class APOLLO_API Window
	{
	public:
		/// Window constructor
		/**
		 * Creates and initializes the window. After the window
		 * is created, it's handle is stored in m_Window.
		 * @param title Window title bar caption
		 * @param width Window width
		 * @param height Window height
		 * @see ~Window()
		 * @see Resize()
		 * @see m_Window
		 * @see m_Width
		 * @see m_Height
		 */
		Window(const char* title, int width, int height);
		~Window(void);

		/// Release window
		/** Releases the window handle and cleans up
		 *  additional resources.
		 */
		void Release(void);

		/// Resizes the window
		/**
		 * @param width Window width
		 * @param height Window height
		 * @see m_Window
		 * @see m_Width
		 * @see m_Height
		 */
		void Resize(int width, int height);

		inline HWND	GetWindowHandle(void) const {	return m_Window;	}

		inline void SetTitle(const char* title) {	SetWindowText(m_Window, title);	}

	protected:
		HWND m_Window;	///< Window handle
		int m_Width;	///< Window width
		int m_Height;	///< Window height
	};
}

#endif // WINDOW_H
