/**
 * @file Apollo.h
 * @author Dan Albert
 * @date Last updated 23/02/2011
 * @version 1.0
 *
 * @section LICENSE
 * 
 * Apollo 2D Rendering Engine
 * Copyright (C) 2011 Dan Albert
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
 * This file sets up macros for defining API visiblity as well handle
 * platform specific configuration.
 * 
 */
#ifndef __APOLLO_H__
#define __APOLLO_H__

#ifdef WIN32

#define _CRT_SECURE_NO_WARNINGS

#pragma warning(disable:4018)
#pragma warning(disable:4244)
#pragma warning(disable:4251)
#pragma warning(disable:4275)
#pragma warning(disable:4482)
#pragma warning(disable:4503)
#pragma warning(disable:4800)

#define WIN32_LEAN_AND_MEAN

#ifndef WINVER
#define WINVER 0x0502
#endif // WINVER

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0502
#endif // _WIN32_WINNT

#ifdef APOLLO_EXPORTS
#define APOLLO_API __declspec(dllexport)
#else
#define APOLLO_API __declspec(dllimport)
#endif // APOLLO_EXPORTS

#endif // WIN32

#endif // __APOLLO_H__