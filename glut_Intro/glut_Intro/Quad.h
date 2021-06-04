#pragma once

#include<stdexcept>
#include<vector>

#include "Vector3d.h"
#include "Vector3dMatrix.h"

class Quad
{
	public:
		Quad();
		Quad(float width, float height, float depth);

		Vector3d fulcrum() { return 0.5 * Vector3d(width, height, depth); };

		std::vector<Vector3d> getQuadVertices();
	private:
		float width;
		float height;
		float depth;

		Vector3d atOrigin = Vector3d::zero();
};

