#include "common.h"

void GetPoint1 (int* vertex_array, Param* param)
{
    int index = 0;

    float x0 = (0 - (WINDOW_WIDTH / 2)) / (WINDOW_WIDTH / param->scale) - param->offsetX;
    float y0 = (0 + (WINDOW_HEIGHT / 2)) / (WINDOW_HEIGHT / param->scale) - param->offsetY;
    
    float beg_yo = y0;

    float step_x = 1  / (WINDOW_WIDTH / param->scale);
    float step_y = -1 / (WINDOW_HEIGHT / param->scale); 
 
    for (float x_pixel = 0; x_pixel < WINDOW_WIDTH; x_pixel++)
    {
        y0 = beg_yo;
        
       for (float y_pixel = 0; y_pixel < WINDOW_HEIGHT; y_pixel++)
        {
            float x  = 0.0f;
            float x2 = 0.0f;
            float y  = 0.0f;
            float y2 = 0.0f;
 
            int iter = 0;
 
            while (x2 + y2 < MAX_RAD_2 && iter < MAX_NUM_ITER) 
            {
                y = 2 * x * y + y0;
                x = x2 - y2 + x0;

                x2 = x * x;
                y2 = y * y;
 
                iter++;
            }
 
            vertex_array[index++] = iter;

            y0 = y0 + step_y;
        }
        x0 = x0 + step_x;
    }
}