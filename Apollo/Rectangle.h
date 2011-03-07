#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Apollo.h"

namespace Apollo
{
	struct APOLLO_API Rectangle
	{
		int x;
		int y;
		int width;
		int height;

		Rectangle(int x, int y, int width, int height);
	};
}

#endif // RECTANGLE_H