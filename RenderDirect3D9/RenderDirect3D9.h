#ifndef RENDERDIRECT3D9_H
#define RENDERDIRECT3D9_H

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN

#ifndef WINVER
#define WINVER 0x0502
#endif // WINVER

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0502
#endif // _WIN32_WINNT

#endif // WIN32

#include <RenderSystem.h>
#include "RenderSystem_Direct3D9.h"

extern "C" __declspec(dllexport) Apollo::RenderSystem* CreateRenderSystem(
	const char* configPath,
	const char* windowTitle = "Apollo 2D Rendering Engine");

#endif // RENDERDIRECT3D9_H
