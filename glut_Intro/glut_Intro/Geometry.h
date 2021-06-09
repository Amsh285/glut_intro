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

	static Vector3d rotateY(const Vector3d& target, const float& angle);

	static std::vector<Vector3d> rotateZ(
		const std::vector<Vector3d>& source,
		const float& angle);

	static std::vector<Vector3d> translate(
		const std::vector<Vector3d>& source,
		const Vector3d translationVector);

	Vector3d getPosition() const { return position; };
	void setPosition(Vector3d value);

	Vector3d getTranslationVector() const { return translationVector; };
private:
	static std::vector<Vector3d> rotate(
		const std::vector<Vector3d>& source,
		const Vector3dMatrix& rotationMatrix);

	Vector3d position = Vector3d::zero();
	Vector3d translationVector = Vector3d::zero();
protected:
	Vector3d atOrigin = Vector3d::zero();
};

