/**
 * @file Geometry.cpp
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
 *	Defines basic geometries and transformations as well as functions for
 *	manipulating vectors and quadrilaterals.
 * 
 */
#include "Geometry.h"

#include <math.h>

#include <Apollo/Debug.h>

#include "BoundingBox.h"
#include "PolygonCollision.h"

Geometry::Geometry(void) throw()
{
	transform.scale = Apollo::Vector2(1.0f, 1.0f);
}

Geometry::Geometry(const Geometry& p) throw() :
	vertexList(p.vertexList),
	transform(p.transform)
{
}

Geometry::Geometry(const VertexList& vertexList) throw() :
	vertexList(vertexList)
{
	transform.scale = Apollo::Vector2(1.0f, 1.0f);
}

Geometry::Geometry(const VertexList& vertexList, const Transformation& transform) throw() :
	vertexList(vertexList),
	transform(transform)
{
}

Geometry::~Geometry(void) throw()
{
}

Geometry& Geometry::operator=(const Geometry& p) throw()
{
	this->vertexList = p.vertexList;
	return *this;
}

Vertex& Geometry::operator[](const int i) throw(Apollo::OutOfBoundsError)
{
	if ((i < 0) || (i >= this->vertexList.size()))
	{
		throw Apollo::OutOfBoundsError();
	}

	return this->vertexList[i];
}



const double Geometry::GetWidth(void) const throw()
{
	double minX;
	double maxX;
		
	if (this->GetNumVerticies() < 3)
	{
		return 0;
	}

	minX = this->vertexList[0].x;
	maxX = this->vertexList[0].x;

	for (int i = 1; i < this->GetNumVerticies(); i++)
	{
		double x = this->vertexList[i].x;

		if (x < minX)
		{
			minX = x;
		}
		else if (x > maxX)
		{
			maxX = x;
		}
	}

	return maxX - minX;
}

const double Geometry::GetHeight(void) const throw()
{
	double minY;
	double maxY;
		
	if (this->GetNumVerticies() < 3)
	{
		return 0;
	}

	minY = this->vertexList[0].y;
	maxY = this->vertexList[0].y;

	for (int i = 1; i < this->GetNumVerticies(); i++)
	{
		double y = this->vertexList[i].y;

		if (y < minY)
		{
			minY = y;
		}
		else if (y > maxY)
		{
			maxY = y;
		}
	}

	return maxY - minY;
}

const BoundingBox Geometry::GetBoundingBox(void) const throw()
{
	double minX;
	double maxX;
	double minY;
	double maxY;
	
	double halfWidth = this->GetWidth() / 2;
	double halfHeight = this->GetHeight() / 2;

	for (int i = 0; i < this->GetNumVerticies(); i++)
	{
		Vertex v = this->vertexList[i];

		// Rotate the point
		double x = (v.x - halfWidth) * cos(this->transform.rotation) -
			(v.y - halfHeight) * sin(this->transform.rotation);

		double y = (v.x - halfWidth) * sin(this->transform.rotation) +
			(v.y - halfHeight) * cos(this->transform.rotation);

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

	// Create the bounding box
	BoundingBox boundingBox;

	boundingBox.points[0].x = minX;
	boundingBox.points[0].y = minY;

	boundingBox.points[1].x = minX;
	boundingBox.points[1].y = maxY;

	boundingBox.points[2].x = maxX;
	boundingBox.points[2].y = maxY;

	boundingBox.points[3].x = maxX;
	boundingBox.points[3].y = minY;

	// Set the bounding boxes translation
	boundingBox.transform = this->transform;
	boundingBox.transform.scale = this->transform.scale;
	boundingBox.transform.translation += Translation(halfWidth, halfHeight);
	boundingBox.transform.rotation = 0;

	return boundingBox;
}

bool Geometry::CollidesWith(const Geometry& other) const throw()
{
	if (BoundingBoxesCollide(this->GetBoundingBox(), other.GetBoundingBox()))
	{
		return PolygonCollision(*this, other);
	}

	return false;
}

void Geometry::Project(const Apollo::Vector2& axis, double* min, double*max) const
{
	VertexList list;
	
	for (int i = 0; i < this->GetNumVerticies(); i++)
	{
		list.push_back(Transform(this->vertexList[i], this->transform));
	}

	Geometry transformed(list);

	double component = transformed[0].ScalarProjection(axis);
	*min = component;
	*max = component;

	for (int i = 1; i < this->GetNumVerticies(); i++)
	{
		component = transformed[i].Dot(axis);
		*min = (component < *min) ? component : *min;
		*max = (component > *max) ? component : *max;
	}
}

Apollo::Vector2 Transform(const Apollo::Vector2& v, const Transformation& t)
{
	TransformationMatrix tm = GetTransformationMatrix(t);
	Apollo::Vector2 tv;

	// Rotate and scale
	tv.x = tm.rows[0].Dot(v);
	tv.y = tm.rows[1].Dot(v);

	// translate
	tv.x += t.translation.x;
	tv.y += t.translation.y;

	return tv;
}

Quad TransformQuad(const Quad& quad)
{
	Quad transformed;

	for (int i = 0; i < 4; i++)
	{
		transformed.points[i] = Transform(quad.points[i], quad.transform);
	}

	return transformed;
}

TransformationMatrix GetTransformationMatrix(const Transformation& t)
{
	TransformationMatrix tm; // Transformation matrix
	TransformationMatrix ts; // Scaling matrix
	TransformationMatrix tr; // Rotation matrix

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

void ProjectQuad(
	const Quad& quad,
	const Apollo::Vector2& axis,
	double* min,
	double* max)
{
	Quad transformed = TransformQuad(quad);
	double component = transformed.points[0].ScalarProjection(axis);
	*min = component;
	*max = component;

	for (int i = 1; i < 4; i++)
	{
		component = transformed.points[i].Dot(axis);
		*min = (component < *min) ? component : *min;
		*max = (component > *max) ? component : *max;
	}
}
