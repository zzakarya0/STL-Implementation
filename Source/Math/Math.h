#ifndef MATH_H
#define MATH_H

#include <math.h>

#include <stdbool.h>
#include <stdint.h>

#define DEBUG 0
#define EPSILON 0.0001f
#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct Point
	{
		float x, y, z;
	} Point;

	typedef struct Vector3
	{
		float x, y, z;
		float sqMagnitude;
	} Vector3;

	/*
		Also used to represent lines and rays
		2D: either parallel/collinear or interesecting
		2D < : parallel/collinear or intersecting or skew
	*/
	typedef struct LineSegment
	{
		Point* start;
		Point* end;
		Vector3* direction;
	} LineSegment;

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

	/*	Axis Aligned Bounding Box defined by:
			+ min and max points					
			. min point + diameter for each axis
			. center point + radius for each axis	(Most efficient space/memory wise)

		Notes:
			.Before testing for overlap convert into same coord system either world space or local space of other AABB 
	*/
	typedef struct AABB
	{
		Point* min;
		Point* max;
	}AABB;

	typedef struct OBB
	{
		Point center;	//center of OBB
		Vector3 u[3];	//local x,y,z axes
		Vector3 e;		//positive halfwidth extends of OBB along each axis
	}OBB;

	/*	Sphere equation: (x - a)^2 + (y - b)^2 + (c - z)^2 = r^2
	*		center = (a,b,c)
	*		radius = r
	*/
	typedef struct Sphere
	{
		Point* center;
		float r;
	}Sphere;

	typedef struct Triangle
	{
		Point* a, * b, * c;
	}Triangle;


	//////////////////// Struct Ctors //////////////////// 
	Vector3* CreateVector3(float x, float y, float z);
	Vector3* CreateVector3FromPoints(Point* from, Point* to);
	Plane* CreatePlane(const Point* const p1, const Point* const p2, const Point* const p3);
	LineSegment* CreateLineSegment(const Point* const start, const Point* const end);
	Triangle* CreateTriangle(const Point* const a, const Point* const b, const Point* const c);
	Sphere* CreateSphere(const Point* const center, float radius);

	//////////////////// Utility functions ////////////////////
	void PrintPoint(Point p);
	void PrintVector(const Vector3 v);
	void PrintPlane(const Plane* const plane);

	void Normalize(Vector3* const v);
	void NormalizePlane(Plane* plane);
	bool IsNormalized(const Vector3 v);
	//Barycentric Coord: P = A + v AB + w AC. If P within triangle ABC: 0 <= 1 - v - w  [0 <= v,w <= 1.f] 
	bool IsPointInTriangle(Point* p, Triangle* abc, float* v, float* w);
	//Return 0: Perpandicular, 1: Parallel/Collinear, 2: Otherwise
	uint8_t CheckVectors(Vector3* A, Vector3* B);
	//P: vector from projecting A over B. Dot(A,B) = |P| * |B|
	float Dot(const Vector3 v1, const Vector3 v2);
	Vector3* Cross(const Vector3* const v1, const Vector3* const v2);
	float SqDist(const Point* const A, const Point* const B);
	float SqMagnitude(const Vector3 v);
	//Projecting P over AB, Dist = Dot(AB, AP) / Magnitude(AB)
	float SqDistFromPointToSegment(Point p, LineSegment segment);
	float SqDistFromPointToAABB(Point* p, AABB* box);
	//Project P over plane normal
	float DistPointToPlane(Point p, Plane plane);

	//Check if a and b have same sign
	bool SameSign(float a, float b);

	/*float Cross2D(const Vector3* const v1, const Vector3* const v2);*/
	// Return 0: point on left, 1: point on right. Note: relative to line directiont in RHCS
	//uint8_t PointSideLine2D(Point* p, LineSegment* segment);


	//////////////////// Primitive intersection test ////////////////////
	//Return 1: Intersect, 0 otherwise
	bool SphereIntersect(Sphere* A, Sphere* B);
	//Return 1: Intersect, 0 otherwise
	bool AABBIntersect(AABB* box1, AABB* box2);


	//////////////////// Closest point tests ////////////////////
	//Make sure plane is normalized, P = (0,0,0) + plane.normal * plane.d
	void GetPointOnPlane(Plane plane, Point* p);
	/*Return if P's projection is within segment, if 0.f <= t <= 1.f projection falls within segment
	Same approach applies to Ray and Line, for Ray clamp if t < 0.f for Line no clamping needed*/
	bool ClosestPointOnSegmentToPoint(Point p, LineSegment segment, Point* closestPoint);
	//Project P over plane normal to get t distance btwn P and Plane, closestPoint = P - t * n
	void ClosestPointOnPlaneToPoint(Point p, Plane plane, Point* closestPoint);
	void ClosestPointInAABBToPoint(Point* p, AABB* box, Point* closestPoint);
	/*Project P over plane spawned by triangle, check if projection lies within triangle (Barycentric Coord)
	if yes then point found. Else Project P over all triangle segments and take closest one to P.*/
	void ClosestPointInTriangleToPoint(Point* p, Triangle* abc, Point* closestPoint);
	void ClosestPointsOf2Lines(const LineSegment* const lineA, const LineSegment* const lineB, Point* pA, Point* pB);
	//Intuuitive approach of going with closest point on lines then clipping to line segments is wrong
	//bool ClosestPointsOf2LineSegments(const LineSegment* const lineA, const LineSegment* const lineB, Point* pA, Point* pB);


	//////////////////// Testing primitives ////////////////////
	//Project sphere's center over plane normal to get distance between plane-sphere, then compare to sphere radius
	bool SphereIntersectPlane(const Sphere* const s, const Plane* const p);
	//Note: AABB/OBB extent is from center to vertex not the vertex
	//Consider L(t) = OBB.center + t * plane.n (line starting at C and going in same direction as plane normal), project one of furthest OBB vertices onto L(t) (onto n) to get distance
	//between C and that vertex (call it r). Project OBB.center onto n to get dst between center and plane (call it s) comapre s and r
	bool OBBIntersectPlane(OBB box, Plane p);
	bool AABBIntersectPlane(AABB box, Plane p);


#ifdef __cplusplus
} // extern "C"
#endif

#endif
