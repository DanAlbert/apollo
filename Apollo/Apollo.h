/**
 * @file Apollo.h
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
 * This file sets up macros for defining API visiblity as well handle
 * platform specific configuration.
 * 
 */
#ifndef APOLLO_H
#define APOLLO_H

#if defined WIN32 || defined __CYGWIN__
	#define _CRT_SECURE_NO_WARNINGS
	
	// Disable some MSVC warnings
	#if defined WIN32
		#pragma warning(disable:4018)
		#pragma warning(disable:4244)
		#pragma warning(disable:4251)
		#pragma warning(disable:4275)
		#pragma warning(disable:4290) // Exception spec ignored warnings
		#pragma warning(disable:4482)
		#pragma warning(disable:4503)
		#pragma warning(disable:4800)
	#endif // WIN32
	
	#define WIN32_LEAN_AND_MEAN

	#ifndef WINVER
		#define WINVER 0x0502
	#endif // WINVER

	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT 0x0502
	#endif // _WIN32_WINNT

	#ifdef APOLLO_EXPORTS
		#ifdef __GNUC__
			#define APOLLO_API __attribute__((dllexport))
		#else
			#define APOLLO_API __declspec(dllexport)
		#endif // __GNUC__
	#else
		#ifdef __GNUC__
			#define APOLLO_API __attribute__((dllimport))
		#else
			#define APOLLO_API __declspec(dllimport)
		#endif // __GNUC__
	#endif // APOLLO_EXPORTS

#else
	
	#if __GNUC__ >= 4
		#define APOLLO_API __attribute__((visibility("default")))
	#else
		#define APOLLO_API
	#endif // __GNUC__ >= 4
	
#endif // WIN32 || __CYGWIN__

#endif // APOLLO_H
