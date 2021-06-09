#include "Camera.h"

void Camera::setRotationAngleX(float value)
{
	rotationAngleX = value;
	alignDirection();
}

void Camera::setRotationAngleY(float value)
{
	rotationAngleY = value;
	alignDirection();
}

void Camera::setAngles(float rotationX, float rotationY)
{
	rotationAngleX = rotationX;
	rotationAngleY = rotationY;

	alignDirection();
}

Camera::Camera()
	: position(Vector3d::zero()), direction(Vector3d::forward()),
	upVector(Vector3d::up()), rotationAngleX(0), rotationAngleY(0)
{
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
