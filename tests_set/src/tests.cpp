#include "common.h"

void tests ()
{
    Param param = {.offsetX = 0, .offsetY = 0, .scale = 2};
    sfVertexArray* vertex_array = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(vertex_array, sfPoints);

    clock_t t1 = clock ();
    for (int i = 0; i < 10; i++)
    {
        GetPoint (vertex_array, &param);
    }
    clock_t t2 = clock ();

    double elapsed_time = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("0: FPS: %.2lf \n", 10 / elapsed_time);

    t1 = clock ();
    for (int i = 0; i < 10; i++)
    {
        GetPoint1 (vertex_array, &param);
    }
    t2 = clock ();

    elapsed_time = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("1: FPS: %.2lf \n", 10 / elapsed_time);

    t1 = clock ();
    for (int i = 0; i < 10; i++)
    {
        GetPoint2 (vertex_array, &param);
    }
    t2 = clock ();

    elapsed_time = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("2: FPS: %.2lf \n", 10 / elapsed_time);
}