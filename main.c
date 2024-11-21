#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

#define  vec3_impl
#include "vec3.h"
#define  color_impl
#include "color.h"
#define  cube_impl
#include "cube.h"
#define rect_impl
#include "rect.h"

Cube **game_floor;
Cube **game_wall;
Cube **creeper;
Rect *pig;
Vec3 *cam;

void initGL() {
	glEnable(GL_DEPTH_TEST);

	glClearColor(DARKGRAY.r, DARKGRAY.g, DARKGRAY.b, 1.0);
}

void drawCreeper() {
	for (int i = 0; i < 22; i += 2) {
		if (creeper[i] != NULL) {
			drawCubeC(creeper[i]);
		}
	}
}

void drawPig() {
	drawRectR(pig);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glLoadIdentity(); // Reset transformations

	gluLookAt(cam->x, cam->y, cam->z, // Camera position
						0, 0, 0, 0, 1, 0);

	for (size_t i = 0; i < 25*50; i++) {
		drawCubeC(game_floor[i]);
	}

	for (size_t i = 0; i < 25*15; i++) {
		drawCubeC(game_wall[i]);
	}

	drawPig();

	drawCreeper();


	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'w':
			cam->z -= 1.0f; // Move forward (-z)
			break;
		case 's':
			cam->z += 1.0f; // Move backward (+z)
			break;
		case 'a':
			cam->x -= 1.0f; // Move left (-x)
			break;
		case 'd':
			cam->x += 1.0f; // Move right (+x)
			break;
		case 'q':
			cam->y -= 1.0f; // Move down (-y)
			break;
		case 'e':
			cam->y += 1.0f; // Move up (+y)
			break;

		// pig
		case '8':
			pig->pos.x += cos(-pig->rotations.y/180 * M_PI);
			pig->pos.z += sin(-pig->rotations.y/180 * M_PI);
			break;
		case '2':
			pig->pos.x -= cos(-pig->rotations.y/180 * M_PI);
			pig->pos.z -= sin(-pig->rotations.y/180 * M_PI);
			break;
		case '4': // rotate left
			pig->rotations.y += 1;
			break;
		case '6': // rotate right
			pig->rotations.y -= 1;
			break;
		case '7': // points down
			pig->rotations.z -= 1;
			break;
		case '9': // points up
			pig->rotations.z += 1;
			break;

		case 27: // ESC key
			exit(0);
			break;
	}
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

void initCreeper() {
	creeper = calloc(22, sizeof(Cube *));

	for(int i = 0; i < 22; i += 2) {
		creeper[i] = newCube(10, 1, -11+i, 1, GREEN);
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1600, 1000);
	glutCreateWindow("Rotating Cube");

	initGL();

	cam = malloc(sizeof(Vec3));
	cam->x = 0;
	cam->y = 10;
	cam->z = 50;

	game_floor = calloc(25*50, sizeof(Cube *));

	for (int i = 0; i < 25; i++) {  // line
		for (int j = 0; j < 50; j++) { // col
			game_floor[i*50 + j] = newCube(j-24.5, 0, i-12, 1, randomColor());

		}
	}

	game_wall = calloc(25*15, sizeof(Cube *));	

	for (int i = 0; i < 25; i++) {  // line
		for (int j = 0; j < 15; j++) { // col
			game_wall[i*15 + j] = newCube(0, j+1, i-12, 1, randomColor());
		}
	}

	pig = newRectV(
		newVec3(-15, 2, 0),
		newVec3(3, 1, 1),
		newVec3(0, 0, 0),
		MYWHITE
	);

	initCreeper();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(0, timer, 0);

	glutMainLoop();
	return 0;
}
