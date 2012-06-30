/**
 * @file Geometry.h
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
 * Defines basic geometries as well as functions for
 * manipulating vectors and quadrilaterals.
 * 
 */
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>

#include <Apollo/OutOfBoundsError.h>
#include <Apollo/Vector2.h>

namespace Apollo
{
	const double PI = 3.1415926535f;
	const double DEGREES_TO_RADIANS = (PI / 180.0f);
	const double RADIANS_TO_DEGREES = (180.0f / PI);

	struct BoundingBox
	{
		Vertex points[4];
	};

	class APOLLO_API Geometry
	{
	public:
		Geometry(void) throw();
		Geometry(const Geometry& p) throw();
		Geometry(const VertexList& vertexList) throw();
		Geometry(const VertexList& vertexList, const Transformation& transform) throw();
		~Geometry(void) throw();

		Geometry& operator=(const Geometry& p) throw();
		Vertex& operator[](const int i) throw(OutOfBoundsError);

		const double GetWidth(void) const throw();
		const double GetHeight(void) const throw();
		const Vector2 GetCenter(void) const throw();

		inline const int GetNumVerticies(void) const throw()
		{
			return this->vertexList.size();
		}

		inline const Transformation& GetTransform(void) const throw()
		{
			return this->transform;
		}

		inline void SetTransform(const Transformation& transform) throw()
		{
			this->transform = transform;
		}

		const BoundingBox GetBoundingBox(void) const throw();

		bool CollidesWith(const Geometry& other) const throw();

		void Project(const Vector2& axis, double* min, double* max) const;

		const Geometry Transformed(void) const throw();

	private:
		VertexList vertexList;
		Transformation transform;

		/**
		 * @brief Returns a vector describing the distance between the origin and the geometry.
		 * 
		 * Distance to origin as defined as the inverse of the translation
		 * that would leave all vertecies in the positive xy quadrant while
		 * having at least one vertex on each axis.
		 */
		Vector2 distanceToOrigin(void) const throw();

		bool boundingBoxCollision(const Geometry& other) const throw();
		bool polygonCollision(const Geometry& other) const throw();

		/**
		 * Determines the distance between two intervals.
		 */
		double Geometry::intervalDistance(
			const double minA,
			const double maxA,
			const double minB,
			const double maxB) const throw();

		/**
		 * Determines if two intervals overlap.
		 */
		bool Geometry::intervalsOverlap(
			const double minA,
			const double maxA,
			const double minB,
			const double maxB) const throw();
	};
}

#endif // GEOMETRY_H
