#include "common.h"

void GetPoint2 (sfVertexArray* vertex_array, Param* param)
{
    float x0 = (0 - (WINDOW_WIDTH  / 2)) / (WINDOW_WIDTH / param->scale) - param->offsetX;
    float y0 = (0 + (WINDOW_HEIGHT / 2)) / (WINDOW_HEIGHT / param->scale) - param->offsetY;

    float step_x = 1  / (WINDOW_WIDTH  / param->scale);
    float step_y = -1 / (WINDOW_HEIGHT / param->scale);

    __m128 max_r2 = _mm_set_ps1 (4);
    __m128 _0123 = _mm_set_ps (0, 1, 2, 3);
    __m128 delta = _mm_mul_ps (_mm_set_ps1 (4), _mm_set_ps1 (step_y));
    
    for (float x_pixel = 0; x_pixel < WINDOW_WIDTH; x_pixel += 1)
    {
        __m128 m128_x0 = _mm_set_ps1 (x0);
        __m128 m128_y0 = _mm_add_ps (_mm_set_ps1 (y0), _mm_mul_ps (_0123, _mm_set_ps1 (step_y)));

        for (float y_pixel = 0; y_pixel < WINDOW_HEIGHT; y_pixel += 4)
        {
            __m128 m128_x  = _mm_setzero_ps();
            __m128 m128_x2 = _mm_setzero_ps();
            __m128 m128_y  = _mm_setzero_ps();
            __m128 m128_y2 = _mm_setzero_ps();
            
            __m128 active_mask = _mm_set_ps1(1.0f);
            __m128 iterations = _mm_setzero_ps();

            int i = 0;
            while (i < 255) 
            {
                __m128 r2 = _mm_add_ps (m128_x2, m128_y2);
                __m128 cmp = _mm_cmple_ps (r2, max_r2);
                int mask = _mm_movemask_ps (cmp);
                if (!mask)
                    break;
                   
                __m128 still_active = _mm_and_ps(cmp, active_mask);
                iterations = _mm_add_ps(iterations, still_active);
                active_mask = still_active;
                
                m128_y = _mm_mul_ps (m128_x, m128_y);
                m128_y = _mm_add_ps (m128_y, m128_y);
                m128_y = _mm_add_ps (m128_y, m128_y0);

                m128_x = _mm_sub_ps (m128_x2, m128_y2);
                m128_x = _mm_add_ps (m128_x, m128_x0);

                m128_x2 = _mm_mul_ps (m128_x, m128_x);
                m128_y2 = _mm_mul_ps (m128_y, m128_y);

                i++;
            }

            for (int i = 0; i < 4; i++)
            {
                sfVertex vertex = {};
                Color color = {};
                GetColor(iterations[3-i], &color);
                vertex.color = sfColor_fromRGB(color.red, color.green, color.blue);
                vertex.position = (sfVector2f){x_pixel, y_pixel + i};
                sfVertexArray_append(vertex_array, vertex);
            }

            m128_y0 = _mm_add_ps (m128_y0, delta);
        }
        x0 = x0 + step_x;
    }
}

