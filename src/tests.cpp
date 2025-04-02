#include "common.h"

void tests ()
{
    Param param = {.offsetX = INIT_SHIFT, .offsetY = INIT_SHIFT, .scale = INIT_SCALE};
    int* vertex_array = (int*) calloc (WINDOW_HEIGHT * WINDOW_WIDTH, sizeof (int));

    uint64_t begin = get_rdtsc();
    
    for (int i = 0; i < SIZE_TEST; i++)
        GetPoint1 (vertex_array, &param);
    
    uint64_t end = get_rdtsc();

    double fps = (SIZE_TEST * 1.0f) / ((double)(end - begin) / cpu_freq);
    printf("(1 type) FPS: %lf\n", fps);

    begin = get_rdtsc();
    
    for (int i = 0; i < SIZE_TEST; i++)
        GetPoint2 (vertex_array, &param);
    
    end = get_rdtsc();

    fps = (SIZE_TEST * 1.0f) / ((double)(end - begin) / cpu_freq);
    printf("(2 type) FPS: %lf\n", fps);

    begin = __rdtsc();
    
    for (int i = 0; i < SIZE_TEST; i++)
        GetPoint3 (vertex_array, &param);
    
    end = get_rdtsc();

    fps = (SIZE_TEST * 1.0f) / ((double)(end - begin) / cpu_freq);
    printf("(3 type) FPS: %lf\n", fps);

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



