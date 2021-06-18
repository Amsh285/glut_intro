#include <iostream>
#include <stdlib.h>

#include <GL/glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>  

#include "Camera.h"
#include "Geometry.h"
#include "Quad.h"
#include "Vector3d.h"
#include "Vector3dMatrix.h"

#include "stb_image.h"
#include "stb_imageData.h"

#include "QuadTextureCoords.h"

const int width = 1024;
const int height = 768;

Camera* camera = nullptr;
Quad* testQuad = nullptr;
Quad* texturedTestQuad = nullptr;
Quad* skyQuad = nullptr;
Quad* animatedQuad = nullptr;

stb_imageData* texture = nullptr;
stb_imageData* skyTexture = nullptr;
stb_imageData* animatedCubeTexture = nullptr;

float animationRotationY = 0.0f;

int downX;
int downY;

const std::pair<float, float> thresholdDeltaY(30.0f, -30.0f);
const std::pair<float, float> thresholdDeltaX(30.0f, -30.0f);

void timerFunc(int id)
{
	/*std::cout << "timer ID: " << id << std::endl;*/

	animationRotationY = std::fmod(animationRotationY + 1.0f, 360);

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, &timerFunc, id);
}

void onClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT)
	{
		switch (state)
		{
			case GLUT_DOWN:
			{
				downX = x;
				downY = y;
				break;
			}
			case GLUT_UP:
			{
				int deltaY = x - downX;
				int deltaX = downY - y;

				bool insideYThreshold = deltaY <= thresholdDeltaY.first && deltaY >= thresholdDeltaY.second;
				bool insideXThreshold = deltaX <= thresholdDeltaX.first && deltaX >= thresholdDeltaX.second;

				if (insideYThreshold)
					deltaY = 0;

				if (insideXThreshold)
					deltaX = 0;

				float ratioY = width / 90;
				float ratioX = height / 60;

				float angleY = std::fmod(camera->getRotationAngleY() + deltaY / ratioY, 360.0f);
				float angleX = camera->getRotationAngleX() + deltaX / ratioX;

				if (angleX > 90.0f)
					angleX = 90.0f;
				else if (angleX < -90.0f)
					angleX = -90.0f;

				std::cout << "Pitch: " << std::to_string(angleX) << " - Yaw: " << std::to_string(angleY) << std::endl;

				//Todo: muss man beim ändern des Winkels einen neuen upvektor berechnen?
				camera->setAngles(angleX, angleY);
				glutPostRedisplay();
				break;
			}
			default:
				break;
		}
	}
}

void onKeyPressed(unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		Vector3d newCameraPosition = camera->getPosition() + camera->getDirection();
		camera->setPosition(newCameraPosition);
		glutPostRedisplay();
	}
	else if (key == 's')
	{
		Vector3d newCameraPosition = camera->getPosition() + -1.0f * camera->getDirection();
		camera->setPosition(newCameraPosition);
		glutPostRedisplay();
	}
	else if (key == 'z')
	{
		camera->setPosition(Vector3d(0.0f, 0.0f, 0.0f));
		camera->setAngles(0.0f, 0.0f);
		glutPostRedisplay();
	}

	Vector3d cameraPosition = camera->getPosition();
	std::cout << "New Camera Position: (" << cameraPosition.X() << ", " << cameraPosition.Y() << ", " << cameraPosition.Z() << ")" << std::endl;
}

