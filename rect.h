#ifndef rect_h
#define rect_h

#include "color.h"
#include "vec3.h"

typedef struct {
	Vec3 pos;
	Vec3 dimensions;
	Vec3 rotations; // all in degrees :(
	Color color;
} Rect;

Rect *newRectV(Vec3 pos, Vec3 dimensions, Vec3 rotations, Color color);
// Rect *newRect(float x, float y, float z, float xs, float ys, float zs, Color color);

void drawRect(float x, float y, float z,
              float xs, float ys, float zs,
              float xr, float yr, float zr,
              Color color);
void drawRectR(Rect *rect);

#ifdef rect_impl
#define rect_impl

#include <GL/gl.h>
#include <GL/glut.h>

Rect *newRectV(Vec3 pos, Vec3 dimensions, Vec3 rotations, Color color) {
	Rect *rect = malloc(sizeof(Rect));

	rect->pos = pos;
	rect->dimensions = dimensions;
	rect->rotations = rotations;
	rect->color = color;

	return rect;
}


void drawRectR(Rect *rect) {
	drawRect(
		rect->pos.x, rect->pos.y, rect->pos.z, 
		rect->dimensions.x, rect->dimensions.y, rect->dimensions.z, 
		rect->rotations.x, rect->rotations.y, rect->rotations.z, 
		rect->color);
}

void drawRect(
	float x, float y, float z, 
	float xs, float ys, float zs, 
	float xr, float yr, float zr, 
	Color c
) {
	glPushMatrix();

	glTranslatef(x, y, z);
	glRotatef(xr, 1, 0, 0);
	glRotatef(yr, 0, 1, 0);
	glRotatef(zr, 0, 0, 1);
	glScalef(xs, ys, zs);

	glColor(c);
	glutSolidCube(1);

	glPopMatrix();
}


#endif // rect_impl

#endif 
