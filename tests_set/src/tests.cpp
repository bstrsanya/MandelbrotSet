#include "common.h"

void tests ()
{
    Param param = {.offsetX = 0, .offsetY = 0, .scale = 2};
    int* vertex_array = (int*) calloc (WINDOW_HEIGHT * WINDOW_WIDTH, sizeof (int));

    uint64_t begin = get_rdtsc();
    
    for (int i = 0; i < 10; i++)
        GetPoint2 (vertex_array, &param);
    
    uint64_t end = get_rdtsc();

    double fps = 10.0 / ((double)(end - begin) / cpu_freq);
    printf("FPS: %lf\n", fps);

    free (vertex_array);

}

uint64_t get_rdtsc()
{
    unsigned int lo, hi;
    __asm__ __volatile__ 
    (
        "rdtsc" : "=a" (lo), "=d" (hi)
    );
    return ((uint64_t) hi << 32) | lo;
}



