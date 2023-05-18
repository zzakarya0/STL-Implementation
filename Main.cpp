#include "Source/Math/Math.h"
#include <cstdio>

int main()
{
	Point a(-4,0,5), b(4, 0, 3), c(1, 6, 10);
	Triangle* abc = CreateTriangle(&a, &b, &c);

	Point p(0, 6, 7), Q;
	ClosestPointInTriangleToPoint(&p, abc, &Q);
	PrintPoint(Q);

	float v, w;
	std::printf("In Triangle: %d \n", IsPointInTriangle(&Q, abc, &v, &w));
	
	return 0;
}