#ifndef COMMON_H
#define COMMON_H

#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>
#include <time.h>

struct Param {
    float offsetX;
    float offsetY;
    float scale;
};

struct Color {
    char red;
    char green;
    char blue;
};

void GetPoint (sfVertexArray* vertex_array, Param* param);
void GetColor (int iterations, Color* color);
void GetPoint1 (sfVertexArray* vertex_array, Param* param);
void GetPoint2 (sfVertexArray* vertex_array, Param* param);
void draw (void (*GetPoint_func)(sfVertexArray* vertex_array, Param* param));
void tests ();

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 1000

#endif // COMMON_H