void resize(int width, int height)
{
	if (height == 0)
		height = 1;

	glViewport(0, 0, width, height);

	// Wechsel auf den Projektionsmatrix- stack
	glMatrixMode(GL_PROJECTION);

	// Initialisieren mit der Einheitsmatrix
	glLoadIdentity();

	// Anpassung des Frustum an den neuen Aspect ratio von Resize(width, height)
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	// Wieder auf den Modelview stack wechseln
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	// Bereinigen des Color buffers und des depth buffers mit glClear()
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Initialisierung des Matrixstacks
	glLoadIdentity();

	Vector3d position = camera->getPosition();
	Vector3d direction = camera->getPosition() + camera->getDirection();

	// Sollte man den anpassen wenn pitch sich ändert?
	Vector3d upVector = camera->getUpVector();

	gluLookAt(position.X(), position.Y(), position.Z(),
		direction.X(), direction.Y(), direction.Z(),
		upVector.X(), upVector.Y(), upVector.Z()
	);

	glBegin(GL_QUADS);

	std::vector<Vector3d> quadVertices = testQuad->getQuadVertices();

	quadVertices = Geometry::rotateY(quadVertices, 45.0f);
	quadVertices = Geometry::rotateX(quadVertices, 45.0f);
	quadVertices = Geometry::translate(quadVertices, testQuad->getTranslationVector());

	for (size_t i = 0; i < quadVertices.size(); i++)
	{
		Vector3d vertex = quadVertices[i];
		glVertex3f(vertex.X(), vertex.Y(), vertex.Z());
	}

	glEnd();

	glEnable(GL_TEXTURE_2D);

	if (texture != nullptr)
		texture->bind();

	glBegin(GL_QUADS);

	std::vector<Vector3d> texQuadVertices = texturedTestQuad->getQuadVertices();
	texQuadVertices = Geometry::translate(texQuadVertices, texturedTestQuad->getTranslationVector());

	for (size_t i = 0; i < texQuadVertices.size(); i++)
	{
		Vector3d vertex = texQuadVertices[i];
		std::pair<float, float> textureCoord = quadTextureCoords[i];

		glTexCoord2f(textureCoord.first, textureCoord.second);
		glVertex3f(vertex.X(), vertex.Y(), vertex.Z());
	}

	glEnd();

	std::vector<Vector3d> skyQuadVertices = skyQuad->getQuadVertices();
	skyQuadVertices = Geometry::translate(skyQuadVertices, skyQuad->getTranslationVector());

	if (skyTexture != nullptr)
		skyTexture->bind();

	glBegin(GL_QUADS);

	for (size_t i = 0; i < skyQuadVertices.size(); i++)
	{
		Vector3d vertex = skyQuadVertices[i];
		std::pair<float, float> textureCoord = quadTextureCoords[i];

		glTexCoord2f(textureCoord.first, textureCoord.second);
		glVertex3f(vertex.X(), vertex.Y(), vertex.Z());
	}

	glEnd();

	std::vector<Vector3d> animatedQuadVertices = animatedQuad->getQuadVertices();
	animatedQuadVertices = Geometry::rotateY(animatedQuadVertices, animationRotationY);
	animatedQuadVertices = Geometry::translate(animatedQuadVertices, animatedQuad->getTranslationVector());

	if (animatedCubeTexture != nullptr)
		animatedCubeTexture->bind();

	glBegin(GL_QUADS);

	for (size_t i = 0; i < animatedQuadVertices.size(); i++)
	{
		Vector3d vertex = animatedQuadVertices[i];
		std::pair<float, float> textureCoord = quadTextureCoords[i];

		glTexCoord2f(textureCoord.first, textureCoord.second);
		glVertex3f(vertex.X(), vertex.Y(), vertex.Z());
	}

	glEnd();

	glDisable(GL_TEXTURE_2D);

	// Renderbuffer wechseln und anzeigen
	glutSwapBuffers();
}

void init(int width, int height)
{
	// Farbe mit der das bild bereinigt wird
	glClearColor(0.3f, 0.3f, 0.3f, 0.0f);

	//initiale tiefenwerte für den z- buffer 1.0 wegen einheitswürfel?
	glClearDepth(1.0);

	//wenn ein eingehender tiefenwert kleiner als der wert an der entsprechenden stelle des z-buffers ist wird überschrieben
	//und die farbe im frame buffer an der entsprechenden stelle übernommen
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	resize(width, height);

	GLuint textureIDs[3];
	glGenTextures(3, textureIDs);

	texture = new stb_imageData(textureIDs[0], "dachs01.jpg");
	skyTexture = new stb_imageData(textureIDs[1], "sky.jpg");
	animatedCubeTexture = new stb_imageData(textureIDs[2], "sire.jpg");
}

int main(int argc, char** argv)
{
	testQuad = new Quad(4.0f, 2.0f, 6.0f);
	testQuad->setPosition(Vector3d(-2.0f, -1.0f, -20.0f));

	texturedTestQuad = new Quad(2.0f, 2.0f, 2.0f);
	texturedTestQuad->setPosition(Vector3d(8.0f, -1.0f, -10.0f));

	skyQuad = new Quad(50.0f, 1.0f, 50.0f);
	skyQuad->setPosition(Vector3d(-25.0f, 75.0f, 25.0f));

	animatedQuad = new Quad(4.0f, 4.0f, 4.0f);
	animatedQuad->setPosition(Vector3d(-2.0f, -2.0f, 20.0f));

	camera = new Camera();

	glutInit(&argc, argv);

	//Tiefenbuffer, Double buffered Window (ein buffer wird angezeigt, auf dem 2. gerendert
	//mit swapbuffers werden die buffer ausgewechselt)
	//RGBA werte für pixel
	//GLUT_MULTISAMPLE https://www.khronos.org/opengl/wiki/Multisampling das vielleicht?
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(150, 150);

	int windowHandle = glutCreateWindow("Intro");
	glutDisplayFunc(&display);
	glutReshapeFunc(&resize);
	glutMouseFunc(&onClick);
	glutKeyboardFunc(&onKeyPressed);
	glutTimerFunc(1000 / 60, &timerFunc, 1);
	init(width, height);

	glutMainLoop();

	return EXIT_SUCCESS;
}