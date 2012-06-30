/**
 * @file Vector2.cpp
 * @author Dan Albert
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
#include "Vector2.h"

#include <math.h>

namespace Apollo
{
	TransformationMatrix GetTransformationMatrix(const Transformation& t);

	Vector2::Vector2(void) :
		x(0.0f),
		y(0.0f)
	{
	}

	Vector2::Vector2(double x, double y) :
		x(x),
		y(y)
	{
	}

	Vector2::Vector2(const Vector2& vector) :
		x(vector.x),
		y(vector.y)
	{
	}

	Vector2::~Vector2(void)
	{
	}

	Vector2& Vector2::operator= (const Vector2& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		this->x = rhs.x;
		this->y = rhs.y;

		return *this;
	}

	bool Vector2::operator== (const Vector2& rhs)
	{
		return ((this->x == rhs.x) && (this->y == rhs.y));
	}

	bool Vector2::operator!= (const Vector2& rhs)
	{
		return ((this->x != rhs.x) || (this->y != rhs.y));
	}

	Vector2 Vector2::operator+ (void) const
	{
		return Vector2(*this);
	}

	Vector2 Vector2::operator- (void) const
	{
		return Vector2(*this * -1);
	}

	Vector2 Vector2::operator+ (const Vector2& rhs) const
	{
		return Vector2(this->x + rhs.x, this->y + rhs.y);
	}
	
	Vector2 Vector2::operator- (const Vector2& rhs) const
	{
		return Vector2(this->x - rhs.x, this->y - rhs.y);
	}
	
	Vector2 Vector2::operator* (const double rhs) const
	{
		return Vector2(this->x * rhs, this->y * rhs);
	}
	
	Vector2 Vector2::operator/ (const double rhs) const
	{
		return Vector2(this->x / rhs, this->y / rhs);
	}
	
	Vector2 operator* (const double lhs, const Vector2& rhs)
	{
		return Vector2(rhs.x * lhs, rhs.y * lhs);
	}
	
	Vector2 operator/ (const double lhs, const Vector2& rhs)
	{
		return Vector2(rhs.x / lhs, rhs.y / lhs);
	}

	void Vector2::operator+= (const Vector2& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
	}

	void Vector2::operator-= (const Vector2& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
	}

	void Vector2::operator*= (const double rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
	}
	
	void Vector2::operator/= (const double rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
	}

	double Vector2::Cross(const Vector2& v) const
	{
		return (this->x * v.y) - (this->y * v.x);
	}

	double Vector2::Dot(const Vector2& v) const
	{
		return (this->x * v.x) + (this->y * v.y);
	}

	double Vector2::ScalarProjection(const Vector2& onto) const
	{
		return this->Dot(onto) / onto.GetMagnitude();
	}

	Vector2 Vector2::Normal(const Vector2& v) const
	{
		double x = -(v.y - this->y);
		double y = (v.x - this->x);
		return Vector2(x, y);
	}

	const double Vector2::GetMagnitude(void) const
	{
		return sqrt((this->x * this->x) + (this->y * this->y));
	}

	Vector2 Vector2::Transform(const Transformation& transform, const Vector2& center) throw()
	{
		TransformationMatrix tm = GetTransformationMatrix(transform);
		Vector2 v = *this - center;
		Vector2 tv;

		// Rotate and scale
		tv.x = tm.rows[0].Dot(v);
		tv.y = tm.rows[1].Dot(v);

		// translate
		tv += transform.translation + center;

		return tv;
	}

	TransformationMatrix GetTransformationMatrix(const Transformation& t)
	{
		Apollo::TransformationMatrix tm; // Transformation matrix
		Apollo::TransformationMatrix ts; // Scaling matrix
		Apollo::TransformationMatrix tr; // Rotation matrix

		// Scale
		ts.rows[0].x = t.scale.x;
		ts.rows[0].y = 0;
		ts.rows[1].x = 0;
		ts.rows[1].y = t.scale.y;

		// Rotate
		tr.rows[0].x = cos(t.rotation);
		tr.rows[0].y = -sin(t.rotation);
		tr.rows[1].x = sin(t.rotation);
		tr.rows[1].y = cos(t.rotation);

		// Multiply the matricies
		tm.rows[0].x = (ts.rows[0].x * tr.rows[0].x) + (ts.rows[0].y * tr.rows[1].x);
		tm.rows[0].y = (ts.rows[0].x * tr.rows[0].y) + (ts.rows[0].y * tr.rows[1].y);
		tm.rows[1].x = (ts.rows[1].x * tr.rows[0].x) + (ts.rows[1].y * tr.rows[1].x);
		tm.rows[1].y = (ts.rows[1].x * tr.rows[0].y) + (ts.rows[1].y * tr.rows[1].y);

		return tm;
	}
}
