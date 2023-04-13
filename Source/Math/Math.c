#include "Math.h"


inline float Magnitude(const Vector3* const v)
{
	float x = v->x;
	float y = v->y;
	float z = v->z;
	return sqrt(x * x + y * y + z * z);
}

inline float SqMagnitude(const Vector3* const v)
{
	float x = v->x;
	float y = v->y;
	float z = v->z;
	return x * x + y * y + z * z;
}

Vector3* Normalize(const Vector3* const v)
{
	Vector3* normalized = malloc(sizeof(Vector3));
	const float magnitude = Magnitude(v);

	*normalized = (Vector3) { .x = (v->x/magnitude), .y = (v->y/magnitude), .z = (v->z/magnitude) };
	return normalized;
}

inline float Dot(const Vector3* const v1, const Vector3* const v2)
{
	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

inline Vector3* Cross(const Vector3* const v1, const Vector3* const v2)
{
	Vector3* result = malloc(sizeof(Vector3));

	result->x = v1->y * v2->z - v2->y * v1->z;
	result->y = -(v1->x * v2->z - v2->x * v1->z);
	result->z = v1->x * v2->y - v2->x * v1->y;
	return result;
}