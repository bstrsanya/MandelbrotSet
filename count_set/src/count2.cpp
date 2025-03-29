#include "common.h"

void GetPoint2 (int* vertex_array, Param* param)
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

// for (int j = 0; j < 8; j++)
            //     vertex_array[index + j] = iter_values[j];


// for (int j = 0; j < 8; j++)
            // {
            //     int color_index = iter_values[j];
                
            //     sfVertex vertex = {
            //         .position = {x_pixel, y_pixel + j},
            //         .color = sfColor_fromRGB(array[color_index].red, 
            //                                  array[color_index].green, 
            //                                  array[color_index].blue)
            //     };
            //     sfVertexArray_append(vertex_array, vertex);
            // }
