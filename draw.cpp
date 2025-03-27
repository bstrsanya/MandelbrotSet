#include "common.h"

void draw (void (*GetPoint_func)(sfVertexArray* vertex_array, Param* param))
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
    sfText_setFont(text, font); 
    sfText_setCharacterSize(text, 30); 
    sfText_setColor(text, sfWhite);  

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
                        param.offsetY += param.scale * 0.1;
                        break;

                    case sfKeyLeft:
                        param.offsetX += param.scale * 0.1;
                        break;
                    
                    case sfKeyRight:
                        param.offsetX -= param.scale * 0.1;
                        break;

                    case sfKeyUp:
                        param.offsetY -= param.scale * 0.1;
                        break;

                    case sfKeyA:
                        param.scale *= 1.1;
                        break;
                    
                    case sfKeyS:
                        param.scale *= 0.9;
                        break;

                    case sfKeyH:
                        param.scale = 2;
                        param.offsetX = 0;
                        param.offsetY = 0;
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

        GetPoint_func (vertex_array, &param);

        sfRenderWindow_drawVertexArray(window, vertex_array, NULL);
        sfRenderWindow_drawText(window, text, NULL);

        sfRenderWindow_display(window);
    }

    sfFont_destroy(font);
    sfText_destroy(text);
    sfVertexArray_destroy(vertex_array);
    sfRenderWindow_destroy(window);
}