#pragma once

#include <GL/glut.h>

#include <string>

#include "stb_image.h"

class stb_imageData
{
public:
	stb_imageData(GLuint textureName, const std::string& fileName);
	~stb_imageData();

	void bind();
	void unbind();
private:
	GLuint textureName;
	std::string fileName;
	int width, height, bitsPerPixel;
	unsigned char* imageBuffer;
};

