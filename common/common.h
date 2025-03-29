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
#include <cstdint>
#include <math.h>
#include <string.h>

struct Param {
    float offsetX;
    float offsetY;
    float scale;
};

struct Color {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

void GetPoint (int* vertex_array, Param* param);
void GetColor (Color* array);
void GetPoint2 (int* vertex_array, Param* param);
void draw (void (*GetPoint_func)(int* vertex_array, Param* param));
uint64_t get_rdtsc();
void tests ();

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 1000

const long cpu_freq = 4000000000;
const int MAX_NUM_ITER = 100;
const int MAX_RAD_2 = 100;
const int SIZE_AVX = 8;



#endif // COMMON_H