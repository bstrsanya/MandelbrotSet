#ifndef COMMON_H
#define COMMON_H

#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>
#include <time.h>
#include <emmintrin.h>
#include <immintrin.h>
#include <x86intrin.h>  

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

void GetPoint (sfVertexArray* vertex_array, Param* param, Color* array);
void GetColor (Color* array);
void GetPoint2 (sfVertexArray* vertex_array, Param* param, Color* array);
void draw (void (*GetPoint_func)(sfVertexArray* vertex_array, Param* param, Color* array), Color* array);
void tests (Color* array);

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 1000




#endif // COMMON_H