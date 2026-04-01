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

UINT16 capitalA[] = {
    0x1FF8,
    0x1FF8,
    0x6006,
    0x6006,
    0x6006,
    0x6006,
    0x6006,
    0x6006,
    0x6006,
    0x7EFE,
    0x7EFE,
    0x6006,
    0x6006,
    0x6006,
    0x6006,
    0x6006,
};

UINT16 capitalS[] = {
    0x0000,
    0x0FFE,
    0x0FFE,
    0x3000,
    0x3000,
    0x3000,
    0x3000,
    0x0FF0,
    0x0FF0,
    0x0006,
    0x0006,
    0x0006,
    0x0006,
    0x3FF8,
    0x3FF8,
    0x0000
};

UINT16 capitalH[] = {
    0x0000,
    0x6006,
    0x6006,
    0x6006,
    0x6006,
    0x6006,
    0x6006,
    0x7FFE,
    0x7FFE,
    0x6006,
    0x6006,
    0x6006,
    0x6006,
    0x6006,
    0x6006,
    0x0000
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

void initilizeSplashScreen(UINT8 *base) {
    char *one_player = "Single Player (1)";
    char *two_player = "Two Player (2)";
    char *quit_game = "Quit Game (3)";

    clearScreen(base);

    plot_16bit_bitmap(base, 50, 50, capitalD, 16);
    plot_16bit_bitmap(base, 50, 70, capitalU, 16);
    plot_16bit_bitmap(base, 50, 90, capitalC, 16);
    plot_16bit_bitmap(base, 50, 110, capitalK, 16);

}