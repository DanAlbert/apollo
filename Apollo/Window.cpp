/**
 * @file Window.cpp
 * @author Dan Albert
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
 * Defines an wrapper for a Win32 window.
 * 
 */
#include "Window.h"

using namespace Apollo;

Window::Window(const char* title, int width, int height)
{
	m_Width = width;
	m_Height = height;

	Log("[Window] Creating Win32 window.");
	m_Window = CreateWindow(
		title,
		title,
		WS_POPUP | WS_VISIBLE | WS_EX_TOPMOST | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		m_Width,
		m_Height,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL);

	if (!m_Window)
	{
		ErrorQuit(ERR_APOLLO_WINDOW_CREATE);
	}

	ShowWindow(m_Window, SW_SHOWNORMAL);
	UpdateWindow(m_Window);
}

Window::~Window(void)
{
	Release();
}

void Window::Release(void)
{
}

void Window::Resize(int width, int height)
{
	SetWindowPos(m_Window, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
}
