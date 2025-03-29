#include "common.h"
#include <immintrin.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

uint64_t get_rdtsc()
{
    unsigned int lo, hi;
    __asm__ __volatile__ (
        "rdtsc" : "=a" (lo), "=d" (hi)
    );
    return ((uint64_t)hi << 32) | lo;
}

void tests (Color* array)
{
    Param param = {.offsetX = 0, .offsetY = 0, .scale = 2};
    sfVertexArray* vertex_array = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(vertex_array, sfPoints);

    FILE* fp = fopen("/proc/cpuinfo", "r");
    double cpu_freq = 0;
    if (fp)
    {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), fp))
        {
            if (sscanf(buffer, "cpu MHz\t: %lf", &cpu_freq) == 1)
            {
                cpu_freq *= 1000000; 
                break;
            }
        }
        fclose(fp);
    }

    uint64_t a = get_rdtsc();
    
    for (int i = 0; i < 100; i++)
    {
        GetPoint (vertex_array, &param, array);
    }
    
    uint64_t b = get_rdtsc();

    uint64_t time_in_cycles = b - a;

    double time_in_seconds = (double)time_in_cycles / cpu_freq;

    double fps = 100.0 / time_in_seconds;

    printf("FPS: %lf\n", fps);


    // t1 = clock ();
    // for (int i = 0; i < 100; i++)
    // {
    //     GetPoint2 (vertex_array, &param, array);
    // }
    // t2 = clock ();

    // elapsed_time = (double)(t2 - t1) / CLOCKS_PER_SEC;
    // printf("1: FPS: %.2lf \n", 100 / elapsed_time);

    // t1 = clock ();
    // for (int i = 0; i < 20; i++)
    // {
    //     GetPoint2 (vertex_array, &param);
    // }
    // t2 = clock ();

    // elapsed_time = (double)(t2 - t1) / CLOCKS_PER_SEC;
    // printf("2: FPS: %.2lf \n", 20 / elapsed_time);

    sfVertexArray_destroy(vertex_array);
}



