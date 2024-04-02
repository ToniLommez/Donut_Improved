#include "math.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 80
#define HEIGHT 40
#define MAX_VERTICES 8
#define MAX_EDGES 12
#define MAX_FACES 6

void drawLine(char *buffer, int width, int x0, int y0, int x1, int y1, char ch) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1) {
        if (x0 >= 0 && x0 < width && y0 >= 0 && y0 < HEIGHT) {
            buffer[y0 * width + x0] = ch;
        }
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

char getLightIntensityChar(float intensity) {
    char lightChars[] = ".,:;~=oO#$@";
    int idx = (int)(intensity * 10);
    if (idx < 0) idx = 0;
    if (idx > 9) idx = 9;
    return lightChars[idx];
}

int main() {
    // Define os vértices, as arestas e as faces de um cubo
    float cube_vertices[MAX_VERTICES][3] = {
        {-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1}, {-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}};
    int cube_edges[MAX_EDGES][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Bottom face
        {4, 5},
        {5, 6},
        {6, 7},
        {7, 4}, // Top face
        {0, 4},
        {1, 5},
        {2, 6},
        {3, 7} // Side edges
    };

    int cube_faces[MAX_FACES][4] = {
        {0, 1, 2, 3}, // Front face
        {4, 5, 6, 7}, // Back face
        {0, 1, 5, 4}, // Bottom face
        {2, 3, 7, 6}, // Top face
        {0, 3, 7, 4}, // Left face
        {1, 2, 6, 5}  // Right face
    };

    float A = 0, B = 0; // Ângulos para a rotação do cubo

    char buffer[WIDTH * HEIGHT]; // Buffer de desenho existente
    char outputBuffer[WIDTH * (HEIGHT + 1) + 1];

    while (1) {
        char buffer[WIDTH * HEIGHT];
        memset(buffer, ' ', sizeof(buffer));

        int projected_points[MAX_VERTICES][2];

        // Rotaciona, projeta os vértices e desenha as arestas
        for (int i = 0; i < MAX_VERTICES; i++) {
            float *v = cube_vertices[i];

            // Rotação ao redor do eixo Y
            float rotY_X = _cos(A) * v[0] + _sin(A) * v[2];
            float rotY_Z = -_sin(A) * v[0] + _cos(A) * v[2];

            // Rotação ao redor do eixo X
            float rotX_Y = _cos(B) * v[1] - _sin(B) * rotY_Z;
            float rotX_Z = _sin(B) * v[1] + _cos(B) * rotY_Z;

            // Projeção para o plano 2D
            int x_2d = WIDTH / 2 + (int)(WIDTH * rotY_X / (rotX_Z + 4));
            int y_2d = HEIGHT / 2 - (int)(HEIGHT * rotX_Y / (rotX_Z + 4));

            projected_points[i][0] = x_2d;
            projected_points[i][1] = y_2d;
        }

        // Cálculo simples da iluminação
        float light_vector[3] = {_cos(A - PI / 4), _cos(B - PI / 4), _sin(A - PI / 4)};
        for (int i = 0; i < MAX_EDGES; i++) {
            int *p1 = projected_points[cube_edges[i][0]];
            int *p2 = projected_points[cube_edges[i][1]];
            char ch = getLightIntensityChar(0.4);
            drawLine(buffer, WIDTH, p1[0], p1[1], p2[0], p2[1], ch);
        }

        // Limpa a tela
        printf("\x1b[H");

        int outputIndex = 0;
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                outputBuffer[outputIndex++] = buffer[y * WIDTH + x];
            }
            outputBuffer[outputIndex++] = '\n';
        }
        outputBuffer[outputIndex] = '\0'; // Termina o buffer de saída com um caractere nulo

        // Imprime o conteúdo completo do buffer de saída de uma vez
        printf("%s", outputBuffer);

        A += 0.00008; // Ajuste esses valores para alterar a velocidade de rotação
        B += 0.00003;
    }

    return 0;
}
