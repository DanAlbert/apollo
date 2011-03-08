#ifndef COLOR_H
#define COLOR_H

#include "Apollo.h"

namespace Apollo
{
	class APOLLO_API Color
	{
	public:
		unsigned char a;
		unsigned char r;
		unsigned char g;
		unsigned char b;

		Color(
			unsigned char r,
			unsigned char g,
			unsigned char b);

		Color(
			unsigned char a,
			unsigned char r,
			unsigned char g,
			unsigned char b);

		static const Color Black;
		static const Color White;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Magenta;
		static const Color Cyan;
	};
}

#endif // COLOR_H