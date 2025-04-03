#ifndef COMMON_H
#define COMMON_H

#include <SFML/Graphics.h>
#include <cstdint>
#include <immintrin.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xmmintrin.h>

struct Param
{
    float offsetX;
    float offsetY;
    float scale;
};

struct Color
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

void GetPoint1 (int* vertex_array, Param* param);
void GetPoint2 (int* vertex_array, Param* param);
void GetPoint3 (int* vertex_array, Param* param);

void GetColor (uint32_t* array);

void draw (void (*GetPoint_func) (int* vertex_array, Param* param));
uint64_t get_rdtsc ();
void tests ();

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 1000

const long cpu_freq               = 4000000000;
const int MAX_NUM_ITER            = 100;
const int MAX_RAD_2               = 100;
const int SIZE_AVX                = 8;
const float COEF_SHIFT            = 0.1f;
const float ZOOM_IN               = 1.1f;
const float ZOOM_OUT              = 0.9f;
const float INIT_SCALE            = 2.0f;
const float INIT_SHIFT            = 0.0f;
const size_t SIZE_BUF_TEXT        = 30;
const int DEEP_COLOR              = 8;
const int SIZE_TEST               = 10;
const int SIZE_PIXEL              = 4;
const int OPAQUE                  = 255;
constexpr const char* WAY_FONT    = "/usr/share/fonts/aajohan-comfortaa-fonts/Comfortaa-Bold.otf";
constexpr const char* NAME_WINDOW = "Mandelbrot";

const float SHIFT_COLOR = 0.5f;
const float RED_A       = 0.35f;
const float RED_B       = 15.0f;
const float RED_C       = 1.6f;
const float GREEN_A     = 0.55f;
const float GREEN_B     = 13.0f;
const float GREEN_C     = 0.4f;
const float BLUE_A      = 0.45f;
const float BLUE_B      = 14.0f;
const float BLUE_C      = -1.5f;
const int MAX_COLOR     = 255;
const int NORMAL_CHAR   = 256;

const int SHIFT_24 = 24;
const int SHIFT_16 = 16;
const int SHIFT_8  = 8;

#endif // COMMON_H