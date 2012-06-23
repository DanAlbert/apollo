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
 * Defines basic geometries and transformations as well as functions for
 * manipulating vectors and quadrilaterals.
 * 
 */
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>

#include <Apollo/OutOfBoundsError.h>
#include <Apollo/Vector2.h>

const double PI = 3.1415926535f;
const double DEGREES_TO_RADIANS = (PI / 180.0f);
const double RADIANS_TO_DEGREES = (180.0f / PI);

/// Vertex type definition
typedef Apollo::Vector2 Vertex;

/// Translation vector type definition
typedef Apollo::Vector2 Translation;

/// Scale vector type definition
typedef Apollo::Vector2 Scale;

/// Angle type definition
typedef double Rotation;

struct Transformation
{
	Translation translation;
	Rotation rotation;
	Scale scale;
};

struct TransformationMatrix
{
	Apollo::Vector2 rows[2];
};

struct Quad
{
	Vertex points[4];
	Transformation transform;
};

/// Bounding box type definition
typedef Quad BoundingBox;

/// Vertex list type definition
typedef std::vector<Vertex> VertexList;

class Geometry
{
public:
	Geometry(void) throw();
	Geometry(const Geometry& p) throw();
	Geometry(const VertexList& vertexList) throw();
	Geometry(const VertexList& vertexList, const Transformation& transform) throw();
	~Geometry(void) throw();

	Geometry& operator=(const Geometry& p) throw();
	Vertex& operator[](const int i) throw(Apollo::OutOfBoundsError);

	const double GetWidth(void) const throw();
	const double GetHeight(void) const throw();

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

	void Project(const Apollo::Vector2& axis, double* min, double* max) const;

private:
	VertexList vertexList;
	Transformation transform;
};

/**
 * Applies a transformation to a given vector.
 */
Apollo::Vector2 Transform(const Vertex& v, const Transformation& t);

/**
 * Transforms a quadrilateral according to its scaling,
 * rotation and translation.
 */
Quad TransformQuad(const Quad& quad);

/**
 * Gets a rotation and scaling matrix for a given transformation.
 */
TransformationMatrix GetTransformationMatrix(const Transformation& t);

/**
 * Finds the minimum and maximum values for the quad
 * when projected onto the given axis.
 */
void ProjectQuad(
	const Quad& quad,
	const Apollo::Vector2& axis,
	double* min,
	double* max);

#endif // GEOMETRY_H
