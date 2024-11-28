#ifndef model_h
#define model_h

#include <GL/gl.h>
#include <stdlib.h>

// Estrutura para representar um vértice
typedef struct {
    float x, y, z; // Coordenadas do vértice
} Vertex;

// Estrutura para representar um triângulo (face)
typedef struct {
    int v1, v2, v3; // Índices dos vértices que formam o triângulo
} Triangle;

// Estrutura para armazenar o modelo 3D
typedef struct {
    Vertex *vertices;    // Array de vértices
    Triangle *triangles; // Array de triângulos
    int vertexCount;     // Número de vértices
    int triangleCount;   // Número de triângulos
} Model;

// Função para carregar um modelo de um arquivo .tri
Model *loadModel(const char *filename);

// Função para desenhar o modelo
void drawModel(Model *model);

// Função para liberar memória do modelo
void freeModel(Model *model);

#ifdef model_impl
#define model_impl

#include <stdio.h>
#include <string.h>

// Implementação para carregar o modelo
Model *loadModel(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erro: Não foi possível abrir o arquivo %s\n", filename);
        return NULL;
    }

    Model *model = malloc(sizeof(Model));
    fscanf(file, "%d %d", &model->vertexCount, &model->triangleCount);

    // Alocar memória para os vértices e triângulos
    model->vertices = malloc(sizeof(Vertex) * model->vertexCount);
    model->triangles = malloc(sizeof(Triangle) * model->triangleCount);

    // Ler os vértices
    for (int i = 0; i < model->vertexCount; i++) {
        fscanf(file, "%f %f %f", &model->vertices[i].x, &model->vertices[i].y, &model->vertices[i].z);
    }

    // Ler os triângulos
    for (int i = 0; i < model->triangleCount; i++) {
        fscanf(file, "%d %d %d", &model->triangles[i].v1, &model->triangles[i].v2, &model->triangles[i].v3);
    }

    fclose(file);
    return model;
}

// Implementação para desenhar o modelo
void drawModel(Model *model) {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < model->triangleCount; i++) {
        Triangle tri = model->triangles[i];
        Vertex v1 = model->vertices[tri.v1];
        Vertex v2 = model->vertices[tri.v2];
        Vertex v3 = model->vertices[tri.v3];

        // Desenhar o triângulo
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }
    glEnd();
}

// Implementação para liberar memória do modelo
void freeModel(Model *model) {
    if (model) {
        free(model->vertices);
        free(model->triangles);
        free(model);
    }
}

#endif // model_impl

#endif // model_h
