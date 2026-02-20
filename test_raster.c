#include "raster.h"
#include "font.h"
#include <osbind.h>
#include <stdio.h>

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 400
#define INVADER_HEIGHT 16

UINT16 invader_bitmap[INVADER_HEIGHT] = {
    0x0000,
    0x0060,
    0x0090,
    0x0108,
    0x0104,
    0x0108,
    0x0E10,
    0x0890,
    0x0910,
    0x0890,
    0x0410,
    0x03E0,
    0x0000,
    0x0000,
    0x0000,
    0x0000
};

/* Wait for key to be pressed*/
void wait_key(void) {
    Cnecin();
}


int main() {
    int r, c;
    void *base = Physbase();

    /*
    plot_something_1(base, 100, 100);
    plot_something_2(base, 200, 200);
    */

    /* clear_screen */
    clear_screen((UINT32 *)base);
    wait_key();

    /* plot_pixel*/
    clear_screen((UINT32 *)base);
    plot_pixel((UINT8 *)base, 0, 0);
    plot_pixel((UINT8 *)base, 0, SCREEN_WIDTH - 1);
    plot_pixel((UINT8 *)base, SCREEN_HEIGHT - 1, 0);
    plot_pixel((UINT8 *)base, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 1);
    wait_key();
    
    
    /* plot_horizontal_line and vertical_line*/
    clear_screen((UINT32 *)base);
    plot_horizontal_line((UINT32 *)base, 50, 50, 200);
    plot_vertical_line((UINT32 *)base, 50, 50, 150);
    wait_key();
    
    /* plot_line (generic line)*/
    clear_screen((UINT32 *)base);
    plot_line((UINT32 *)base, 10, 10, 300, 300);
    plot_line((UINT32 *)base, 300, 10, 10, 300);
    wait_key();
    
    /* plot_rectangle and plot_square */
    clear_screen((UINT32 *)base);
    plot_rectangle((UINT32 *)base, 100, 100, 200, 100);
    plot_square((UINT32 *)base, 350, 100, 80);
    wait_key();


    /* plot_triangle */
    clear_screen((UINT32 *)base);
    plot_triangle((UINT32 *)base, 250, 200, 60, 40);
    wait_key();

    /* 16-bit bitmap of a duck */
    clear_screen((UINT32 *)base);
    for (r = 0; r < INVADER_HEIGHT; r++) {
        for (c = 0; c < 16; c++) {
            if (invader_bitmap[r] & (0x8000 >> c)) {
                plot_pixel((UINT8 *)base, 50 + r, 50 + c);
            }
        }
    }
    wait_key();

    /* plot_charachter */
    clear_screen((UINT32 *)base);
    plot_character((UINT8 *)base, 'A', 100, 100);
    wait_key();


    /* plot_string (display SCORE on top right)*/
    plot_string((UINT8 *)base, 10, SCREEN_WIDTH - (5 * 8) - 10, "SCORE");
    wait_key();
    
    clear_screen((UINT32 *)base);
    return 0;
}
