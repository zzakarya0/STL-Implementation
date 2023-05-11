#ifndef MATH_H
#define MATH_H

#include <math.h>

#include <stdbool.h>
#include <stdint.h>

#define DEBUG 0
#define EPSILON 0.0001
#ifdef __cplusplus
extern "C"
{
#endif

	bool SameSign(float a, float b);


	typedef struct Point
	{
		float x, y, z;
	} Point;
	void PrintPoint(Point p);


	typedef struct Vector3
	{
		float x, y, z;
		float sqMagnitude;
	} Vector3;
	// Ctor for Vector
	Vector3* CreateVector3(float x, float y, float z);
	void PrintVector(const Vector3 v);
	void Normalize(Vector3* const v);
	bool IsNormalized(const Vector3 v);
	float SqMagnitude(const Vector3 v);
	float Dot(const Vector3 v1, const Vector3 v2);
	Vector3* Cross(const Vector3* const v1, const Vector3* const v2);
	float Cross2D(const Vector3* const v1, const Vector3* const v2);
	// Return 0: Perpandicular, 1: Parallel/Collinear, 2: Otherwise
	uint8_t CheckVectors(Vector3* A, Vector3* B);


	typedef struct LineSegment
	{
		Point* start;
		Point* end;
		Vector3* direction;
	} LineSegment;
	// Ctor for line segment
	LineSegment* CreateLineSegment(const Point* const start, const Point* const end);
	// Return 0: point on left, 1: point on right. Note: relative to line directiont in RHCS
	uint8_t PointSideLine2D(Point* p, LineSegment* segment);
	/*Return if P's projection is within segment, if 0.f <= t <= 1.f projection falls within segment 
	Same approach applies to Ray and Line, for Ray clamp if t < 0.f for Line no clamping needed*/
	bool ClosestPointOnSegmentToPoint(Point p, LineSegment segment, Point* closestPoint);
	// Projecting P over AB, Dist = Dot(AB, AP) / Magnitude(AB)
	float SqDistFromPointToSegment(Point p, LineSegment segment);


	/*	Plane defined by:
			. distance from origin and normal vector
			or 3 non-colinear points
			or normal and point on plane

			Ax + By + Cz - d = 0
	*/
	typedef struct Plane
	{
		float d;
		Vector3* normal;
	} Plane;
	void NormalizePlane(Plane* plane);
	// Normalizing P so it isn't scalled by plane normal
	void GetPointOnPlane(Plane plane, Point* p);
	// Project P over plane normal to get t distance btwn P and Plane, closestPoint = P - t * n 
	void ClosestPointOnPlaneToPoint(Point p, Plane plane, Point* closestPoint);
	// Project P over plane normal
	float DistPointToPlane(Point p, Plane plane);


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
	void ClosestPointInAABBToPoint(Point* p, AABB* box, Point* closestPoint);
	float SqDistFromPointToAABB(Point* p, AABB* box);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
