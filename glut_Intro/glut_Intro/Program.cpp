#include <stdlib.h>

#include <GL/glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>  

#include "Camera.h"
#include "Geometry.h"
#include "Quad.h"
#include "Vector3d.h"
#include "Vector3dMatrix.h"

Camera* camera = nullptr;
Quad* testQuad = nullptr;

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
	Vector3d direction = camera->getDirection();
	Vector3d upVector = camera->getUpVector();

	gluLookAt(position.X(), position.Y(), position.Z(),
		direction.X(), direction.Y(), direction.Z(),
		upVector.X(), upVector.Y(), upVector.Z()
	);

	glBegin(GL_QUADS);
	
	//sollte man nicht unbedingt hier machen. Die Vertices kann man besser woanders berechnen
	std::vector<Vector3d> quadVertices = testQuad->getQuadVertices();
	quadVertices = Geometry::rotateY(quadVertices, 45.0f);
	quadVertices = Geometry::rotateX(quadVertices, 45.0f);
	/*quadVertices = Geometry::rotateZ(quadVertices, 45.0);*/
	quadVertices = Geometry::translate(quadVertices, testQuad->getTranslationVector());

	for (size_t i = 0; i < quadVertices.size(); i++)
	{
		Vector3d vertex = quadVertices[i];
		glVertex3f(vertex.X(), vertex.Y(), vertex.Z());
	}

	glEnd();

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
}

int main(int argc, char** argv)
{
	testQuad = new Quad(4.0f, 2.0f, 6.0f);
	testQuad->setPosition(Vector3d(-2.0f, -1.0f, -20.0f));

	camera = new Camera();
	camera->setRoationAngleY(180.0f);

	glutInit(&argc, argv);

	//Tiefenbuffer, Double buffered Window (ein buffer wird angezeigt, auf dem 2. gerendert
	//mit swapbuffers werden die buffer ausgewechselt)
	//RGBA werte für pixel
	//GLUT_MULTISAMPLE https://www.khronos.org/opengl/wiki/Multisampling das vielleicht?
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(150, 150);

	int windowHandle = glutCreateWindow("Intro");
	glutDisplayFunc(&display);
	glutReshapeFunc(&resize);
	init(1024, 768);

	glutMainLoop();

	return EXIT_SUCCESS;
}