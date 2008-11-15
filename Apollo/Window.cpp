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
		ErrorQuit("Could not create window.", ERR_APOLLO_WINDOW_CREATE);
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
