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

UINT16 capitalU[] = {
    0x0000,
    0xC003,
    0xC003,
    0xC003,
    0xC003,
    0xC003,
    0xC003,
    0xC003,
    0xC003,
    0xC003,
    0xC003,
    0xC003,
    0xC003,
    0x3FFC,
    0x3FFC
};

UINT16 capitalC[] = {
    0x0000,
    0x1FFE,
    0x1FFE,
    0x6000,
    0x6000,
    0x6000,
    0x6000,
    0x6000,
    0x6000,
    0x6000,
    0x6000,
    0x6000,
    0x6000,
    0x1FFE,
    0x1FFE,
    0x0000
};

UINT16 capitalK[] = {
    0x0000,
    0x6010,
    0x6030,
    0x6060,
    0x60C0,
    0x6180,
    0x6300,
    0x7E00,
    0x7E00,
    0x6300,
    0x6180,
    0x60C0,
    0x6060,
    0x6030
};

int startScreen(UINT8 *base)
{

    int selection = 0;
    long input = 0;
    int result = 0;
    int i;

    initilizeSplashScreen(base);

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