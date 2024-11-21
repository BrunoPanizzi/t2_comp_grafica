#ifndef rect_h
#define rect_h

#include "color.h"
#include "vec3.h"

typedef struct {
	Vec3 pos;
	Vec3 dimensions;
	float rotation;
	Color color;
} Rect;

Rect *newRectV(Vec3 pos, Vec3 dimensions, Color color);
Rect *newRect(float x, float y, float z, float xs, float ys, float zs, Color color);

void drawRect(float x, float y, float z,
              float xs, float ys, float zs,
              float rotate, Color color);
void drawRectR(Rect *rect);

#ifdef rect_impl
#define rect_impl

#include <GL/gl.h>

Rect *newRectV(Vec3 pos, Vec3 dimensions, Color color) {
	Rect *rect = malloc(sizeof(Rect));

	rect->pos = pos;
	rect->dimensions = dimensions;
	rect->color = color;

	return rect;
}

Rect *newRect(float x, float y, float z, float xs, float ys, float zs, Color color) {
	return newRectV(newVec3(x, y, z), newVec3(xs, ys, zs), color);
}


void drawRectR(Rect *rect) {
	drawRect(
		rect->pos.x, rect->pos.y, rect->pos.z, 
		rect->dimensions.x, rect->dimensions.y, rect->dimensions.z, 
		rect->rotation, rect->color);
}

void drawRect(float x, float y, float z, float xs, float ys, float zs, float rotation, Color c) {
	glPushMatrix();

	glTranslatef(x, y, z);
	glRotatef(rotation, 0, 1, 0);
	glScalef(xs, ys, zs);

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


#endif // rect_impl

#endif 
