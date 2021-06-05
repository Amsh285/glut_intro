#pragma once

#include<cmath>

#include "MathHelper.h"
#include "Vector3d.h"

class Vector3dMatrix
{
	public:
		static Vector3dMatrix rotationX(const float& angle);
		static Vector3dMatrix rotationY(const float& angle);
		static Vector3dMatrix rotationZ(const float& angle);
		static Vector3dMatrix identity() { return Vector3dMatrix(Vector3d::right(), Vector3d::up(), Vector3d::back()); };

		Vector3dMatrix(Vector3d col1, Vector3d col2, Vector3d col3);

		Vector3d operator*(const Vector3d& other) const;
		Vector3dMatrix operator*(const float& value) const;
	private:
		Vector3d col1, col2, col3;
};

