#ifndef cube_h
#define cube_h

#include "color.h"
#include "vec3.h"

typedef struct {
	Vec3 pos;
	float size;
	Color color;
} Cube;

Cube *newCubeV(Vec3 pos, float size, Color color);
Cube *newCube(float x, float y, float z, float size, Color color);

void drawCube(float x, float y, float z, float size, Color c);
void drawCubeC(Cube *cube);

#ifdef cube_impl
#define cube_impl

#include <GL/gl.h>

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
	drawCube(cube->pos.x, cube->pos.y, cube->pos.z, cube->size, cube->color);
}

void drawCube(float x, float y, float z, float size, Color c) {
	glPushMatrix();

	glTranslatef(x, y, z);
	glScalef(size/2, size/2, size/2);

	glBegin(GL_QUADS);
	// Front face
	glColor(c);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	// Back face
	glColor(c);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Top face
	glColor(c);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Bottom face
	glColor(c);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	// Right face
	glColor(c);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Left face
	glColor(c);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();

	glPopMatrix();
}


#endif // cube_impl

#endif // cube_h
