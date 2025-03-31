# MandelbrotSet

## Installation
```
sudo dnf install CSFML
```
## Program launch
```
make
./main <arg>
```
```
arg = tests | draw_type1 | draw_type2 | draw_type3
```
**tests** - run only test calculations

**draw_type1** - first version graphics window

**draw_type2** - second version graphics window

**draw_type3** - third version graphics window

## Description

Three versions of calculating the points of the Mandelbrot set are implemented with the same algorithm. The difference is only in the optimization of these calculations.

The first version implements a naive algorithm, where each point is calculated separately.
```
int iter = 0;
while (x2 + y2 < MAX_RAD_2 && iter < MAX_NUM_ITER) 
{
    y = 2 * x * y + y0;
    x = x2 - y2 + x0;

    x2 = x * x;
    y2 = y * y;

    iter++;
}
```

The second version implements manual loop unrolling and with the **$-O3$** compilation flag, performance increases by almost 2 times.
```
int iterations[SIZE_AVX] = {};
for (int i = 0; i < MAX_NUM_ITER; i++)
{
    float r2[SIZE_AVX]  = {};
    for (int k = 0; k < SIZE_AVX; k++) r2[k] = x2[k] + y2[k];

    int cmp[SIZE_AVX] = {};
    for (int k = 0; k < SIZE_AVX; k++) cmp[k] = r2[k] < max_r2 ? 1 : 0;

    int mask = 0;
    for (int k = 0; k < SIZE_AVX; k++) mask += (cmp[k] == 0);                
    if (mask == SIZE_AVX)
        break;
        
    for (int k = 0; k < SIZE_AVX; k++) iterations[k] += (cmp[k] != 0);

    for (int k = 0; k < SIZE_AVX; k++) y[k] = y[k] * x[k] * 2 + y0[k];
    for (int k = 0; k < SIZE_AVX; k++) x[k] = x2[k] - y2[k] + x0[k];

    for (int k = 0; k < SIZE_AVX; k++) x2[k] = x[k] * x[k];
    for (int k = 0; k < SIZE_AVX; k++) y2[k] = y[k] * y[k];
}
```

The third version uses 256-bit AVX instructions, which allow for simultaneous calculation of multiple points. With the -O3 compilation flag, there is a 6x acceleration.
```
__m256i iterations = _mm256_setzero_si256();

for (int i = 0; i < MAX_NUM_ITER; i++)
{
    __m256 r2  = _mm256_add_ps (m256_x2, m256_y2);
    __m256 cmp = _mm256_cmp_ps (r2, max_r2, _CMP_LE_OQ);
    int   mask = _mm256_movemask_ps (cmp);
    
    if (!mask)
        break;
        
    iterations = _mm256_add_epi32(iterations, 
                                _mm256_and_si256(_mm256_castps_si256 (cmp), active_mask));

    m256_y = _mm256_mul_ps (m256_x, m256_y);
    m256_y = _mm256_add_ps (m256_y, m256_y);
    m256_y = _mm256_add_ps (m256_y, m256_y0);

    m256_x = _mm256_sub_ps (m256_x2, m256_y2);
    m256_x = _mm256_add_ps (m256_x, m256_x0);

    m256_x2 = _mm256_mul_ps (m256_x, m256_x);
    m256_y2 = _mm256_mul_ps (m256_y, m256_y);
}
```


## Example of work

<img src="./gif/example.gif" width="400" height="400"/>

### Functional

| key | value |
| :-: | :---: |
| 🡠 | shift to left  |
| 🡡 | shift to up |
| 🡢 | shift to right |
| 🡣 | shift to down |
| S | zoom in |
| A | zoom out |
| H | return to initial position |

## Program speed

Below are the FPS (frame per second) for all program variations.

> [!Note]
> Since displaying an image on the screen takes a lot of time, which does not depend on the speed of calculating coordinates, I preferred to split the time with and without rendering.

Optimization with flag **$-O0$**
| Version | With rendering | Just calculation | 
| :-----: | :------------: | :-------: |
| 1       |       8.1      |   8.8     |
| 2       |       2.4      |   2.9     |
| 3       |       18.7     |   20.9    |

Optimization with flag **$-O3$** 

| Version | With rendering | Just calculation | 
| :-----: | :------------: | :-------: |
| 1       |        18.7    |      19.9 |
| 2       |        35.9    |      39.6 |
| 3       |        109.1    |      121.3|

When calling the **draw** function, the FPS is shown taking into account rendering, and when calling the **tests** function, without it.

## Characteristics of the testing machine

Intel(R) Core(TM) Ultra 7 155H

CPU average MHz: 4000


