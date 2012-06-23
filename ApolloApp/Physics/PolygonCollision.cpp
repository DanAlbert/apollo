/**
 * @file PolygonCollision.cpp
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
 *	Provides functions for detection of collisions between convex
 *	quadtrilaterals.
 * 
 */
#include "PolygonCollision.h"

/**
 * Determines the distance between two intervals.
 */
double intervalDistance(
	const double minA,
	const double maxA,
	const double minB,
	const double maxB)
{
	return (minA < minB) ? minB - maxA : minA - maxB;
}

/**
 * Determines if two intervals overlap.
 */
bool intervalsOverlap(
	const double minA,
	const double maxA,
	const double minB,
	const double maxB)
{
	return intervalDistance(minA, maxA, minB, maxB) < 0;
}

bool PolygonCollision(const Geometry& a, const Geometry& b)
{
	for (int i = 0; i < a.GetNumVerticies(); i++)
	{
		Apollo::Vector2 projectionAxis;
		double minA;
		double maxA;
		double minB;
		double maxB;

		Vertex u = const_cast<Geometry&>(a)[i];
		Vertex v = const_cast<Geometry&>(a)[(i + 1) % a.GetNumVerticies()];

		u -= Translation(a.GetWidth() / 2, a.GetHeight() / 2);
		v -= Translation(a.GetWidth() / 2, a.GetHeight() / 2);
		u = Transform(u, a.GetTransform());
		v = Transform(v, a.GetTransform());
		u += Translation(a.GetWidth() / 2, a.GetHeight() / 2);
		v += Translation(a.GetWidth() / 2, a.GetHeight() / 2);

		projectionAxis = u.Normal(v);

		a.Project(projectionAxis, &minA, &maxA);
		b.Project(projectionAxis, &minB, &maxB);

		if (!intervalsOverlap(minA, maxA, minB, maxB))
		{
			return false;
		}
	}

	for (int i = 0; i < b.GetNumVerticies(); i++)
	{
		Apollo::Vector2 projectionAxis;
		double minA;
		double maxA;
		double minB;
		double maxB;

		Vertex u = const_cast<Geometry&>(a)[i];
		Vertex v = const_cast<Geometry&>(a)[(i + 1) % a.GetNumVerticies()];

		u -= Translation(b.GetWidth() / 2, b.GetHeight() / 2);
		v -= Translation(b.GetWidth() / 2, b.GetHeight() / 2);
		u = Transform(u, b.GetTransform());
		v = Transform(v, b.GetTransform());
		u += Translation(b.GetWidth() / 2, b.GetHeight() / 2);
		v += Translation(b.GetWidth() / 2, b.GetHeight() / 2);

		projectionAxis = u.Normal(v);

		a.Project(projectionAxis, &minA, &maxA);
		b.Project(projectionAxis, &minB, &maxB);

		if (!intervalsOverlap(minA, maxA, minB, maxB))
		{
			return false;
		}
	}

	return true;
}
