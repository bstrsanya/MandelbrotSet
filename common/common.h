#ifndef COMMON_H
#define COMMON_H

#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>
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

void GetPoint1  (int* vertex_array, Param* param);
void GetPoint2 (int* vertex_array, Param* param);
void GetPoint3 (int* vertex_array, Param* param);

void GetColor  (Color* array);


void draw (void (*GetPoint_func)(int* vertex_array, Param* param));
uint64_t get_rdtsc();
void tests ();

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 1000

const long cpu_freq = 4000000000;
const int MAX_NUM_ITER = 100;
const int MAX_RAD_2 = 100;
const int SIZE_AVX = 8;
const float COEF_SHIFT = 0.1f;
const float ZOOM_IN = 1.1f;
const float ZOOM_OUT = 0.9f;
const float INIT_SCALE = 2.0f;
const float INIT_SHIFT = 0.0f;
const size_t SIZE_BUF_TEXT = 30;
const int DEEP_COLOR = 8;
const int SIZE_TEST = 10;
constexpr const char* WAY_FONT = "./draw_set/1.otf";
constexpr const char* NAME_WINDOW = "Mandelbrot";

#endif // COMMON_H