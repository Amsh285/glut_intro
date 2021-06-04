#include "Vector3dMatrix.h"

Vector3dMatrix::Vector3dMatrix(Vector3d col1, Vector3d col2, Vector3d col3)
	: col1(col1), col2(col2), col3(col3)
{
}

Vector3d Vector3dMatrix::operator*(const Vector3d& other) const
{
	Vector3d v1 = other.X() * col1;
	Vector3d v2 = other.Y() * col2;
	Vector3d v3 = other.Z() * col3;

	return v1 + v2 + v3;
}

Vector3dMatrix Vector3dMatrix::operator*(const float& value) const
{
	return Vector3dMatrix(value * col1, value * col2, value * col3);
}
