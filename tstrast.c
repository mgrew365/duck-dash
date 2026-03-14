/*
File: TSTRAST.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: March 14, 2026
File Description: This file is a test driver for the raster graphics library.
                  It verifies the functionality of the routines implemented in raster.c
                  which include clearing the screen, plotting pixels, drawing lines, 
                  shapes, characters, strings, and a bitmap image. Each test is displayed
                  on a blank screen and the user must press any button to see 
                  a visual drawing. In between each drawing, any key must be pressed
                  to see the next drawing. The screen should be cleared between each click.
*/

/* check borders */
/* dont have to fill the boxes */
#include "raster.h"
#include "font.h"
#include <osbind.h>
#include <stdio.h>

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 400
#define DUCK_HEIGHT 32

const UINT32 duck_bitmap[32] = {
    0x00000000,
    0x00000000,
    0x000FE000,
    0x000FE000,
    0x00301800,
    0x00301800,
    0x00301800,
    0x00C0C600,
    0x00C0C600,
    0x00C0C600,
    0x00C00180,
    0x00C00180,
    0x00C00180,
    0x00C00600,
    0x0F000600,
    0x0F000600,
    0x0F000600,
    0x0C181800,
    0x0C181800,
    0x0C181800,
    0x0C601800,
    0x0C601800,
    0x0C601800,
    0x0C181800,
    0x0C181800,
    0x0C181800,
    0x03001800,
    0x03001800,
    0x03001800,
    0x00FFE000,
    0x00FFE000,
    0x00000000
};

/* Wait for key to be pressed*/
void wait_key(void) {
    Cnecin();
}

int main() {
    void *base = Physbase();

    /* Clear screen */
    clear_screen((UINT32 *)base);
    wait_key();

    /* Plot single pixels - corners & out-of-bounds */
    clear_screen((UINT32 *)base);
    plot_pixel((UINT8 *)base, 0, 0);
    plot_pixel((UINT8 *)base, 0, SCREEN_WIDTH-1);
    plot_pixel((UINT8 *)base, SCREEN_HEIGHT-1, 0);
    plot_pixel((UINT8 *)base, SCREEN_HEIGHT-1, SCREEN_WIDTH-1);
    plot_pixel((UINT8 *)base, -5, 10);
    plot_pixel((UINT8 *)base, 100, SCREEN_WIDTH+10);
    wait_key();

    /* Horizontal & vertical lines (normal + clipped) */
    clear_screen((UINT32 *)base);
    plot_horizontal_line((UINT32 *)base, 50, 50, 100);
    plot_horizontal_line((UINT32 *)base, 60, -20, 100);
    plot_horizontal_line((UINT32 *)base, 70, 600, 100);
    plot_vertical_line((UINT32 *)base, 80, 100, 150);
    plot_vertical_line((UINT32 *)base, -30, 150, 50);
    plot_vertical_line((UINT32 *)base, 350, 200, 100);
    wait_key();

    /* Arbitrary lines (horizontal, vertical, diagonal) */
    clear_screen((UINT32 *)base);
    plot_line((UINT32 *)base, 10, 10, 200, 10);
    plot_line((UINT32 *)base, 10, 10, 10, 200);
    plot_line((UINT32 *)base, 10, 10, 200, 200);
    plot_line((UINT32 *)base, 200, 10, 10, 200);
    plot_line((UINT32 *)base, -50, -50, 50, 50);
    wait_key();

    /* Rectangles and squares */
    clear_screen((UINT32 *)base);
    plot_rectangle((UINT32 *)base, 100, 100, 200, 150);
    plot_rectangle((UINT32 *)base, -20, 300, 50, 80);
    plot_square((UINT32 *)base, 300, 500, 100);
    plot_square((UINT32 *)base, SCREEN_HEIGHT+10, 10, 30);
    wait_key();

    /* Triangles - all directions */
    clear_screen((UINT32 *)base);
    plot_triangle((UINT32 *)base, 50, 50, 60, 40, 0);
    plot_triangle((UINT32 *)base, 50, 150, 60, 40, 1);
    plot_triangle((UINT32 *)base, 150, 50, 60, 40, 2);
    plot_triangle((UINT32 *)base, 150, 150, 60, 40, 3);
    plot_triangle((UINT32 *)base, 100, SCREEN_WIDTH - 60, 100, 80, 0); /* top-left right-angle triangle */

    wait_key();

    /* 32-bit bitmap (duck) - normal + clipped */
    clear_screen((UINT32 *)base);
    plot_32bit_bitmap((UINT32 *)base, 100, 100, duck_bitmap, DUCK_HEIGHT);
    plot_32bit_bitmap((UINT32 *)base, -10, -10, duck_bitmap, DUCK_HEIGHT);
    plot_32bit_bitmap((UINT32 *)base, SCREEN_HEIGHT-16, SCREEN_WIDTH-16, duck_bitmap, DUCK_HEIGHT);
    wait_key();

    /* Characters & strings */
    clear_screen((UINT32 *)base);
    plot_character((UINT8 *)base, 100, 100, 'A');
    plot_character((UINT8 *)base, -5, 50, 'B');
    plot_string((UINT8 *)base, 200, 200, "HELLO WORLD");
    plot_string((UINT8 *)base, 395, SCREEN_WIDTH-20, "END");
    plot_string((UINT8 *)base, 10, SCREEN_WIDTH - (5*8) - 10, "SCORE");
    plot_string((UINT8 *)base, SCREEN_HEIGHT - 16, SCREEN_WIDTH - (12*8) - 10, "GAME OVER"); 
    wait_key();

    /* Done */
    clear_screen((UINT32 *)base);
    return 0;
}