#include "common.h"
#include <assert.h>

void GetPoint1 (sfVertexArray* vertex_array, Param* param)
{
    float cx = (0 - (WINDOW_WIDTH / 2)) / (WINDOW_WIDTH / param->scale) - param->offsetX;
    float cy = (0 + (WINDOW_HEIGHT / 2)) / (WINDOW_HEIGHT / param->scale) - param->offsetY;
    float y0 = cy;
    float step_x = 1 / (WINDOW_WIDTH / param->scale);
    float step_y = -step_x;
    
    for (float x_pixel = 0; x_pixel < WINDOW_WIDTH; x_pixel++)
    {
        cy = y0;
        for (float y_pixel = 0; y_pixel < WINDOW_HEIGHT; y_pixel++)
        {
            float z_x = 0.0f;
            float z_x2 = 0.0f;
            float z_y = 0.0f;
            float z_y2 = 0.0f;

            int iterations = 0;

            while (z_x2 + z_y2 < 4 && iterations < 255) 
            {
                z_y = 2 * z_x * z_y + cy;
                z_x = z_x2 - z_y2 + cx;

                z_x2 = z_x * z_x;
                z_y2 = z_y * z_y;

                iterations++;
            }

            sfVertex vertex = {};
            Color color = {};
            GetColor (iterations, &color);
            vertex.color = sfColor_fromRGB(color.red, color.green, color.blue);

            vertex.position = (sfVector2f){x_pixel, y_pixel};
            sfVertexArray_append(vertex_array, vertex);

            cy = cy + step_y;
        }
        cx = cx + step_x;
    }
}

