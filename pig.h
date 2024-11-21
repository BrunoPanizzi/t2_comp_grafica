#ifndef pig_h
#define pig_h

#include "vec3.h"

typedef struct {
	Vec3 pos;
	float body_rotation;
	float gun_rotation;
} Pig;

Pig *newPig(Vec3 pos);

void drawPig(Pig *pig);

#ifdef pig_impl
#define pig_impl

#include "color.h"

Pig *newPig(Vec3 pos) {
	Pig *pig = malloc(sizeof(Pig));

	pig->pos = pos;

	return pig;
}

void drawPig(Pig *pig) {
	glPushMatrix();

	glTranslatef(pig->pos.x, pig->pos.y, pig->pos.z);
	glRotatef(pig->body_rotation, 0, 1, 0);

	glPushMatrix();
	glScalef(3, 1, 2);

	glColor(PINK);
	glutSolidCube(1);

	glPopMatrix();

	// pingola
	glTranslatef(1.5, 0.5, 0);

	glRotatef(pig->gun_rotation, 0, 0, 1);
	glScalef(1, .4, .4);

	glColor(BLACK);
	glutSolidCube(1);
	
	glPopMatrix();
}

#endif // pig_impl

#endif // pig_h
