#ifndef cube_h
#define cube_h

#include "color.h"
#include "vec3.h"

typedef struct {
	Vec3 pos;
	float size;
	float rotation;
	Color color;
	GLuint texture;
} Cube;

Cube *newCubeV(Vec3 pos, float size, Color color);
Cube *newCube(float x, float y, float z, float size, Color color);

void drawCube(float x, float y, float z, float rotation, float size, Color c, GLuint texture);
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
	drawCube(cube->pos.x, cube->pos.y, cube->pos.z, cube->rotation, cube->size, cube->color, cube->texture);
}

void drawCube(float x, float y, float z, float rotation, float size, Color c, GLuint texture) {

	glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(size, size, size);
    glRotatef(rotation, 0, 0, 0);

    const float vertices[8][3] = {
        {-0.5f, -0.5f,  0.5f}, {0.5f, -0.5f,  0.5f}, {0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f},
        {-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f,  0.5f, -0.5f}, {-0.5f,  0.5f, -0.5f} 
    };

    const int faces[6][4] = {
        {0, 1, 2, 3}, // Front
        {5, 4, 7, 6}, // Back
        {3, 2, 6, 7}, // Top
        {4, 5, 1, 0}, // Bottom
        {1, 5, 6, 2}, // Right
        {4, 0, 3, 7}  // Left
    };

    const float texCoords[4][2] = { // Vertex coordinates for texture mapping
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}
    };
	
	if (!texture) {
		glColor(c);
	}
    else {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glColor3f(1.0f, 1.0f, 1.0f);
    } 

    glBegin(GL_QUADS);
    for (int i = 0; i < 6; i++) { // Para cada face
        for (int j = 0; j < 4; j++) { // Para cada vértice da face
            if (texture) {
                glTexCoord2f(texCoords[j][0], texCoords[j][1]); // Coordenadas de textura
            }
            int vertexIndex = faces[i][j];
            glVertex3f(vertices[vertexIndex][0], vertices[vertexIndex][1], vertices[vertexIndex][2]);
        }
    }
    glEnd();

    if (texture) {
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
}

#endif // cube_impl

#endif // cube_h
