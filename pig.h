#ifndef pig_h
#define pig_h

#include "vec3.h"
#include "bomb.h"

#define PIG_BODY_SIZE newVec3(3, 1, 2)
#define PINGOLA_SIZE  newVec3(1, 0.4, 0.4)

typedef struct {
	Vec3 pos;
	float bodyRotation;
	float gunRotation;
	float shotPower;

	int movPos;
	int movRotate;
	int movGunRotate;
	int movShot;
} Pig;

Pig *newPig(Vec3 pos);
void drawPig(Pig *pig);
void simulatePig(Pig *pig);
Bomb *shoot(Pig *pig);


#ifdef pig_impl


#include "color.h"

Pig *newPig(Vec3 pos) {
	Pig *pig = malloc(sizeof(Pig));

	pig->pos = pos;
	pig->shotPower = 20;

	return pig;
}

void drawPig(Pig *pig) {
	glPushMatrix();

	translateVec3(pig->pos);
	glRotatef(pig->bodyRotation, 0, 1, 0);

	glPushMatrix();
	scaleVec3(PIG_BODY_SIZE);

	glColor(PINK);
	glutSolidCube(1);

	glPopMatrix();

	// pingola
	Vec3 pingolaPos = vec3Scale(PIG_BODY_SIZE, 0.5);
	pingolaPos.z = 0;
	translateVec3(pingolaPos);

	glRotatef(pig->gunRotation, 0, 0, 1);
	scaleVec3(PINGOLA_SIZE);

	glColor(BLACK);
	glutSolidCube(1);

	glLineWidth(3);

	glPopMatrix();

	glBegin(GL_LINE_STRIP);

	Bomb *bomb = shoot(pig);

	float length = 2; // 2 second of bomb
	for (float i = 0; i < length; i+=0.01) {
		// fade the aim
		glColor4f(0, 0, 0, ((float)length - i)/length);
		Vec3 pos = simulate(&bomb, 0.01);
		glVertex3f(pos.x, pos.y, pos.z);
	}

	if (bomb) free(bomb);

	glEnd();
}


void simulatePig(Pig *🐖) {
	if (🐖->movPos == 1) {
		🐖->pos.x += cos(-🐖->bodyRotation/180 * M_PI)*0.1;
		🐖->pos.z += sin(-🐖->bodyRotation/180 * M_PI)*0.1;
	} else if (🐖->movPos == -1) {
		🐖->pos.x -= cos(-🐖->bodyRotation/180 * M_PI);
		🐖->pos.z -= sin(-🐖->bodyRotation/180 * M_PI);
	}

	if (🐖->movRotate ==  1) 🐖->bodyRotation += 2;
	if (🐖->movRotate == -1) 🐖->bodyRotation -= 2;
	
	if (🐖->movGunRotate == 1 && 🐖->gunRotation < 150)
		🐖->gunRotation += 2;
	if (🐖->movGunRotate ==-1 && 🐖->gunRotation > 0) 
		🐖->gunRotation -= 2;

	if (🐖->movShot == 1 && 🐖->shotPower < 20) 
		🐖->shotPower += 0.4;
	if (🐖->movShot ==-1 && 🐖->shotPower > 5)  
		🐖->shotPower -= 0.4;
	
	🐖->movPos = 0;
	🐖->movRotate = 0;
	🐖->movGunRotate = 0;
	🐖->movShot = 0;
}

Bomb *shoot(Pig *pig) {
	Vec3 offset = vec3Scale(PIG_BODY_SIZE, 0.5);
	offset.x *= cos(-pig->bodyRotation/180 * M_PI);
	offset.z *= sin(-pig->bodyRotation/180 * M_PI);

	Vec3 bombPos = vec3Add(pig->pos, offset);

	float force = pig->shotPower;
	float yf = sin(pig->gunRotation/180 * M_PI) * force;
	force = cos(pig->gunRotation/180 * M_PI) * force;

	float xf = cos(-pig->bodyRotation/180 * M_PI) * force;
	float zf = sin(-pig->bodyRotation/180 * M_PI) * force;

	Vec3 bombDir = newVec3(xf, yf, zf);

	Bomb *bomb = newBomb(
		bombPos,
		bombDir
	);

	return bomb;
}

#endif // pig_impl

#endif // pig_h
