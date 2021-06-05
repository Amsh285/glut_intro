#pragma once

#include<stdexcept>
#include<vector>

#include "Vector3d.h"
#include "Vector3dMatrix.h"

class Geometry
{
public:
	static std::vector<Vector3d> rotateX(
		const std::vector<Vector3d>& source,
		const float& angle);

	static std::vector<Vector3d> rotateY(
		const std::vector<Vector3d>& source,
		const float& angle);

	static std::vector<Vector3d> rotateZ(
		const std::vector<Vector3d>& source,
		const float& angle);
private:
	static std::vector<Vector3d> rotate(
		const std::vector<Vector3d>& source,
		const Vector3dMatrix& rotationMatrix);
};

