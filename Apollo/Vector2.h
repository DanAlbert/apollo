/**
 * @file Vector2.h
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
 * A two-dimensional vector.
 *
 * Vector2s are commonly used for coordinates in a two-dimensional plane.
 * 
 */
#ifndef VECTOR2_H
#define VECTOR2_H

#include "Apollo.h"

namespace Apollo
{
	class APOLLO_API Vector2
	{
	public:
		double x;
		double y;

		Vector2(void);
		Vector2(double x, double y);
		Vector2(const Vector2& vector);
		~Vector2(void);

		Vector2& operator= (const Vector2& rhs);
		bool operator== (const Vector2& rhs);
		bool operator!= (const Vector2& rhs);
		Vector2& operator+ (void) const;
		Vector2& operator- (void) const;
		Vector2& operator+ (const Vector2& rhs) const;
		Vector2& operator- (const Vector2& rhs) const;
		Vector2& operator* (const double rhs) const;
		Vector2& operator/ (const double rhs) const;
		friend Vector2& operator* (const double lhs, const Vector2& rhs);
		friend Vector2& operator/ (const double lhs, const Vector2& rhs);
		void operator+= (const Vector2& rhs);
		void operator-= (const Vector2& rhs);
		void operator*= (const double rhs);
		void operator/= (const double rhs);

		const double GetMagnitude(void) const;
	};
}

#endif // VECTOR2_H
