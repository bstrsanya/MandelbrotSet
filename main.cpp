#include <SFML/Graphics.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 1000

struct Param {
    double offsetX;
    double offsetY;
    double scale;
};

void GetPoint (sfVertexArray* vertex_array, Param* param);

int main() 
{
    sfRenderWindow* window;
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 8};
    window = sfRenderWindow_create(mode, "Mandelbrot", sfClose, NULL);

    sfVertexArray* vertex_array = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(vertex_array, sfPoints);

    Param param = {.offsetX = 0, .offsetY = 0, .scale = 2};

    sfClock* clock = sfClock_create(); 

    sfFont* font = sfFont_createFromFile("1.otf");
    
    sfText* text = sfText_create();
    sfText_setFont(text, font);  // Устанавливаем шрифт
    sfText_setCharacterSize(text, 30);  // Устанавливаем размер шрифта
    sfText_setColor(text, sfWhite);  // Устанавливаем цвет текста

    while (sfRenderWindow_isOpen(window)) 
    {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) 
        {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            
            if (event.type == sfEvtKeyPressed) 
            {
                switch ((int) event.key.code)
                {
                    case sfKeyDown:
                        param.offsetY += 0.5;
                        break;

                    case sfKeyLeft:
                        param.offsetX += 0.5;
                        break;
                    
                    case sfKeyRight:
                        param.offsetX -= 0.5;
                        break;

                    case sfKeyUp:
                        param.offsetY -= 0.5;
                        break;

                    case sfKeyA:
                        param.scale += 0.5;
                        break;
                    
                    case sfKeyS:
                        param.scale -= 0.5;
                        break;
                }
            }
        }

        sfTime deltaTime = sfClock_getElapsedTime(clock);
        float deltaTimeSeconds = sfTime_asSeconds(deltaTime);

        float fps = 1.0f / deltaTimeSeconds;

        sfClock_restart(clock);

        char fpsString[50];
        sprintf(fpsString, "FPS: %.1f", fps);
        sfText_setString(text, fpsString);

        sfText_setPosition(text, (sfVector2f){0.0f, 0.0f});

        sfRenderWindow_clear(window, sfBlack);

        sfVertexArray_clear(vertex_array);

        GetPoint (vertex_array, &param);

        sfRenderWindow_drawVertexArray(window, vertex_array, NULL);
        sfRenderWindow_drawText(window, text, NULL);

        sfRenderWindow_display(window);
    }

    // Освобождение ресурсов
    sfFont_destroy(font);
    sfText_destroy(text);
    sfVertexArray_destroy(vertex_array);
    sfRenderWindow_destroy(window);

    return 0;
}

void GetPoint (sfVertexArray* vertex_array, Param* param)
{
    for (double x = 0; x < WINDOW_WIDTH; x++)
        {
            for (double y = 0; y < WINDOW_HEIGHT; y++)
            {
                double cx = (x - (WINDOW_WIDTH / 2)) / (WINDOW_WIDTH / param->scale) - param->offsetX;
                double cy = (- y + (WINDOW_HEIGHT / 2)) / (WINDOW_HEIGHT / param->scale) - param->offsetY;

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

                vertex.position = (sfVector2f){x, y};
                sfVertexArray_append(vertex_array, vertex);
            }
        }
}

