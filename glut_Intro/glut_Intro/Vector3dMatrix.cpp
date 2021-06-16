#include "Vector3dMatrix.h"

Vector3dMatrix Vector3dMatrix::rotationX(const float& angle)
{
	float rad = MathHelper::convertToRad(angle);

	Vector3d col1 = Vector3d(1.0, 0.0, 0.0);
	Vector3d col2 = Vector3d(0.0, std::cos(rad), std::sin(rad));
	Vector3d col3 = Vector3d(0.0, -std::sin(rad), std::cos(rad));

	return Vector3dMatrix(col1, col2, col3);
}

Vector3dMatrix Vector3dMatrix::rotationY(const float& angle)
{
	float rad = MathHelper::convertToRad(angle);

	Vector3d col1 = Vector3d(std::cos(rad), 0.0, -std::sin(rad));
	Vector3d col2 = Vector3d(0.0, 1.0, 0.0);
	Vector3d col3 = Vector3d(std::sin(rad), 0.0, std::cos(rad));

	return Vector3dMatrix(col1, col2, col3);
}

Vector3dMatrix Vector3dMatrix::rotationZ(const float& angle)
{
	float rad = MathHelper::convertToRad(angle);

	Vector3d col1 = Vector3d(std::cos(rad), std::sin(rad), 0.0);
	Vector3d col2 = Vector3d(-std::sin(rad), std::cos(rad), 0.0);
	Vector3d col3 = Vector3d(0.0, 0.0, 1.0);

	return Vector3dMatrix(col1, col2, col3);
}

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
