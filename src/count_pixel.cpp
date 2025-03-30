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

void GetPoint3 (int* vertex_array, Param* param)
{
    int index = 0;

    float x0 = (0 - (WINDOW_WIDTH  / 2)) / (WINDOW_WIDTH / param->scale) - param->offsetX;
    float y0 = (0 + (WINDOW_HEIGHT / 2)) / (WINDOW_HEIGHT / param->scale) - param->offsetY;

    float step_x = 1  / (WINDOW_WIDTH  / param->scale);
    float step_y = -1 / (WINDOW_HEIGHT / param->scale);

    __m256  max_r2      = _mm256_set1_ps (MAX_RAD_2);
    __m256  _76543210   = _mm256_set_ps (7,6,5,4,3,2,1,0);
    __m256  delta       = _mm256_mul_ps (_mm256_set1_ps (SIZE_AVX), _mm256_set1_ps (step_y));
    __m256i active_mask = _mm256_set1_epi32(1); 
    __m256  beg_m256_y0 = _mm256_add_ps (_mm256_set1_ps (y0), _mm256_mul_ps (_76543210, _mm256_set1_ps (step_y)));
    
    for (float x_pixel = 0; x_pixel < WINDOW_WIDTH; x_pixel += 1)
    {
        __m256 m256_x0 = _mm256_set1_ps (x0);
        __m256 m256_y0 = beg_m256_y0;

        for (float y_pixel = 0; y_pixel < WINDOW_HEIGHT; y_pixel += SIZE_AVX)
        {
            __m256 m256_x  = _mm256_setzero_ps();
            __m256 m256_x2 = _mm256_setzero_ps();
            __m256 m256_y  = _mm256_setzero_ps();
            __m256 m256_y2 = _mm256_setzero_ps();

            __m256i iterations = _mm256_setzero_si256();

            for (int i = 0; i < MAX_NUM_ITER; i++)
            {
                __m256 r2  = _mm256_add_ps (m256_x2, m256_y2);
                __m256 cmp = _mm256_cmp_ps (r2, max_r2, _CMP_LE_OQ);
                int   mask = _mm256_movemask_ps (cmp);
                
                if (!mask)
                    break;
                   
                iterations = _mm256_add_epi32(iterations, _mm256_and_si256(_mm256_castps_si256 (cmp), active_mask));

                m256_y = _mm256_mul_ps (m256_x, m256_y);
                m256_y = _mm256_add_ps (m256_y, m256_y);
                m256_y = _mm256_add_ps (m256_y, m256_y0);

                m256_x = _mm256_sub_ps (m256_x2, m256_y2);
                m256_x = _mm256_add_ps (m256_x, m256_x0);

                m256_x2 = _mm256_mul_ps (m256_x, m256_x);
                m256_y2 = _mm256_mul_ps (m256_y, m256_y);
            }

            memcpy (&vertex_array[index], (int*) &iterations, SIZE_AVX * sizeof (int));
            index += SIZE_AVX;

            m256_y0 = _mm256_add_ps (m256_y0, delta);
        }
        x0 += step_x;
    }
}
