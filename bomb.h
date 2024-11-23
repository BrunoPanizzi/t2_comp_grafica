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
Vec3 simulate(Bomb *bomb, float dt);


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

Vec3 simulate(Bomb *bomb, float dt) {
	Vec3 pos = bomb->pos;
	bomb->pos = vec3Add(pos, vec3Scale(bomb->speed, dt));
	bomb->speed.y -= GRAVITY*dt;
	return pos;
}

#endif // bomb_impl

#endif // bomb_h
