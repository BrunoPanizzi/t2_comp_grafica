#ifndef bomb_h
#define bomb_h

#include "vec3.h"

#define GRAVITY 10


typedef struct {
	Vec3 pos;
	Vec3 speed;
} Bomb;

Bomb *newBomb(Vec3 pos, Vec3 speed);
void drawBomb(Bomb *bomb);
void simulate(Bomb *bomb, float dt);


#ifdef bomb_impl


Bomb *newBomb(Vec3 pos, Vec3 speed) {
	Bomb *bomb = malloc(sizeof(Bomb));

	bomb->pos = pos;
	bomb->speed = speed;

	return bomb;
}

void drawBomb(Bomb *bomb) {
	glPushMatrix();

	glTranslatef(bomb->pos.x, bomb->pos.y, bomb->pos.z);

	glutSolidSphere(1, 16, 16);

	glPopMatrix();
}

void simulate(Bomb *bomb, float dt) {
	bomb->pos = vec3Add(bomb->pos, vec3Scale(bomb->speed, dt));
	bomb->speed.y -= GRAVITY*dt;
}

#endif // bomb_impl

#endif // bomb_h
