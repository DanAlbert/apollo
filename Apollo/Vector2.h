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
