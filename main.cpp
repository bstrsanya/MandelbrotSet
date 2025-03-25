#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH  2000
#define WINDOW_HEIGHT 2000

typedef struct {
    float x, y; 
    sfColor color;
} Point;

int main() 
{
    sfRenderWindow* window;
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    window = sfRenderWindow_create(mode, "Display Points Together", sfResize | sfClose, NULL);

    sfVertexArray* vertex_array = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(vertex_array, sfPoints);

    double offsetX = 0;
    double offsetY = 0;

    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }
        }

        if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
            offsetX += 0.5;
        }
        if (sfKeyboard_isKeyPressed(sfKeyRight)) {
            offsetX -= 0.5;
        }
        if (sfKeyboard_isKeyPressed(sfKeyUp))   {
            offsetY -= 0.5;
        }
        if (sfKeyboard_isKeyPressed(sfKeyDown))   {
            offsetY += 0.5;
        }

        sfRenderWindow_clear(window, sfBlack);
        sfVertexArray_clear(vertex_array);

        for (double x = 0; x < WINDOW_WIDTH; x++)
        {
            for (double y = 0; y < WINDOW_HEIGHT; y++)
            {
                double cx = (x - (WINDOW_WIDTH / 2)) / (WINDOW_WIDTH / 2) - offsetX;
                double cy = (- y + (WINDOW_HEIGHT / 2)) / (WINDOW_HEIGHT / 2) - offsetY;

                double z_x = 0.0f, z_x2 = 0.0f,
                z_y = 0.0f, z_y2 = 0.0f;

                int iterations = 0;

                while (z_x2 + z_y2 < 4 &&
                        iterations < 255) 
                {
                    z_y = 2 * z_x * z_y + cy;
                    z_x = z_x2 - z_y2 + cx;

                    z_x2 = z_x * z_x;
                    z_y2 = z_y * z_y;

                    iterations++;
                }

                sfVertex vertex;

                const float colorScale = 255.0f / 256;
                const float iterNormalized = iterations * colorScale;
                if (iterations >= 255)
                    vertex.color = sfColor_fromRGB(0, 0, 0);
                else
                    vertex.color = sfColor_fromRGB(iterNormalized * 2, iterNormalized * 10 + 2, iterNormalized * 1 + 5);



                vertex.position = (sfVector2f){x,y};
                sfVertexArray_append(vertex_array, vertex);
                
            }
        }
        sfRenderWindow_drawVertexArray(window, vertex_array, NULL);

        sfRenderWindow_display(window);

    }
    sfVertexArray_destroy(vertex_array);
    sfRenderWindow_destroy(window);

    return 0;
}
