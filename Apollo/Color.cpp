#include "Color.h"

namespace Apollo
{
	Color::Color(
			unsigned char r,
			unsigned char g,
			unsigned char b) :
				a(0xff),
				r(r),
				g(g),
				b(b)
	{
	}
	
	Color::Color(
			unsigned char a,
			unsigned char r,
			unsigned char g,
			unsigned char b) :
				a(a),
				r(r),
				g(g),
				b(b)
	{
	}

	const Color Color::Black(0, 0, 0);
	const Color Color::White(255, 255, 255);
	const Color Color::Red(255, 0, 0);
	const Color Color::Green(0, 255, 0);
	const Color Color::Blue(0, 0, 255);
	const Color Color::Yellow(255, 255, 0);
	const Color Color::Magenta(255, 0, 255);
	const Color Color::Cyan(0, 255, 255);
}
