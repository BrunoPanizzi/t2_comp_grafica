#ifndef cube_h
#define cube_h

#include "color.h"
#include "vec3.h"

typedef struct {
	Vec3 pos;
	float size;
	float rotation;
	Color color;
} Cube;

Cube *newCubeV(Vec3 pos, float size, Color color);
Cube *newCube(float x, float y, float z, float size, Color color);

void drawCube(float x, float y, float z, float rotation, float size, Color c);
void drawCubeC(Cube *cube);

#ifdef cube_impl
#define cube_impl

#include <GL/gl.h>
#include <GL/glut.h>

Cube *newCubeV(Vec3 pos, float size, Color color) {
	Cube *cube = malloc(sizeof(Cube));

	cube->pos = pos;
	cube->size = size;
	cube->color = color;

	return cube;
}

Cube *newCube(float x, float y, float z, float size, Color color) {
	return newCubeV(newVec3(x, y, z), size, color);
}


void drawCubeC(Cube *cube) {
	drawCube(cube->pos.x, cube->pos.y, cube->pos.z, cube->rotation, cube->size, cube->color);
}

void drawCube(float x, float y, float z, float rotation, float size, Color c) {
	glPushMatrix();

	glTranslatef(x, y, z);
	glScalef(size, size, size);
	glRotatef(rotation, 0, 1, 0);

	// Front face
	glColor(c);
	glutSolidCube(1);

	glPopMatrix();
}


#endif // cube_impl

#endif // cube_h
