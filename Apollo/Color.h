/**
 * @file Color.h
 * @author Dan Albert <dan@gingerhq.net>
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
 * Defines a basic ARGB color class and exposes default colors.
 * 
 */
#ifndef COLOR_H
#define COLOR_H

#include "Apollo.h"

namespace Apollo
{
	class APOLLO_API Color
	{
	public:
		unsigned char a;
		unsigned char r;
		unsigned char g;
		unsigned char b;

		Color(
			unsigned char r,
			unsigned char g,
			unsigned char b);

		Color(
			unsigned char a,
			unsigned char r,
			unsigned char g,
			unsigned char b);

		static const Color Black;
		static const Color White;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Magenta;
		static const Color Cyan;
	};
}

#endif // COLOR_H
