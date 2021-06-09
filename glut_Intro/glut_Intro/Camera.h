#pragma once
#include <cmath>

#include "MathHelper.h"
#include "Vector3d.h"

class Camera
{
public:
	Vector3d getPosition() const { return position; };
	void setPosition(Vector3d value) { position = value; };

	Vector3d getDirection() const { return direction; };

	Vector3d getUpVector() const { return upVector; };

	float getRotationAngleX() const { return rotationAngleX; };
	void setRotationAngleX(float value);

	float getRotationAngleY() const { return rotationAngleY; };
	void setRotationAngleY(float value);

	void setAngles(float rotationX, float rotationY);

	Camera();
private:
	void alignDirection();

	Vector3d position;
	Vector3d direction;
	Vector3d upVector;

	float rotationAngleX, rotationAngleY;
};

