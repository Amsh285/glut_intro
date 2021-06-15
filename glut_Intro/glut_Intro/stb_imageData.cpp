#include "stb_imageData.h"

stb_imageData::stb_imageData(GLuint textureName, const std::string& fileName)
	: textureName(textureName), fileName(fileName), width(0), height(0), bitsPerPixel(0), imageBuffer(nullptr)
{
	stbi_set_flip_vertically_on_load(1);
	imageBuffer = stbi_load(fileName.c_str(), &width, &height, &bitsPerPixel, 4);

	//new
	/*glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	https://stackoverflow.com/questions/5681948/multiple-textures-opengl-glut-c/5682082 ist ein versuch wert.
	*/

	glBindTexture(GL_TEXTURE_2D, textureName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageBuffer);
	/*glBindTexture(GL_TEXTURE_2D, 0);*/
}

stb_imageData::~stb_imageData()
{
	if(imageBuffer != nullptr)
		delete imageBuffer;

	glDeleteTextures(1, &textureName);
}

void stb_imageData::bind()
{
	glBindTexture(GL_TEXTURE_2D, textureName);
}

void stb_imageData::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
