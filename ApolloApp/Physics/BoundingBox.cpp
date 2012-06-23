/**
 * @file BoundingBox.cpp
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

 * Defines a bounding box type and provides functions for determining
 * collisions.
 * 
 */
#include "BoundingBox.h"

#include <Windows.h>
#include <GL/gl.h>
#include <math.h>

#include "Geometry.h"

bool BoundingBoxesCollide(const BoundingBox& a, const BoundingBox& b)
{
	// The boundaries for each box
	double aLeft = a.points[0].x + a.transform.translation.x;
	double aRight = a.points[3].x + a.transform.translation.x;
	double aTop = a.points[1].y + a.transform.translation.y;
	double aBottom = a.points[0].y + a.transform.translation.y;

	double bLeft = b.points[0].x + b.transform.translation.x;
	double bRight = b.points[3].x + b.transform.translation.x;
	double bTop = b.points[1].y + b.transform.translation.y;
	double bBottom = b.points[0].y + b.transform.translation.y;

	// It's much easier to determine if two boxes do
	// NOT intersect, so just invert that result.
	return	!((aRight < bLeft) ||
			  (aLeft > bRight) ||
			  (aTop < bBottom) ||
			  (aBottom > bTop));
}

void CalculateBoundingBox(const Quad& polygon, BoundingBox* boundingBox)
{
	double minX;
	double maxX;
	double minY;
	double maxY;

	for (int i = 0; i < 4; i++)
	{
		// Rotate the point
		double x = polygon.points[i].x * cos(polygon.transform.rotation) -
			polygon.points[i].y * sin(polygon.transform.rotation);

		double y = polygon.points[i].x * sin(polygon.transform.rotation) +
			polygon.points[i].y * cos(polygon.transform.rotation);

		// Set the beginnning minimums and maximums
		if (i == 0)
		{
			minX = x;
			maxX = x;
			minY = y;
			maxY = y;
		}
		
		// Find the minimum in each dimension
		minX = (x < minX) ? x : minX;
		maxX = (x > maxX) ? x : maxX;
		minY = (y < minY) ? y : minY;
		maxY = (y > maxY) ? y : maxY;
	}

	// Create the quad
	boundingBox->points[0].x = minX;
	boundingBox->points[0].y = minY;

	boundingBox->points[1].x = minX;
	boundingBox->points[1].y = maxY;

	boundingBox->points[2].x = maxX;
	boundingBox->points[2].y = maxY;

	boundingBox->points[3].x = maxX;
	boundingBox->points[3].y = minY;

	// Set the bounding boxes translation
	boundingBox->transform = polygon.transform;
}
