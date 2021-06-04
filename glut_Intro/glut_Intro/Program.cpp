#include <stdlib.h>

#include <GL/glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h>  

#include "Vector3d.h"
#include "Quad.h"
#include "Vector3dMatrix.h"

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

	glTranslatef(0, 0, -20);
	//glRotatef(45.0, 0.0, 1.0, 0.0);
	glRotatef(-45.0, 0.0, 1.0, 0.0);
	glRotatef(45.0, 1.0, 0.0, 0.0);
	/*glRotatef(15.0, 0.0, 1.0, 0.0);
	glTranslatef(0, 0, -8);*/

	glBegin(GL_QUADS);
	
	//sollte man nicht unbedingt hier machen. Die Vertices kann man besser woanders berechnen
	std::vector<Vector3d> quadVertices = testQuad->getQuadVertices();

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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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
	//Vector3d lScale = 2 * Vector3d::right();
	testQuad = new Quad(4, 2, 6);

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