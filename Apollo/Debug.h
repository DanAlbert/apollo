#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "Apollo.h"

#include <cassert>
#include <stdio.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

// byte 0:		Application
// byte 1:		Class
// byte 2/3:	Error ID
#define ERR_NONE	0x00000000

#define ERR_APOLLO_WINDOW_CREATE	0x10010001

// These should be moved to RenderDirect3D9
#define ERR_APOLLO_RENDERSYSTEM_NOD3D		0x10020001
#define ERR_APOLLO_RENDERSYSTEM_NODEV		0x10020002
#define ERR_APOLLO_RENDERSYSTEM_NOSPRITE	0x10020003
#define ERR_APOLLO_RENDERSYSTEM_BACKBUFFER	0x10020004
#define ERR_APOLLO_RENDERSYSTEM_PIXELFORMAT	0x10020005

#define ERR_APOLLO_INPUTLISTENER_NOKEYBD	0x10030001
#define ERR_APOLLO_INPUTLISTENER_NOMOUSE	0x10030002

extern const char LOG_FILE[];

void APOLLO_API ErrorMessage(const char* szText);
void APOLLO_API ErrorQuit(const char* szText, int iErrNo = ERR_NONE);
void APOLLO_API Log(const char* szFormat, ...);
void APOLLO_API LogNoTime(const char* szFormat, ...);

#endif