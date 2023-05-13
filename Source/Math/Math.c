#include "Math.h"

#include <stdio.h>
#include <stdlib.h>


bool SameSign(float a, float b)
{
	__int32 flag = 0x80000000;
	__int32 a0 = a;
	__int32 b0 = b;
	
	flag = flag ^ a0  ^ b0;
	return flag < 0;
}

Vector3* CreateVector3(float x, float y, float z)
{
	Vector3* vector = malloc(sizeof(Vector3));

	*vector = (Vector3){ .x = x, .y = y, .z = z, .sqMagnitude = x * x + y * y + z * z };
	return vector;
}

LineSegment* CreateLineSegment(const Point* const start, const Point* const end)
{
	LineSegment* segment = malloc(sizeof(LineSegment));

	*segment = (LineSegment){ .start = start, .end = end, .direction = CreateVector3(end->x - start->x, end->y - start->y, end->z - start->z) };
	return segment;
}

void PrintPoint(Point p)
{ 
	printf("Point(%f, %f, %f)\n", p.x, p.y, p.z); 
}

void PrintVector(const Vector3 v)
{
	printf("Vector(%f, %f, %f) with sqMagnitude = %f\n", v.x, v.y, v.z, v.sqMagnitude);
}

float Cross2D(const Vector3* const v1, const Vector3* const v2)
{
	return v1->x * v2->y - v2->x * v1->y;
}

uint8_t PointSideLine2D(Point* p, LineSegment* segment)
{
	Vector3* lineToPoint = CreateVector3(p->x - segment->start->x, p->y - segment->start->y, p->z - segment->start->z);

	float crossRes = Cross2D(segment->direction, lineToPoint);

	if (0 < crossRes) return 0;
	else if (crossRes < 0) return 1;
	return 2;
}

uint8_t CheckVectors(Vector3* A, Vector3* B)
{
	if (Dot(*A, *B) == 0) return 0;
	
	Vector3* AxB = Cross(A, B);
	float sqArea = SqMagnitude(*AxB);
	if (-EPSILON <= sqArea && sqArea <= EPSILON) return 1;

	return 2;
}

float GetSqDist(const Point* const A, const Point* const B)
{
	float x = A->x - B->x;
	float y = A->y - B->y;
	float z = A->z - B->z;
	return x * x + y * y + z * z;
}

void Normalize(Vector3* const v)
{
	float sqMagnitude = SqMagnitude(*v);

	v->x = v->x / sqrtf(sqMagnitude);
	v->y = v->y / sqrtf(sqMagnitude);
	v->z = v->z / sqrtf(sqMagnitude);

	if (DEBUG) printf("Normalized vector(%f, %f, %f)\n", v->x, v->y, v->z);
}

inline bool IsNormalized(const Vector3 v)
{
	double result = 1.0f - (v.x + v.y + v.z);
	return fabs(result) <= EPSILON;
}

inline float SqMagnitude(const Vector3 v)
{
	float x = v.x;
	float y = v.y;
	float z = v.z;
	return x * x + y * y + z * z;
}

