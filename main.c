#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

#define  vec3_impl
#include "vec3.h"
#define  color_impl
#include "color.h"
#define  cube_impl
#include "cube.h"

Cube *cube;

void initGL() {
	glEnable(GL_DEPTH_TEST);

	glClearColor(DARKGRAY.r, DARKGRAY.g, DARKGRAY.b, 1.0);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glLoadIdentity(); // Reset transformations

	gluLookAt(
		0, 8, 20, // Camera position
		0, 0, 0,  // Look at the origin
		0, 1, 0
	);

	drawCubeC(cube);

	glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height) {
	if (height == 0) height = 1; // Prevent divide by zero
	float aspect = (float)width / (float)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
}

void timer() {
	glutPostRedisplay(); // Post a paint request to activate display()
	glutTimerFunc(16, timer, 0); // Re-register timer for roughly 60 FPS
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Rotating Cube");

	initGL();

	cube = newCube(0, 0, 0, 1, randomColor());

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);

	glutMainLoop();
	return 0;
}
