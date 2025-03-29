#include "common.h"
#include <math.h>

void GetColor (Color* array)
{
    for (int t = 0; t < 101; t++)
    {
        if (t >= 100)
        {
            array[t].red  = 0;
            array[t].green = 0;
            array[t].blue   = 0;
        }
        else
        {
            array[t].red  =  (0.5 + 0.35 * sin (15 * t + 1.6)) * 255;
            array[t].green = (0.5 + 0.55 * sin (13 * t + 0.4)) * 255;
            array[t].blue  = (0.5 + 0.45 * sin (14 * t - 1.5)) * 255;
        } // Нельзя ставить просто так char
    }
}