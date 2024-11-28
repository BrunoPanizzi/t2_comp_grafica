#ifndef bomb_h
#define bomb_h

#include <stdbool.h>
#include <GL/gl.h>

#include "vec3.h"
#include "cube.h"

#define GRAVITY 10
#define MAX_BALL_AGE 10
#define BOMB_SIZE 0.5

typedef struct {
	Vec3 pos;
	Vec3 speed;
	float age;
} Bomb;

Bomb *newBomb(Vec3 pos, Vec3 speed);
void drawBomb(Bomb *bomb);
Vec3 simulate(Bomb **bomb, float dt);

bool checkCollision(Bomb *bomb, Cube *cube);

#ifdef bomb_impl


Bomb *newBomb(Vec3 pos, Vec3 speed) {
	Bomb *bomb = malloc(sizeof(Bomb));

	bomb->pos = pos;
	bomb->speed = speed;

	return bomb;
}

void drawBomb(Bomb *bomb) {
	glPushMatrix();

	glColor3f(0.95, 0.23, 0.3);

	glTranslatef(bomb->pos.x, bomb->pos.y, bomb->pos.z);

	glutSolidSphere(BOMB_SIZE, 16, 16);

	glPopMatrix();
}

Vec3 simulate(Bomb **bomb, float dt) {
	if (*bomb == NULL) {
		return newVec3(0, 0, 0);
	}
	Vec3 pos = (*bomb)->pos;
	(*bomb)->age += dt;
	if ((*bomb)->age > MAX_BALL_AGE) {
		free((*bomb));
		*bomb = NULL;
		return pos;
	}
	(*bomb)->pos = vec3Add(pos, vec3Scale((*bomb)->speed, dt));
	(*bomb)->speed.y -= GRAVITY*dt;
	return pos;
}

float clamp(float t, float min, float max) {
	if (t <= min) return min;
	if (t >= max) return max;
	return t;
}

bool checkCollision(Bomb *bomb, Cube *cube) {
	Vec3 d = vec3Sub(bomb->pos, cube->pos);
	float halfSide = cube->size / 2;

	Vec3 dClamped = newVec3(
		clamp(d.x, -halfSide, halfSide),
		clamp(d.y, -halfSide, halfSide),
		clamp(d.z, -halfSide, halfSide)
	);

	Vec3 closestPointOnCube = vec3Add(cube->pos, dClamped);
	float distance = vec3Length(vec3Sub(bomb->pos, closestPointOnCube));

	return distance <= BOMB_SIZE;
}

#endif // bomb_impl

#endif // bomb_h
