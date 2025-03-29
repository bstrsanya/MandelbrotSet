#include "common.h"

void GetColor (Color* array)
{
    for (int t = 0; t < MAX_NUM_ITER; t++)
    {
        array[t].red  =  (unsigned char) (((int) round ((0.5 + 0.35 * sin (15 * t + 1.6)) * 255)) % 256);
        array[t].green = (unsigned char) (((int) round ((0.5 + 0.55 * sin (13 * t + 0.4)) * 255)) % 256);
        array[t].blue  = (unsigned char) (((int) round ((0.5 + 0.45 * sin (14 * t - 1.5)) * 255)) % 256);
    }

    array[MAX_NUM_ITER].red = 0;
    array[MAX_NUM_ITER].green = 0;
    array[MAX_NUM_ITER].blue = 0;
}