#ifndef rect_h
#define rect_h

#include "color.h"
#include "vec3.h"
#include "bomb.h"

typedef struct {
	Vec3 pos;
	Vec3 dimensions;
	Vec3 rotations; // all in degrees :(
	Color color;
} Rect;

Rect *newRectV(Vec3 pos, Vec3 dimensions, Vec3 rotations, Color color);

void drawRect(float x, float y, float z,
              float xs, float ys, float zs,
              float xr, float yr, float zr,
              Color color);
void drawRectR(Rect *rect);
bool checkCollisionRectBomb(Rect *rect, Bomb *ball);

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

// Function to calculate the closest point on the rectangular prism to the sphere's center
Vec3 closestPointOnRect(Rect *rect, Vec3 point) {
    Vec3 closest = rect->pos;
    Vec3 halfDimensions = {rect->dimensions.x / 2, rect->dimensions.y / 2, rect->dimensions.z / 2};

    closest.x = fmax(rect->pos.x - halfDimensions.x, fmin(point.x, rect->pos.x + halfDimensions.x));
    closest.y = fmax(rect->pos.y - halfDimensions.y, fmin(point.y, rect->pos.y + halfDimensions.y));
    closest.z = fmax(rect->pos.z - halfDimensions.z, fmin(point.z, rect->pos.z + halfDimensions.z));

    return closest;
}

// Function to check collision between a Rect and a Sphere
bool checkCollisionRectBomb(Rect *rect, Bomb *ball) {
    Vec3 closestPoint = closestPointOnRect(rect, ball->pos);
    Vec3 distanceVector = {closestPoint.x - ball->pos.x, closestPoint.y - ball->pos.y, closestPoint.z - ball->pos.z};
    float distanceSquared = distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y + distanceVector.z * distanceVector.z;
    float radiusSquared = BOMB_SIZE * BOMB_SIZE;

    return distanceSquared <= radiusSquared;
}


#endif // rect_impl

#endif 
