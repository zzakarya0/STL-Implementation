#include "Source/Math/Math.h"


int main()
{
	/*float f1 = -10.34;
	float f2 = 123.321;

	printf("1 if same sign, 0 otherwise: %d\n", SameSign(f1, f2));*/

	AABB box = { {-1, 2, -5}, {10, 6, 10} };
	Point P(-1, 1, -6);
	Point Q;

	//ClosestPointInAABBToPoint(&P, &box, &Q);

	SqDistFromPointToAABB(&P, &box);

	return 0;
}