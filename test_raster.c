#include <osbind.h>
#include "raster.h"
#include "font.h"
#include <stdint.h>   // For UINT16, UINT32
#include <stdio.h>

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

int main()
{
    /*void *base = Physbase();

    
    plot_something_1(base, 100, 100);
    plot_something_2(base, 200, 200);
    */

        UINT32 *base = (UINT32 *)Physbase(); // Framebuffer base

    /* clear_screen */
    clear_screen(base);

    /* Draw invader bitmap at (50,50)*/
    for (int r = 0; r < INVADER_HEIGHT; r++) {
        for (int c = 0; c < 16; c++) {
            if (invader_bitmap[r] & (0x8000 >> c)) {
                plot_pixel(base, 50 + r, 50 + c);
            }
        }
    }
    
    /* plot_horizontal_line at (350, 50) that has length: 120 */
    plot_horizontal_line(base, 350, 50, 120);

    /* plot_vertical_line at (50, 300) that has length: 120 */
    plot_vertical_line(base, 50, 300, 120);

    /* plot_rectangle at (100,100) that is the size: 40x80*/
    plot_rectangle(base, 100, 100, 40, 80);

    /* plot_square at (150,150) with the size: 50x50*/
    plot_square(base, 150, 150, 50);

    /* plot_triangle at (250,200) with base: 60, height: 40, and is a right angle*/
    plot_triangle(base, 250, 200, 60, 40, 0);

    /* draw a test string for score */
    plot_string((UINT8 *)base, 20, 400, "Score");


    return 0;
}

