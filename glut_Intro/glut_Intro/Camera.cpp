#include "Camera.h"

void Camera::setRoationAngleX(float value)
{
	rotationAngleX = value;
	alignDirection();
}

void Camera::setRoationAngleY(float value)
{
	rotationAngleY = value;
	alignDirection();
}

Camera::Camera()
	: position(Vector3d::zero()), direction(Vector3d(0.0f, 0.0f, 1.0f)),
	upVector(Vector3d::up()), rotationAngleX(0), rotationAngleY(0)
{
	//Todo: use refactored Vector3d::forward()
}

void Camera::alignDirection()
{
	float pitch = MathHelper::convertToRad(rotationAngleX);
	float yaw = MathHelper::convertToRad(rotationAngleY);

	direction = Vector3d(
		-std::sin(yaw) * std::cos(pitch),
		std::sin(pitch),
		std::cos(yaw) * std::cos(pitch)
	);
}
