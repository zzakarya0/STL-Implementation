#include "Math.h"

#include <stdlib.h>
#include <stdio.h>

#define debug 1

bool SameSign(float a, float b)
{
	__int32 flag = 0x80000000;
	__int32 a0 = a;
	__int32 b0 = b;
	
	flag = flag ^ a0  ^ b0;
	return flag < 0;
}

inline float SqMagnitude(const Vector3* const v)
{
	float x = v->x;
	float y = v->y;
	float z = v->z;
	return x * x + y * y + z * z;
}

//Vector3* Normalize(const Vector3* const v)
//{
//	Vector3* normalized = (Vector3*) malloc(sizeof(Vector3));
//	const float magnitude = Magnitude(v);
//
//	*normalized = { .x = (v->x/magnitude), .y = (v->y/magnitude), .z = (v->z/magnitude) };
//	return normalized;
//}

inline float Dot(const Vector3* const v1, const Vector3* const v2)
{
	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

inline Vector3* Cross(const Vector3* const v1, const Vector3* const v2)
{
	Vector3* result = (Vector3*) malloc(sizeof(Vector3));

	result->x = v1->y * v2->z - v2->y * v1->z;
	result->y = -(v1->x * v2->z - v2->x * v1->z);
	result->z = v1->x * v2->y - v2->x * v1->y;
	return result;
}

void ClosestPointInAABBToPoint(Point* P, AABB* Box, Point* ClosestPoint)
{
	// Get X component
	ClosestPoint->x = fmax(P->x, Box->minPoints[0]);
	ClosestPoint->x = fmin(ClosestPoint->x, Box->maxPoints[0]);
	// Get Y component
	ClosestPoint->y = fmax(P->y, Box->minPoints[1]);
	ClosestPoint->y = fmin(ClosestPoint->y, Box->maxPoints[1]);
	// Get Z component
	ClosestPoint->z = fmax(P->z, Box->minPoints[2]);
	ClosestPoint->z = fmin(ClosestPoint->z, Box->maxPoints[2]);

	if (debug) printf("closest point: (%f, %f, %f)\n", ClosestPoint->x, ClosestPoint->y, ClosestPoint->z);
}

float SqDistFromPointToAABB(Point* P, AABB* Box)
{
	float sqDist = 0.f;

	float x = P->x;
	if (x < Box->minPoints[0]) sqDist += (x - Box->minPoints[0]) * (x - Box->minPoints[0]);
	else if (Box->maxPoints[0] < x) sqDist += (x - Box->maxPoints[0]) * (x - Box->maxPoints[0]);

	float y = P->y;
	if (y < Box->minPoints[1]) sqDist += (y - Box->minPoints[1]) * (y - Box->minPoints[1]);
	else if (Box->maxPoints[1] < y) sqDist += (y - Box->maxPoints[1]) * (y - Box->maxPoints[1]);

	float z = P->z;
	if (z < Box->minPoints[2]) sqDist += (z - Box->minPoints[2]) * (z - Box->minPoints[2]);
	else if (Box->maxPoints[2] < z) sqDist += (z - Box->maxPoints[2]) * (z - Box->maxPoints[2]);

	if (debug) {
		Point Q;
		ClosestPointInAABBToPoint(P, Box, &Q);
		printf("SqDist between (%f, %f, %f) and (%f, %f, %f) = %f\n", x, y, z, Q.x, Q.y, Q.z, sqDist);
	}
	return sqDist;
}