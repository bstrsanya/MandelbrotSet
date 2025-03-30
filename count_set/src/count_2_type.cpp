#include "common.h"

void GetPoint2 (int* vertex_array, Param* param)
{
    int index = 0;

    float beg_x0 = (0 - (WINDOW_WIDTH  / 2)) / (WINDOW_WIDTH / param->scale) - param->offsetX;
    float beg_y0 = (0 + (WINDOW_HEIGHT / 2)) / (WINDOW_HEIGHT / param->scale) - param->offsetY;

    float step_x = 1  / (WINDOW_WIDTH  / param->scale);
    float step_y = -1 / (WINDOW_HEIGHT / param->scale);

    float max_r2 = MAX_RAD_2;
    
    for (float x_pixel = 0; x_pixel < WINDOW_WIDTH; x_pixel += 1)
    {
        float x0[SIZE_AVX] = {beg_x0};
        float y0[SIZE_AVX] = {beg_y0};

        for (int k = 1; k < SIZE_AVX; k++) 
        {   
            y0[k] = y0[k - 1] + step_y; 
            x0[k] = beg_x0;
        }

        for (float y_pixel = 0; y_pixel < WINDOW_HEIGHT; y_pixel += SIZE_AVX)
        {
            float x[SIZE_AVX]  = {};
            float x2[SIZE_AVX] = {};
            float y[SIZE_AVX]  = {};
            float y2[SIZE_AVX] = {};

            int iterations[SIZE_AVX] = {};

            for (int i = 0; i < MAX_NUM_ITER; i++)
            {
                float r2[SIZE_AVX]  = {};
                for (int k = 0; k < SIZE_AVX; k++) r2[k] = x2[k] + y2[k];

                int cmp[SIZE_AVX] = {};
                for (int k = 0; k < SIZE_AVX; k++) cmp[k] = r2[k] < max_r2 ? 1 : 0;

                int mask = 0;
                for (int k = 0; k < SIZE_AVX; k++) mask += (cmp[k] == 0);                
                if (mask == SIZE_AVX)
                    break;
                   
                for (int k = 0; k < SIZE_AVX; k++) iterations[k] += (cmp[k] != 0);

                for (int k = 0; k < SIZE_AVX; k++) y[k] = y[k] * x[k] * 2 + y0[k];
                for (int k = 0; k < SIZE_AVX; k++) x[k] = x2[k] - y2[k] + x0[k];

                for (int k = 0; k < SIZE_AVX; k++) x2[k] = x[k] * x[k];
                for (int k = 0; k < SIZE_AVX; k++) y2[k] = y[k] * y[k];

            }

            memcpy (&vertex_array[index], (int*) &iterations, SIZE_AVX * sizeof (int));
            index += SIZE_AVX;

            for (int k = 0; k < SIZE_AVX; k++) y0[k] += step_y * SIZE_AVX;
        }
        beg_x0 += step_x;
    }
}
