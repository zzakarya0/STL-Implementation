#include "Math.h"

#include <assert.h>
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

inline void SetBit(uint8_t bit, int32_t n) { n |= (1 << bit); }
inline void ClearBit(uint8_t bit, int32_t n) { n &= ~(1 << bit); }
inline void FlipBit(uint8_t bit, int32_t n) { n ^= (1 << bit); }
inline uint8_t CheckBit(uint8_t bit, int32_t n) { return (n >> bit) & 1; }
inline bool CheckMask(uint32_t mask, int32_t n) { return (n & mask) == mask; }
inline bool HasAnyFlags(int32_t flags, int32_t n) { return flags & n; }
inline bool HasAllFlagsSet(int32_t flags, int32_t n) { return (flags & n) == flags; }
inline int32_t EnableFlags(int32_t startingFlags, int32_t flagsToEnable) { return startingFlags | flagsToEnable; }
inline int32_t DisableFlags(int32_t startingFlags, int32_t flagsToDisable) { return startingFlags & (~flagsToDisable); }

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

Sphere* CreateSphere(const Point* const center, float radius)
{
	Sphere* s = malloc(sizeof(Sphere));

	*s = (Sphere){ .center = center, .r = radius };
	return s;
}

void PrintPoint(Point p)
{ 
	printf("Point(%f, %f, %f)\n", p.x, p.y, p.z); 
}

void PrintVector(const Vector3 v)
{
	printf("Vector(%f, %f, %f) with sqMagnitude = %f\n", v.x, v.y, v.z, v.sqMagnitude);
}

void PrintPlane(const Plane* const plane)
{
	printf("Plane normal: "); 
	PrintVector(*plane->normal);

	printf("Plane Dst from origin: %f\n", plane->d);
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

float SqDist(const Point* const A, const Point* const B)
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
	float sqDist = SqDist(aCenter, bCenter);

	float radii = A->r + B->r;
	return sqDist <= radii * radii;
}


Triangle* CreateTriangle(const Point* const a, const Point* const b, const Point* const c)
{
	Triangle* abc = malloc(sizeof(Triangle));

	abc->a = a;
	abc->b = b;
	abc->c = c;
	return abc;
}

Vector3* CreateVector3FromPoints(Point* from, Point* to)
{
	float x = to->x - from->x;
	float y = to->y - from->y;
	float z = to->z - from->z;

	Vector3* vec = CreateVector3(x, y, z);
	return vec;
}

Plane* CreatePlane(const Point* const p1, const Point* const p2, const Point* const p3)
{
	Vector3* v1 = CreateVector3FromPoints(p1, p2);
	Vector3* v2 = CreateVector3FromPoints(p2, p3);

	Vector3* n = Cross(v1, v2);
	Normalize(n);
	float d = n->x * p1->x + n->y * p1->y + n->z * p1->z;

	Plane* p = malloc(sizeof(Plane));
	*p = (Plane){ .d = d, .normal = n };

	free(v1);
	free(v2);
	return p;
}

bool IsPointInTriangle(Point* p, Triangle* abc, float* v, float* w)
{
	Vector3* AB = CreateVector3FromPoints(abc->a, abc->b), *AC = CreateVector3FromPoints(abc->a, abc->c);
	Vector3* AP = CreateVector3FromPoints(abc->a, p);

	// Barycentric Coord Eq: P - A = v(B - A) + w(C - A) --> AP = v AB + w AC	
	// Dot(AP, AB) = v Dot(AB, AB) + w Dot(AC, AB)
	// Dot(AP, AC) = v Dot(AB, AC) + w Dot(AC, AC)
	const float d00 = Dot(*AP, *AB), d01 = Dot(*AB, *AB), d02 = Dot(*AC, *AB);
	const float d10 = Dot(*AP, *AC), d11 = Dot(*AB, *AC), d12 = Dot(*AC, *AC);

	const float denom = d01 * d12 - d02 * d11;
	bool check = EPSILON <= denom || denom <= -EPSILON;
	//static_assert(check != 0);

	*v = (d00 * d12 - d10 * d02) / denom;
	*w = (d01 * d10 - d11 * d00) / denom;

	free(AB);
	free(AC);
	free(AP);
	return -EPSILON <= 1.f - *v - *w;
}

void ClosestPointInTriangleToPoint(Point* p, Triangle* abc, Point* closestPoint)
{
	// Get plane spawned by triangle
	const Point* A = abc->a, * B = abc->b, * C = abc->c;
	const Plane* trianglePlane = CreatePlane(A, B, C);
	
	// Project P over plane
	Point Q;
	ClosestPointOnPlaneToPoint(*p, *trianglePlane, &Q);

	// Check if Q falls within triangle
	float v, w;
	if (IsPointInTriangle(&Q, abc, &v, &w))
	{
		*closestPoint = (Point){ .x = Q.x, .y = Q.y, .z = Q.z };
		return;
	}

	LineSegment* AB = CreateLineSegment(A, B);
	LineSegment* BC = CreateLineSegment(B, C);
	LineSegment* CA = CreateLineSegment(C, A);

	Point p0, p1, p2;
	ClosestPointOnSegmentToPoint(*p, *AB, &p0);
	ClosestPointOnSegmentToPoint(*p, *BC, &p1);
	ClosestPointOnSegmentToPoint(*p, *CA, &p2);

	float d0 = SqDist(&p0, p);
	float d1 = SqDist(&p1, p);
	float d2 = SqDist(&p2, p);

	Point closest = (d0 < d1) ? ((d0 < d2) ? p0 : p2) : ((d1 < d2) ? p1 : p2);
	*closestPoint = (Point){ .x = closest.x, .y = closest.y, .z = closest.z };

	free(AB); 
	free(BC); 
	free(CA);
	free(trianglePlane);
}

