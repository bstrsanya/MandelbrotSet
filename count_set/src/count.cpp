#include "common.h"

void GetPoint (sfVertexArray* vertex_array, Param* param, Color* array)
{
    for (float x_pixel = 0; x_pixel < WINDOW_WIDTH; x_pixel++)
    {
        for (float y_pixel = 0; y_pixel < WINDOW_HEIGHT; y_pixel++)
        {
            float cx = (x_pixel - (WINDOW_WIDTH / 2)) / (WINDOW_WIDTH / param->scale) - param->offsetX;
            float cy = (- y_pixel + (WINDOW_HEIGHT / 2) ) / (WINDOW_HEIGHT / param->scale) - param->offsetY;

            float z_x = 0.0f;
            float z_x2 = 0.0f;
            float z_y = 0.0f;
            float z_y2 = 0.0f;

            int iterations = 0;

            while (z_x2 + z_y2 < 100 && iterations < 100) 
            {
                z_y = 2 * z_x * z_y + cy;
                z_x = z_x2 - z_y2 + cx;

                z_x2 = z_x * z_x;
                z_y2 = z_y * z_y;

                iterations++;
            }

            sfVertex vertex = {};

            vertex.color = sfColor_fromRGB(array[iterations].red, array[iterations].green, array[iterations].blue);
            vertex.position = (sfVector2f){x_pixel, y_pixel};
            sfVertexArray_append(vertex_array, vertex);
        }
    }
}

// массив цветов и синусы и косинусы
// наивная сами циклы разварачиваем и интринсики
// rdtsc