inline float Dot(const Vector3 v1, const Vector3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3* Cross(const Vector3* const v1, const Vector3* const v2)
{
	Vector3* result = malloc(sizeof(Vector3));

	result->x = v1->y * v2->z - v2->y * v1->z;
	result->y = -(v1->x * v2->z - v2->x * v1->z);
	result->z = v1->x * v2->y - v2->x * v1->y;
	return result;
}

bool ClosestPointOnSegmentToPoint(Point p, LineSegment segment, Point* closestPoint)
{
	Point* A = segment.start, *B = segment.end;
	Vector3 AP = { p.x - A->x, p.y - A->y, p.z - A->z };
	Vector3 AB = { B->x - A->x, B->y - A->y, B->z - A->z };

	float t = Dot(AP, AB) / Dot(AB, AB);

	bool isWithinSegment = 0.f - EPSILON <= t && t <= 1.f + EPSILON;
	if (t < 0.f) t = 0.f;
	else if (1.f < t) t = 1.f;
	
	*closestPoint = (Point) { .x = A->x + t * AB.x, .y = A->y + t * AB.y, .z = A->z + t * AB.z };
	return  isWithinSegment;
}

float SqDistFromPointToSegment(Point p, LineSegment segment)
{
	Point* A = segment.start, * B = segment.end;
	Vector3 AP = { p.x - A->x, p.y - A->y, p.z - A->z };
	Vector3 AB = { B->x - A->x, B->y - A->y, B->z - A->z };

	float t = Dot(AP, AB);
	if (t < 0.f) return Dot(AP, AP);

	float denom = Dot(AB, AB);
	if (t >= denom + EPSILON) 
	{
		Vector3 BP = { p.x - B->x, p.y - B->y, p.z - B->z };
		return Dot(BP, BP);
	}

	return Dot(AP, AP) - (t * t / denom) ;
}

void NormalizePlane(Plane* plane)
{
	Vector3* n = plane->normal;
	float N_sqMagnitude = SqMagnitude(*n);

	plane->d = plane->d / sqrtf(N_sqMagnitude);
	Normalize(n);
}

void GetPointOnPlane(Plane plane, Point* p)
{
	Vector3* n = plane.normal;
	if (!IsNormalized(*n)) NormalizePlane(&plane);

	*p = (Point) { .x = n->x * plane.d, .y = n->y * plane.d, .z = n->z * plane.d };
}

void ClosestPointOnPlaneToPoint(Point p, Plane plane, Point* closestPoint)
{
	Vector3* n = plane.normal;
	if (!IsNormalized(*n)) NormalizePlane(&plane);

	Point q;
	GetPointOnPlane(plane, &q);
	
	Vector3 QP = { p.x - q.x, p.y - q.y, p.z - q.z };
	float t = Dot(*n, QP);
	
	*closestPoint = (Point) { .x = p.x - t * n->x, .y = p.y - t * n->y,  .z = p.z - t * n->z };
}

float DistPointToPlane(Point p, Plane plane)
{
	Vector3* n = plane.normal;
	if (!IsNormalized(*n)) NormalizePlane(&plane);

	Point q;
	GetPointOnPlane(plane, &q);

	Vector3 qp = { p.x - q.x, p.y - q.y, p.z - q.z };
	return Dot(*n, qp);
}

bool AABBIntersect(AABB* A, AABB* B)
{
	Point* minA = A->min, * maxA = A->max;
	Point* minB = B->min, * maxB = B->max;

	if (maxA->x < minB->x || maxB->x < minA->x) return 0;
	if (maxA->y < minB->y || maxB->y < minA->y) return 0;
	if (maxA->z < minB->z || maxB->z < minA->z) return 0;

	return 1;
}

void ClosestPointInAABBToPoint(Point* p, AABB* box, Point* closestPoint)
{
	Point* min = box->min, * max = box->max;

	// Get X component
	closestPoint->x = fmax(p->x, min->x);
	closestPoint->x = fmin(closestPoint->x, max->x);
	// Get Y component
	closestPoint->y = fmax(p->y, min->y);
	closestPoint->y = fmin(closestPoint->y, max->y);
	// Get Z component
	closestPoint->z = fmax(p->z, min->z);
	closestPoint->z = fmin(closestPoint->z, max->z);

	if (DEBUG) printf("closest point: (%f, %f, %f)\n", closestPoint->x, closestPoint->y, closestPoint->z);
}

float SqDistFromPointToAABB(Point* p, AABB* box)
{
	Point* min = box->min, * max = box->max;
	float sqDist = 0.f;

	float x = p->x;
	if (x < min->x) sqDist += (x - min->x) * (x - min->x);
	else if (max->x < x) sqDist += (x - max->x) * (x - max->x);

	float y = p->y;
	if (y < min->y) sqDist += (y - min->y) * (y - min->y);
	else if (max->y < y) sqDist += (y - max->y) * (y - max->y);

	float z = p->z;
	if (z < min->z) sqDist += (z - min->z) * (z - min->z);
	else if (max->z < z) sqDist += (z - max->z) * (z - max->z);

	if (DEBUG) {
		Point Q;
		ClosestPointInAABBToPoint(p, box, &Q);
		printf("SqDist between (%f, %f, %f) and (%f, %f, %f) = %f\n", x, y, z, Q.x, Q.y, Q.z, sqDist);
	}
	return sqDist;
}

bool SphereIntersect(Sphere* A, Sphere* B)
{
	Point* aCenter = A->center, *bCenter = B->center;
	float sqDist = GetSqDist(aCenter, bCenter);

	float radii = A->r + B->r;
	return sqDist <= radii * radii;
}