#include "common.h"

void GetPoint2 (sfVertexArray* vertex_array, Param* param)
{
    float cx = (0 - (WINDOW_WIDTH / 2)) / (WINDOW_WIDTH / param->scale) - param->offsetX;
    float cy = (0 + (WINDOW_HEIGHT / 2)) / (WINDOW_HEIGHT / param->scale) - param->offsetY;
    float y0 = cy;
    float step_x = 1 / (WINDOW_WIDTH / param->scale);
    float step_y = -step_x;

    __m128 r = _mm_set_ps1 (4);
    __m128 q = _mm_set_ps1 (2);
    __m128 _0123 = _mm_set_ps (0, 1, 2, 3);
    
    for (float x_pixel = 0; x_pixel < WINDOW_WIDTH; x_pixel += 1)
    {
        __m128 cxx = _mm_set_ps1 (cx);
        __m128 c_yy = _mm_add_ps (_mm_set_ps1 (y0), _mm_mul_ps (_0123, _mm_set_ps1 (step_y)));

        for (float y_pixel = 0; y_pixel < WINDOW_HEIGHT; y_pixel += 4)
        {
            __m128 z_x = _mm_setzero_ps();
            __m128 z_x2 = _mm_setzero_ps();
            __m128 z_y = _mm_setzero_ps();
            __m128 z_y2 = _mm_setzero_ps();
            

            __m128 active_mask = _mm_set_ps1(1.0f);
            __m128 iterations = _mm_setzero_ps();
            int i = 0;
            while (i < 255) 
            {
                __m128 r2 = _mm_add_ps (z_x2, z_y2);
                __m128 cmp = _mm_cmple_ps (r2, r);
                int mask = _mm_movemask_ps (cmp);
                if (!mask)
                    break;
                   
                __m128 still_active = _mm_and_ps(cmp, active_mask);
                iterations = _mm_add_ps(iterations, still_active);
                active_mask = still_active;
                
                z_y = _mm_mul_ps (z_x, z_y);
                z_y = _mm_add_ps (z_y, z_y);
                z_y = _mm_add_ps (z_y, c_yy);

                z_x = _mm_sub_ps (z_x2, z_y2);
                z_x = _mm_add_ps (z_x, cxx);

                z_x2 = _mm_mul_ps (z_x, z_x);
                z_y2 = _mm_mul_ps (z_y, z_y);

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

            c_yy = _mm_add_ps (c_yy, _mm_mul_ps (r, _mm_set_ps1 (step_y)));
        }
        cx = cx + step_x;
    }
}