void ClosestPointsOf2Lines(const LineSegment* const lineA, const LineSegment* const lineB, Point* pA, Point* pB)
{
	//v = pA - pB
	//Dot(v, DirA) = 0	--> ((startA + x DirA) - (startB + y DirB)) . DirA = 0
	//Dot(v, DirB) = 0	--> ((startA + x DirA) - (startB + y DirB)) . DirB = 0

	const LineSegment* const BA = CreateLineSegment(lineB->start, lineA->start);
	Vector3* dirA = lineA->direction, * dirB = lineB->direction, *dir = BA->direction;

	float dAA = Dot(*dirA, *dirA), dAB = Dot(*dirA, *dirB), dBB = Dot(*dirB, *dirB);
	float dA = Dot(*dir, *dirA), dB = Dot(*dir, *dirB);

	float cramer = dAA * dBB - (dAB * dAB);
	assert(cramer != 0);

	float x = (-dA * dBB + (dB * dAB)) / cramer, y = (dAA * dB - (dA * dAB)) / cramer;

	Point* startA = lineA->start;
	*pA = (Point){ .x = startA->x + x * dirA->x, .y = startA->y + x * dirA->y, .z = startA->z + x * dirA->z};

	Point* startB = lineB->start;
	*pB = (Point){ .x = startB->x + y * dirB->x, .y = startB->y + y * dirB->y, .z = startB->z + y * dirB->z };

	free(BA);
}

//bool ClosestPointsOf2LineSegments(const LineSegment* const lineA, const LineSegment* const lineB, Point* pA, Point* pB)
//{
//	const LineSegment* const BA = CreateLineSegment(lineB->start, lineA->start);
//	Vector3* dirA = lineA->direction, * dirB = lineB->direction, * dir = BA->direction;
//
//	float dAA = Dot(*dirA, *dirA), dAB = Dot(*dirA, *dirB), dBB = Dot(*dirB, *dirB);
//	float dA = Dot(*dir, *dirA), dB = Dot(*dir, *dirB);
//
//	float cramer = dAA * dBB - (dAB * dAB);
//	assert(cramer != 0);
//
//	float x = (-dA * dBB + (dB * dAB)) / cramer, y = (dAA * dB - (dA * dAB)) / cramer;
//
//	bool withinSegments = false;
//	if (-EPSILON <= x && x <= 1.f + EPSILON && -EPSILON <= y && y <= 1.f + EPSILON) withinSegments = true;
//	
//	else {
//		if (EPSILON >= x || x >= 1.f + EPSILON) x = x <= EPSILON ? 0 : 1.f;
//		if (EPSILON >= y || y >= 1.f + EPSILON) y = y <= EPSILON ? 0 : 1.f;
//	}
//
//	Point* startA = lineA->start;
//	*pA = (Point){ .x = startA->x + x * dirA->x, .y = startA->y + x * dirA->y, .z = startA->z + x * dirA->z };
//
//	Point* startB = lineB->start;
//	*pB = (Point){ .x = startB->x + y * dirB->x, .y = startB->y + y * dirB->y, .z = startB->z + y * dirB->z };
//
//	free(BA);
//	return withinSegments;
//}

bool SphereIntersectPlane(const Sphere* const s, Plane* const p)
{
	Vector3* n = p->normal;
	if (!IsNormalized(*n)) NormalizePlane(p);

	float dist = DistPointToPlane(*s->center, *p);
	return fabs(dist) <= s->r;
}

bool OBBIntersectPlane(OBB box, Plane p)
{
	//Project OBB furthest vertex  onto plane.n
	Point center = { box.center.x, box.center.y, box.center.z};
	Point e0 = { box.u[0].x * box.e.x, box.u[0].y * box.e.x, box.u[0].z * box.e.x };
	Point e1 = { box.u[1].x * box.e.y, box.u[1].y * box.e.y, box.u[1].z * box.e.y };
	Point e2 = { box.u[2].x * box.e.z, box.u[2].y * box.e.z, box.u[2].z * box.e.z };

	Point vertex = { center.x + e0.x + e1.x + e2.x, center.y + e0.y + e1.y + e2.y, center.z + e0.z + e1.z + e2.z };
	Vector3 centerToVertex = { vertex.x - center.x, vertex.y - center.y, vertex.z - center.z };

	Vector3* n = p.normal;
	if (!IsNormalized(*n)) NormalizePlane(&p);
	float vertexCenterDst = fabsf(Dot(centerToVertex, *n));

	//Project OBB.center over n
	Point Q;
	GetPointOnPlane(p, &Q);
	Vector3* QC = CreateVector3FromPoints(&Q, &center);
	float centerPlaneDst = Dot(*QC, *n);

	return fabsf(centerPlaneDst) <= vertexCenterDst;
}

bool AABBIntersectPlane(AABB box, Plane p)
{
	Point center = { (box.min->x + box.max->x) / 2, (box.min->y + box.max->y) / 2, (box.min->z + box.max->z) / 2 };
	Vector3 centerToVertex = { box.max->x - center.x, box.max->y - center.y, box.max->z - center.z };

	Vector3* n = p.normal;
	if (!IsNormalized(*n)) NormalizePlane(&p);
	float vertexCenterDst = fabsf(Dot(centerToVertex, *n));

	Point Q;
	GetPointOnPlane(p, &Q);
	Vector3* QC = CreateVector3FromPoints(&Q, &center);
	float centerPlaneDst = Dot(*QC, *n);

	return fabsf(centerPlaneDst) <= vertexCenterDst;
}