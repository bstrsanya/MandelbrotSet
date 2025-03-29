#include "common.h"

int main() 
{
    // tests ();

    // draw (GetPoint);

    Color* array_color = (Color*) calloc (101, sizeof (Color));
    GetColor (array_color);

    // for (int i = 0; i < 101; i++)
    // {
    //     printf ("%d %d %d\n", array_color[i].red, array_color[i].green, array_color[i].blue);
    // }

    // draw (GetPoint2, array_color);
    tests (array_color);

    free(array_color);

    return 0;
}
