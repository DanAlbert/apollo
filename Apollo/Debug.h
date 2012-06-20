/**
 * @file Debug.h
 * @author Dan Albert <dan@gingerhq.net>
 * @date Last updated 06/18/2012
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
 * Debug, error handling and logging facilities.
 * 
 */
#ifndef DEBUG_H
#define DEBUG_H

#include "Apollo.h"

#include <cassert>
#include <stdio.h>
#include <time.h>

#include "ApolloError.h"

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
#define ERR_APOLLO_RENDERSYSTEM_LOADLIB		0x10020006
#define ERR_APOLLO_RENDERSYSTEM_LOADPROC	0x10020007

#define ERR_APOLLO_INPUTLISTENER_NOKEYBD	0x10030001
#define ERR_APOLLO_INPUTLISTENER_NOMOUSE	0x10030002

#define ERR_APOLLO_CONFIGURATION_LOAD		0x10040001

#define ERR_APOLLO_SPRITEDEF_LOAD			0x10050001

#define ERR_APOLLO_TEXTURE_LOAD_INFO		0x10060001
#define ERR_APOLLO_TEXTURE_LOAD_FILE		0x10060002

extern const char LOG_FILE[];

APOLLO_API const char* ErrorStr(const int err);

void APOLLO_API ErrorMessage(const char* szText);
void APOLLO_API ErrorQuit(const int err = ERR_NONE);
void APOLLO_API ErrorQuit(const Apollo::ApolloError& ex);
void APOLLO_API Log(const char* szFormat, ...);
void APOLLO_API LogNoTime(const char* szFormat, ...);

#endif // DEBUG_H
