#include "common.h"

void GetColor (int iterations, Color* color)
{
    const float colorScale = 255.0f / 256;
    const float iterNormalized = iterations * colorScale;
    if (iterations >= 255)
    {
        color->blue = 0;
        color->green = 0;
        color->red = 0;
    }
    else
    {
        color->red = iterNormalized * 2;
        color->green = iterNormalized * 10 + 2;
        color->blue = iterNormalized * 1 + 5;
    }
}