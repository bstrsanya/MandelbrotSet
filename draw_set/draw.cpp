#include "common.h"

void draw (void (*GetPoint_func)(int* vertex_array, Param* param))
{
    sfRenderWindow* window;
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 8};
    window = sfRenderWindow_create(mode, "Mandelbrot", sfClose, NULL);

    sfVertexArray* vertex_array = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(vertex_array, sfPoints);

    Param param = {.offsetX = 0, .offsetY = 0, .scale = 2};

    sfClock* clock = sfClock_create(); 

    sfFont* font = sfFont_createFromFile("./draw_set/1.otf");
    
    sfText* text = sfText_create();
    sfText_setFont(text, font); 
    sfText_setCharacterSize(text, 30); 
    sfText_setColor(text, sfBlue);  

    Color* array = (Color*) calloc (MAX_NUM_ITER + 1, sizeof (Color));
    GetColor (array);

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
                        param.offsetY += param.scale * 0.1f;
                        break;

                    case sfKeyLeft:
                        param.offsetX += param.scale * 0.1f;
                        break;
                    
                    case sfKeyRight:
                        param.offsetX -= param.scale * 0.1f;
                        break;

                    case sfKeyUp:
                        param.offsetY -= param.scale * 0.1f;
                        break;

                    case sfKeyA:
                        param.scale *= 1.1f;
                        break;
                    
                    case sfKeyS:
                        param.scale *= 0.9f;
                        break;

                    case sfKeyH:
                        param.scale = 2.0f;
                        param.offsetX = 0.0f;
                        param.offsetY = 0.0f;

                    default:
                        break;
                }
            }
        }

        sfTime deltaTime = sfClock_getElapsedTime(clock);
        float deltaTimeSeconds = sfTime_asSeconds(deltaTime);

        float fps = 1.0f / deltaTimeSeconds;

        sfClock_restart(clock);

        char fpsString[20];
        sprintf(fpsString, "FPS: %.1f", fps);
        sfText_setString(text, fpsString);

        sfText_setPosition(text, (sfVector2f){0.0f, 0.0f});

        sfRenderWindow_clear(window, sfBlack);

        sfVertexArray_clear(vertex_array);

        int* arr = (int*) calloc (WINDOW_HEIGHT * WINDOW_WIDTH, sizeof (int));
        GetPoint_func (arr, &param);

        for (int x = 0; x < WINDOW_WIDTH; x++)
        {
            for (int y = 0; y < WINDOW_HEIGHT; y++)
            {
                sfVertex vertex = {
                    .position = {(float) x, (float) y},
                    .color = sfColor_fromRGB(array[arr[x * WINDOW_HEIGHT + y]].red, 
                                             array[arr[x * WINDOW_HEIGHT + y]].green, 
                                             array[arr[x * WINDOW_HEIGHT + y]].blue)
                };
                sfVertexArray_append(vertex_array, vertex);
            }
        }

        free (arr);


        sfRenderWindow_drawVertexArray(window, vertex_array, NULL);
        sfRenderWindow_drawText(window, text, NULL);

        sfRenderWindow_display(window);
    }

    sfFont_destroy(font);
    sfText_destroy(text);
    sfVertexArray_destroy(vertex_array);
    sfRenderWindow_destroy(window);
    sfClock_destroy (clock);
    free(array);
}