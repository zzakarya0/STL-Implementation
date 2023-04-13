#ifndef MATH_H
#define MATH_H

#include <math.h>

typedef struct Point
{
	float x, y, z;
} Point;

//Point* NewPoint(float X, float Y, float Z);
//Point* CopyPoint(Point* p);

/*	Vector3 defined by start and end points*/
typedef struct Vector3 
{
	float x, y, z;
} Vector3;

//Vector3* NewVector(Point* start, Point* end);
//Vector3* CopyVector(Vector3* vec);

float Magnitude(const Vector3* const v);
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









#endif
