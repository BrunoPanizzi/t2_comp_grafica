#ifndef model_h
#define model_h

#include <GL/gl.h>
#include <stdlib.h>

#define color_impl
#include "color.h"

typedef struct {
    float x, y, z;
} Vertex;

typedef struct {
    int v1, v2, v3;
} Triangle;

typedef struct {
    Vertex *vertices;
    Triangle *triangles;
    int vertexCount;
    int triangleCount;
} Model;

Model *loadModel(const char *filename);

void drawModel(Model *model, float x, float y, float z, float scale, Color c);

void freeModel(Model *model);

Vertex calculateCenter(Model *model);
Vertex calculateSize(Model *model);

#ifdef model_impl
#define model_impl

#include <stdio.h>
#include <string.h>

Model *loadModel(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erro: Não foi possível abrir o arquivo %s\n", filename);
        return NULL;
    }

    Model *model = calloc(sizeof(Model), 1);
    fscanf(file, "%d %d", &model->vertexCount, &model->triangleCount);

    model->vertices = calloc(sizeof(Vertex) * model->vertexCount, 1);
    model->triangles = calloc(sizeof(Triangle) * model->triangleCount, 1);

    for (int i = 0; i < model->vertexCount; i++) {
        fscanf(file, "%f %f %f", &model->vertices[i].x, &model->vertices[i].y, &model->vertices[i].z);
    }

    for (int i = 0; i < model->triangleCount; i++) {
        fscanf(file, "%d %d %d", &model->triangles[i].v1, &model->triangles[i].v2, &model->triangles[i].v3);
    }

    fclose(file);
    return model;
}

void drawModel(Model *model, float x, float y, float z, float scale, Color c) {
    glPushMatrix();
    glScalef(scale, scale, scale);

    glTranslatef(x, y, z);

    glColor(c);

    glBegin(GL_TRIANGLES);

    for (int i = 0; i < model->triangleCount; i++) {
        Triangle tri = model->triangles[i];
        Vertex v1 = model->vertices[tri.v1];
        Vertex v2 = model->vertices[tri.v2];
        Vertex v3 = model->vertices[tri.v3];

        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }

    glEnd();

    glPopMatrix();
}

void freeModel(Model *model) {
    if (model) {
        free(model->vertices);
        free(model->triangles);
        free(model);
    }
}

Vertex calculateCenter(Model *model) {
    Vertex center = {0, 0, 0};
    for (int i = 0; i < model->vertexCount; i++) {
        center.x += model->vertices[i].x;
        center.y += model->vertices[i].y;
        center.z += model->vertices[i].z;
    }
    center.x /= model->vertexCount;
    center.y /= model->vertexCount;
    center.z /= model->vertexCount;
    return center;
}

Vertex calculateSize(Model *model) {
    float minX = model->vertices[0].x;
    float maxX = model->vertices[0].x;
    float minY = model->vertices[0].y;
    float maxY = model->vertices[0].y;
    float minZ = model->vertices[0].z;
    float maxZ = model->vertices[0].z;

    for (int i = 1; i < model->vertexCount; i++) {
        if (model->vertices[i].x < minX) minX = model->vertices[i].x;
        if (model->vertices[i].x > maxX) maxX = model->vertices[i].x;
        if (model->vertices[i].y < minY) minY = model->vertices[i].y;
        if (model->vertices[i].y > maxY) maxY = model->vertices[i].y;
        if (model->vertices[i].z < minZ) minZ = model->vertices[i].z;
        if (model->vertices[i].z > maxZ) maxZ = model->vertices[i].z;
    }

    Vertex size = {maxX - minX, maxY - minY, maxZ - minZ};
    return size;
}

#endif // model_impl

#endif // model_h
