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

namespace Apollo
{
	Geometry::Geometry(void) throw()
	{
		transform.scale = Vector2(1.0f, 1.0f);
	}

	Geometry::Geometry(const Geometry& p) throw() :
		vertexList(p.vertexList),
		transform(p.transform)
	{
	}

	Geometry::Geometry(const VertexList& vertexList) throw() :
		vertexList(vertexList)
	{
		transform.scale = Vector2(1.0f, 1.0f);
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

	Apollo::Vertex& Geometry::operator[](const int i) throw(OutOfBoundsError)
	{
		if ((i < 0) || (i >= this->vertexList.size()))
		{
			throw OutOfBoundsError();
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

	const Vector2 Geometry::GetCenter(void) const throw()
	{
		return Vertex(this->GetWidth() / 2, this->GetHeight() / 2) + this->distanceToOrigin();
	}

	const BoundingBox Geometry::GetBoundingBox(void) const throw()
	{
		double minX;
		double maxX;
		double minY;
		double maxY;

		for (int i = 0; i < this->GetNumVerticies(); i++)
		{
			Vertex v = this->vertexList[i];
			Vertex tv = v.Transform(
				this->GetTransform(),
				this->GetCenter());

			// Set the beginnning minima and maxima
			if (i == 0)
			{
				minX = tv.x;
				maxX = tv.x;
				minY = tv.y;
				maxY = tv.y;
			}
		
			// Find the minimum in each dimension
			minX = (tv.x < minX) ? tv.x : minX;
			maxX = (tv.x > maxX) ? tv.x : maxX;
			minY = (tv.y < minY) ? tv.y : minY;
			maxY = (tv.y > maxY) ? tv.y : maxY;
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

		return boundingBox;
	}

	bool Geometry::CollidesWith(const Geometry& other) const throw()
	{
		if (this->boundingBoxCollision(other))
		{
			return this->polygonCollision(other);
		}

		return false;
	}

	void Geometry::Project(const Vector2& axis, double* min, double* max) const
	{
		Apollo::VertexList list;
	
		for (int i = 0; i < this->GetNumVerticies(); i++)
		{
			Vertex u = this->vertexList[i];
			list.push_back(u.Transform(this->GetTransform(), this->GetCenter()));
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

	const Geometry Geometry::Transformed(void) const throw()
	{
		VertexList transformed;

		for (int i = 0; i < this->GetNumVerticies(); i++)
		{
			Vertex u = this->vertexList[i];
			transformed.push_back(u.Transform(this->GetTransform(), this->GetCenter()));
		}

		return Geometry(transformed);
	}

	Vector2 Geometry::distanceToOrigin(void) const throw()
	{
		
		double minX;
		double minY;

		minX = this->vertexList[0].x;
		minY = this->vertexList[0].y;

		for (int i = 1; i < this->GetNumVerticies(); i++)
		{
			double x = this->vertexList[i].x;
			double y = this->vertexList[i].y;

			if (x < minX)
			{
				minX = x;
			}
			if (y < minY)
			{
				minY = y;
			}
		}

		return Vector2(minX, minY);
	}

	bool Geometry::boundingBoxCollision(const Geometry& other) const throw()
	{
		// The boundaries for each box
		double aLeft = this->GetBoundingBox().points[0].x;
		double aRight = this->GetBoundingBox().points[3].x;
		double aTop = this->GetBoundingBox().points[1].y;
		double aBottom = this->GetBoundingBox().points[0].y;

		double bLeft = other.GetBoundingBox().points[0].x;
		double bRight = other.GetBoundingBox().points[3].x;
		double bTop = other.GetBoundingBox().points[1].y;
		double bBottom = other.GetBoundingBox().points[0].y;

		// It's much easier to determine if two boxes do
		// NOT intersect, so just invert that result.
		return	!((aRight < bLeft) ||
				  (aLeft > bRight) ||
				  (aTop < bBottom) ||
				  (aBottom > bTop));
	}

	bool Geometry::polygonCollision(const Geometry& other) const throw()
	{
		for (int i = 0; i < this->GetNumVerticies(); i++)
		{
			Vector2 projectionAxis;
			double minA;
			double maxA;
			double minB;
			double maxB;

			Vertex u = this->vertexList[i];
			Vertex v = this->vertexList[(i + 1) % this->GetNumVerticies()];

			Vertex ut = u.Transform(this->GetTransform(), this->GetCenter());
			Vertex vt = v.Transform(this->GetTransform(), this->GetCenter());

			projectionAxis = u.Normal(v);

			this->Project(projectionAxis, &minA, &maxA);
			other.Project(projectionAxis, &minB, &maxB);

			if (!intervalsOverlap(minA, maxA, minB, maxB))
			{
				return false;
			}
		}

		for (int i = 0; i < other.GetNumVerticies(); i++)
		{
			Apollo::Vector2 projectionAxis;
			double minA;
			double maxA;
			double minB;
			double maxB;

			Apollo::Vertex u = const_cast<Geometry&>(other)[i];
			Apollo::Vertex v = const_cast<Geometry&>(other)[(i + 1) % other.GetNumVerticies()];

			Vertex ut = u.Transform(other.GetTransform(), other.GetCenter());
			Vertex vt = v.Transform(other.GetTransform(), other.GetCenter());

			projectionAxis = u.Normal(v);

			this->Project(projectionAxis, &minA, &maxA);
			other.Project(projectionAxis, &minB, &maxB);

			if (!intervalsOverlap(minA, maxA, minB, maxB))
			{
				return false;
			}
		}

		return true;
	}

	/**
	 * Determines the distance between two intervals.
	 */
	double Geometry::intervalDistance(
		const double minA,
		const double maxA,
		const double minB,
		const double maxB) const throw()
	{
		return (minA < minB) ? minB - maxA : minA - maxB;
	}

	
	bool Geometry::intervalsOverlap(
		const double minA,
		const double maxA,
		const double minB,
		const double maxB) const throw()
	{
		return intervalDistance(minA, maxA, minB, maxB) < 0;
	}
}
