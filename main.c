#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

#define texture_impl
#include "texture.h"
#define  vec3_impl
#include "vec3.h"
#define  color_impl
#include "color.h"
#define  cube_impl
#include "cube.h"
#define rect_impl
#include "rect.h"
#define bomb_impl
#include "bomb.h"
#define pig_impl
#include "pig.h"


#define MAX_BOMBS 8

#define BOARD_DEPTH 25
#define BOARD_WIDTH 50
#define WALL_HEIGHT 15

Cube *game_floor[BOARD_DEPTH * BOARD_WIDTH];
Cube *game_wall[BOARD_DEPTH * WALL_HEIGHT];
Cube **creeper;
Pig  *🐖;
Bomb *bombBuffer[MAX_BOMBS];
Vec3 *cam;
GLuint floorTexture;
GLuint wallTexture;

void initTexture() {
	floorTexture = loadTexture("floor.png");
	wallTexture = loadTexture("wall.png");
}

void initGL() {
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(DARKGRAY.r, DARKGRAY.g, DARKGRAY.b, 1.0);

}

void verifyCollision() {
	for (int b = 0; b < MAX_BOMBS; b++) {
		for (int w = 0; w < WALL_HEIGHT*BOARD_DEPTH; w++) {
			if (bombBuffer[b] == NULL) continue;
			if (game_wall[w] == NULL) continue;

			if (checkCollision(bombBuffer[b], game_wall[w])) {
				free(game_wall[w]);
				free(bombBuffer[b]);
				game_wall[w] = NULL;
				bombBuffer[b] = NULL;
			}
		}

		for (int f = 0; f < BOARD_WIDTH*BOARD_DEPTH; f++) {
			if (bombBuffer[b] == NULL) continue;
			if (game_floor[f] == NULL) continue;

			if (checkCollision(bombBuffer[b], game_floor[f])) {
				free(game_floor[f]);
				free(bombBuffer[b]);
				game_floor[f] = NULL;
				bombBuffer[b] = NULL;
			}
		}
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glLoadIdentity(); // Reset transformations

	gluLookAt(cam->x, cam->y, cam->z, // Camera position
						0, 0, 0, 
						0, 1, 0);

	for (size_t i = 0; i < BOARD_WIDTH*BOARD_DEPTH; i++) {
		if (game_floor[i] != NULL) {
			drawCubeC(game_floor[i]);
		}
	}

	for (size_t i = 0; i < WALL_HEIGHT*BOARD_DEPTH; i++) {
		if (game_wall[i] != NULL) {
			drawCubeC(game_wall[i]);
		}
	}

	drawPig(🐖);

	for (int i = 0; i < MAX_BOMBS; i++) {
		if (bombBuffer[i] == NULL) continue;
		drawBomb(bombBuffer[i]);
		simulate(&bombBuffer[i], 1.0 / 60.0);
	}

	verifyCollision();
	simulatePig(🐖);

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
		case '8': 🐖->movPos = 1;        break;
		case '2': 🐖->movPos = -1;       break;
		// rotate left
		case '4': 🐖->movRotate = 1;     break;
		// rotate right
		case '6': 🐖->movRotate = -1;    break;
		// points down
		case '7': 🐖->movGunRotate = -1; break;
		// points up
		case '9': 🐖->movGunRotate = 1;  break;
		case '1': 🐖->movShot = -1;      break;
		case '3': 🐖->movShot = 1;       break;
		case '5': // shoot bomb
			for (int i = 0; i < MAX_BOMBS; i++) {
				if (bombBuffer[i]) continue;
				bombBuffer[i] = shoot(🐖);
				break;
			}
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

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1600, 1000);
	glutCreateWindow("Rotating Cube");

	initGL();

	cam = malloc(sizeof(Vec3));
	cam->x = 0;
	cam->y = 15;
	cam->z = 40;

	initTexture();

	for (int i = 0; i < BOARD_DEPTH; i++) {  // line
		for (int j = 0; j < BOARD_WIDTH; j++) { // col
			game_floor[i*50 + j] = newCube(j-24.5, 0, i-12, 1, WHITE);
			game_floor[i*50 + j]->texture = floorTexture;
		}
	}

	for (int i = 0; i < BOARD_DEPTH; i++) {  // line
		for (int j = 0; j < WALL_HEIGHT; j++) { // col
			game_wall[i*15 + j] = newCube(0, j+1, i-12, 1, WHITE);
			game_wall[i*15 + j]->texture = wallTexture;
		}
	}

	🐖 = newPig(newVec3(-15, 1, 0));

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(0, timer, 0);

	glutMainLoop();
	return 0;
}
