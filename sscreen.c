#include <stdio.h>

#include "sscreen.h"
#include "font.c"
#include "raster.h"
#include "input.h"

UINT16 capitalD[] = {
    0xFFF8,
    0xFFFC,
    0xFFFE,
    0xF01F,
    0xF00F,
    0xF007,
    0xF007,
    0xF007,
    0xF007,
    0xF007,
    0xF007,
    0xF00F,
    0xF01F,
    0xFFFE,
    0xFFFC,
    0xFFF8,
};

int startScreen(UINT8 *base)
{

    int selection = 0;
    long input = 0;
    int result = 0;
    int i;

    initSplash(base);

    input = 0;
    while (selection == 0)
    {
        input = getKey();
        if (input != 0)
        {
            switch (input)
            {
            case '1':
                selection = 1;
                break;

            case '2':
                break;

            case '3':
            selection = 3;
                break;

            default:
                break;
            }
        }
    }
    return selection;
}