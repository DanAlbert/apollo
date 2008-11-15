#ifndef __WINDOW_H__
#define __WINDOW_H__

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

#endif // __WINDOW_H__