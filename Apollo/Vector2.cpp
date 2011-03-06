#include "Vector2.h"

#include <math.h>

namespace Apollo
{
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

	Vector2& Vector2::operator+ (void) const
	{
		return Vector2(*this);
	}

	Vector2& Vector2::operator- (void) const
	{
		return Vector2(*this * -1);
	}

	Vector2& Vector2::operator+ (const Vector2& rhs) const
	{
		return Vector2(this->x + rhs.x, this->y + rhs.y);
	}
	
	Vector2& Vector2::operator- (const Vector2& rhs) const
	{
		return Vector2(this->x - rhs.x, this->y - rhs.y);
	}
	
	Vector2& Vector2::operator* (const double rhs) const
	{
		return Vector2(this->x * rhs, this->y * rhs);
	}
	
	Vector2& Vector2::operator/ (const double rhs) const
	{
		return Vector2(this->x / rhs, this->y / rhs);
	}
	
	Vector2& operator* (const double lhs, const Vector2& rhs)
	{
		return Vector2(rhs.x * lhs, rhs.y * lhs);
	}
	
	Vector2& operator/ (const double lhs, const Vector2& rhs)
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

	const double Vector2::GetMagnitude(void) const
	{
		return sqrt((this->x * this->x) + (this->y * this->y));
	}
}
