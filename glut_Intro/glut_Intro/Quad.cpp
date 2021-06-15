#include "Quad.h"

Quad::Quad()
	: Quad(1.0, 1.0, 1.0)
{
}

Quad::Quad(float width, float height, float depth)
	: width(width), height(height), depth(depth)
{
	//todo: check negative Values and 0

	Vector3d identityX = Vector3d(-1.0f, 0.0f, 0.0f);
	Vector3d identityY = Vector3d(0.0f, -1.0f, 0.0f);
	Vector3d identityZ = Vector3d(0.0f, 0.0f, -1.0f);

	Vector3dMatrix reflectionMatrix = Vector3dMatrix(identityX, identityY, identityZ);
	atOrigin = reflectionMatrix * fulcrum();
}

std::vector<Vector3d> Quad::getQuadVertices()
{
	std::vector<Vector3d> quadVertices;

	//front
	Vector3d frontRightBottom = atOrigin + width * Vector3d::forward();
	Vector3d frontRightTop = frontRightBottom + height * Vector3d::up();
	Vector3d frontLeftTop = frontRightTop + width * Vector3d::back();

	//Die Reihenfolge spielt eine Rolle
	//links unten, rechts unten, rechts oben, links oben
	quadVertices.push_back(atOrigin);
	quadVertices.push_back(frontRightBottom);
	quadVertices.push_back(frontRightTop);
	quadVertices.push_back(frontLeftTop);

	//right side
	Vector3d backRightBottom = frontRightBottom + depth * Vector3d::right();
	Vector3d backRightTop = backRightBottom + height * Vector3d::up();
 
	quadVertices.push_back(frontRightBottom);
	quadVertices.push_back(backRightBottom);
	quadVertices.push_back(backRightTop);
	quadVertices.push_back(frontRightTop);

	//upside
	Vector3d backLeftTop = backRightTop + width * Vector3d::back();

	quadVertices.push_back(frontLeftTop);
	quadVertices.push_back(frontRightTop);
	quadVertices.push_back(backRightTop);
	quadVertices.push_back(backLeftTop);

	//backside
	Vector3d backLeftBottom = backLeftTop + height * Vector3d::down();

	quadVertices.push_back(backLeftBottom);
	quadVertices.push_back(backRightBottom);
	quadVertices.push_back(backRightTop);
	quadVertices.push_back(backLeftTop);

	//left side
	quadVertices.push_back(atOrigin);
	quadVertices.push_back(backLeftBottom);
	quadVertices.push_back(backLeftTop);
	quadVertices.push_back(frontLeftTop);

	//downside
	quadVertices.push_back(atOrigin);
	quadVertices.push_back(frontRightBottom);
	quadVertices.push_back(backRightBottom);
	quadVertices.push_back(backLeftBottom);

	return quadVertices;
}


