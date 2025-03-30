#include "common.h"

int main(int argc, char** argv) 
{
    if (argc != 2)
    {
        printf ("Enter 1 command line argument\n");
        return 0;
    }

    if (!strcmp (argv[1], "tests"))
        tests ();
    
    else if (!strcmp (argv[1], "draw_type1"))
        draw (GetPoint1);
    
    else if (!strcmp (argv[1], "draw_type2"))
        draw (GetPoint2);
    
    else if (!strcmp (argv[1], "draw_type3"))
        draw (GetPoint3);
    else
    {
        printf ("Correct arg: [tests], [draw_type1], [draw_type2], [draw_type3]\n");
    }

    return 0;
}
