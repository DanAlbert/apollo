/**
 * @file Debug.cpp
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
 * Debug, error handling and logging facilities.
 * 
 */
#include "debug.h"

#include <stdlib.h>
#include <string>
#include <sstream>

const char LOG_FILE[] = "apollo.log";

inline const char* ErrorStr(const int err)
{
	static std::string msg; // Static so messages for unknown errors will be preserved
	std::stringstream ss;

	switch (err)
	{
	case ERR_NONE:
		return "No error";
	case ERR_SYSTEM_OUTOFBOUNDS:
		return "Index out of bounds";
	case ERR_APOLLO_WINDOW_CREATE:
		return "Could not create window";
	case ERR_APOLLO_RENDERSYSTEM_NOD3D:
		return "Could not initialize Direct3D";
	case ERR_APOLLO_RENDERSYSTEM_NODEV:
		return "Could not create the Direct3D device";
	case ERR_APOLLO_RENDERSYSTEM_NOSPRITE:
		return "Could not create the Direct3D sprite handler";
	case ERR_APOLLO_RENDERSYSTEM_BACKBUFFER:
		return "Could not retrieve the Direct3D backbuffer";
	case ERR_APOLLO_RENDERSYSTEM_PIXELFORMAT:
		return "Could not find a supported pixel format for the requested screen resolution";
	case ERR_APOLLO_RENDERSYSTEM_LOADLIB:
		return "Failed to load RenderSystem library";
	case ERR_APOLLO_RENDERSYSTEM_LOADPROC:
		return "Failed to load CreateRenderSystem()";
	case ERR_APOLLO_INPUTLISTENER_NOKEYBD:
		return "No keyboard detected";
	case ERR_APOLLO_INPUTLISTENER_NOMOUSE:
		return "No mouse detected";
	case ERR_APOLLO_CONFIGURATION_LOAD:
		return "Could not load configuration file";
	case ERR_APOLLO_SPRITEDEF_LOAD:
		return "Could not load sprite definition file";
	case ERR_APOLLO_TEXTURE_LOAD_INFO:
		return "Could not load image info";
	case ERR_APOLLO_TEXTURE_LOAD_FILE:
		return "Could not load image info";
	case ERR_APOLLOAPP_ENTITYDEF_LOAD:
		return "Could not load entity definition file";
	case ERR_APOLLOAPP_ENTITYDEF_MISSINGELEM:
		return "Entity missing element";
	case ERR_APOLLOAPP_ENTITYDEF_MISSINGATTR:
		return "Entity missing attribute";
	case ERR_APOLLOAPP_PLAYERDEF_LOAD:
		return "Could not load Player definition file";
	case ERR_APOLLOAPP_PLAYERDEF_MISSINGATTR:
		return "Player missing attribute";
	case ERR_APOLLOAPP_PLAYERDEF_MISSINGELEM:
		return "Player missing element";
	default:
		ss << std::hex << "0x" << err;
		msg = "Unknown error: " + ss.str();
		return msg.c_str();
	}
}

// MessageBox() wrappers
inline void ErrorMessage(const char* szText)
{
	Log("%s", szText);
	MessageBox(NULL, szText, "Error!", MB_OK);
}

inline void ErrorQuit(const int err)
{
	Log("%s (0x%02X)", ErrorStr(err), err);
	MessageBox(NULL, ErrorStr(err), "Error!", MB_OK);
	exit(EXIT_FAILURE);
}

inline void ErrorQuit(const Apollo::ApolloError& ex)
{
	Log("%s (0x%02X)", ex.getErrStr(), ex.getErrNo());
	MessageBox(NULL, ex.getErrStr(), "Error!", MB_OK);
	exit(EXIT_FAILURE);
}

inline void Log(const char* szFormat, ...)
{
	if (!szFormat)
	{
		return;
	}

	const time_t t = time(NULL);
	tm* c = localtime(&t);
	
	FILE* fp = NULL;
	if ((fp = fopen(LOG_FILE, "a")) == NULL)
	{
		return;
	}

	// Begin by prepending time to log file
	fprintf(
		fp,
		"|%02d-%02d-%04d  %02d:%02d:%02d| ",
		c->tm_mday,
		(c->tm_mon + 1),
		(c->tm_year + 1900),
		c->tm_hour,
		c->tm_min,
		c->tm_sec);

	// Begin va list 
	va_list args;
	va_start(args, szFormat);
	
	// Print formatted log message to log file
	vfprintf(fp, szFormat, args);
	putc('\n', fp);

	// Print formatted log message to stdout
	vprintf(szFormat, args);
	putchar('\n');

	va_end(args);
	fclose(fp);
}

inline void LogNoTime(const char* szFormat, ...)
{
	if (!szFormat)
	{
		return;
	}
	
	FILE* fp = NULL;
	if ((fp = fopen(LOG_FILE, "a")) == NULL)
	{
		return;
	}

	// Begin va list 
	va_list args;
	va_start(args, szFormat);
	
	// Print formatted log message to log file
	vfprintf(fp, szFormat, args);
	putc('\n', fp);

	// Print formatted log message to stdout
	vprintf(szFormat, args);
	putchar('\n');

	va_end(args);
	fclose(fp);
}
