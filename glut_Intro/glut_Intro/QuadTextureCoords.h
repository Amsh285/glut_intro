#pragma once

#include<utility>
#include<vector>

std::vector<std::pair<float, float>> quadTextureCoords = {
	// front face
	std::pair<float, float>(0.0f, 0.0f), std::pair<float, float>(1.0f, 0.0f),
	std::pair<float, float>(1.0f, 1.0f), std::pair<float, float>(0.0f, 1.0f),
	// right face
	std::pair<float, float>(1.0f, 0.0f), std::pair<float, float>(1.0f, 1.0f),
	std::pair<float, float>(0.0f, 1.0f), std::pair<float, float>(0.0f, 0.0f),
	// top face
	std::pair<float, float>(0.0f, 1.0f), std::pair<float, float>(0.0f, 0.0f),
	std::pair<float, float>(1.0f, 0.0f), std::pair<float, float>(1.0f, 1.0f),
	// back face
	std::pair<float, float>(1.0f, 0.0f), std::pair<float, float>(1.0f, 1.0f),
	std::pair<float, float>(0.0f, 1.0f), std::pair<float, float>(0.0f, 0.0f),
	// left face
	std::pair<float, float>(0.0f, 0.0f), std::pair<float, float>(1.0f, 0.0f),
	std::pair<float, float>(1.0f, 1.0f), std::pair<float, float>(0.0f, 1.0f),
	// bottom face
	std::pair<float, float>(1.0f, 1.0f), std::pair<float, float>(0.0f, 1.0f),
	std::pair<float, float>(0.0f, 0.0f), std::pair<float, float>(1.0f, 0.0f),
};
