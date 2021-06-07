#include "Vector3d.h"

Vector3d::Vector3d(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

Vector3d Vector3d::operator+(const Vector3d& other) const
{
	return Vector3d(x + other.x, y + other.y, z + other.z);
}

Vector3d Vector3d::operator-(const Vector3d& other) const
{
	return Vector3d(x - other.x, y - other.y, z - other.z);
}
