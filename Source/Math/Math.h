#ifndef MATH_H
#define MATH_H

#include <math.h>

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

	bool SameSign(float a, float b);

	typedef struct Point
	{
		float x, y, z;
	} Point;

	/*	Vector3 defined by start and end points*/
	typedef struct Vector3
	{
		float x, y, z;
	} Vector3;
	float SqMagnitude(const Vector3* const v);
	Vector3* Normalize(const Vector3* const v);
	float Dot(const Vector3* const v1, const Vector3* const v2);
	Vector3* Cross(const Vector3* const v1, const Vector3* const v2);


	/*	Plane defined by:
			. distance from origin and normal vector
			or 3 non-colinear points
			or normal and point on plane
	*/
	typedef struct Plane
	{
		Point* d;
		Vector3* normal;
	} Plane;


	/*	Axis Aligned Bounding Box defined by
		min and max points in each axis	 [x, y, z]

		Y-axis	^		.---------------.
				|		|				|
				|		|				|
				|		.---------------.
				0-----------------------------> X-axis
	*/
	typedef struct AABB
	{
		float minPoints[3];
		float maxPoints[3];
	}AABB;
	void ClosestPointInAABBToPoint(Point* P, AABB* Box, Point* ClosestPoint);
	// Otherwise could find closest point and then get the dist
	float SqDistFromPointToAABB(Point* P, AABB* Box);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
