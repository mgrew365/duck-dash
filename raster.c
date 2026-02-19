#include "raster.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BYTES_PER_ROW (SCREEN_WIDTH / 8)
/*----- Function: clear_screen -----
v
 PURPOSE: Clears the entire screen.

 INPUT: Address(UINT32*): to the start of the screen

 OUTPUT: None

*/
void clear_screen(UINT32 *base) {
    register int i = 0;
    register UINT32 *location = (UINT32 *)base;

    while (i++ < BYTES_PER_ROW / 4) {
        *(location++) = 0x00000000;
    }
}

/*----- Function: clear_region -----

 PURPOSE: Clear a region of the screen. The section is specified by the coordinates of the top left corner, and the height and width of the region.

 INPUT: Address(UINT32*): to the start of the screen
        Position(row,col): the coordinates of the top left pixel of the region
        Length: the lenth (number of rows) in pixels of the region
        Width: the width (number of columns) in pixels of the region

 OUTPUT: None

*/
       
void clear_region(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width) {
    UINT16 r, c;

    for (r = 0; r < length; r++) {
        for (c = 0; c < width; c++) {
            plot_pixel((UINT8 *)base, row + r, col + c);
        }
    }
}

/*----- Function: plot_pixel -----

 PURPOSE: Plots a single pixel on the screen.

 INPUT: Base pointer to FB

 OUTPUT: None

*/
void plot_pixel(UINT16 *base, UINT16 row, UINT16 col){
    if (col < SCREEN_WIDTH && row < SCREEN_HEIGHT)
        *(base + row * 40 + (col >> 4)) |= (1 << (15 - (col & 15)));
}

void plot_pixel(UINT16 *base, int x, int y) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
    *(base + y * 40 + (x >> 4)) |= 1 << 15 - (x & 15);
};


/*----- Function: plot_horizontal_line -----

 PURPOSE: Plot a hoizontal line on the screen. The horizontal line is specified by the leftmost pixel of the line and the length of the line.

 INPUT: Address(UINT8*): to the start of the screen
        Position(row,col): the coordinates of the leftmost pixel of the horizontal line
        Length: the lenth in pixels of the line

 OUTPUT: None
*/


void plot_horizontal_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length) {
    UINT16 i;

    for (i = 0; i < length; i++) {
        plot_pixel((UINT8 *)base, row, col + i);
    }
}

/*----- Function: plot_vertical_line -----

 PURPOSE: Plot a hoizontal line on the screen. The vertical line is specified by the topmost pixel of the line and the length of the line.

 INPUT: Address(UINT32*): to the start of the screen
        Position(row,col): the coordinates of the topmost pixel of the vertical line
        Length: the lenth in pixels of the line

 OUTPUT: None
*/
void plot_vertical_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length) {
    UINT16 i;

    if (col < SCREEN_WIDTH && row < SCREEN_HEIGHT && row + length <= SCREEN_HEIGHT)
    {
        UINT32 *loc = base + (row * 20) + (col >> 5);
        for (i = 0; i < length; i++)
        {
            *loc |= (UINT32)1 << (31 - (col & 31));
            loc += 20;
        }
    }

}*


/*----- Function: plot_line -----

 PURPOSE: Plots a line on the screen between the two given points.

 INPUT: Address(UINT32*): to the start of the screen
        Position(start_row,start_col): the coordinates of the start of the line
        Position(end_row,end_col): the coordinates of the end of the line

 OUTPUT: None
*/
void plot_line(UINT32 *base, UINT16 start_row, UINT16 start_col, UINT16 end_row, UINT16 end_col) {
    INT16 del_r = end_row - start_row;
    INT16 del_c = end_col - start_col;
    INT16 r, c;
    INT16 step_r, step_c;

    /* For horizontal line*/
    if (del_r == 0) {
        if (del_c < 0) {
            start_col = end_col;
            del_c = -del_c;
        }
    
        for (c = 0; c <= del_c; c++) {
            plot_pixel((UINT8 *)base, start_row, start_col + c);
        }

        return;
    }

    /* For vertical line*/
    if (del_c == 0) {
        if (del_r < 0) {
            start_row = end_row;
            del_r = -del_r;
        }

        for (r = 0; r <= del_r; r++) {
            plot_pixel((UINT8 *)base, start_row + r, start_col);
        }

        return;
    }

    /* For a diagonal line */
    if (del_r < 0) {
        del_r = -del_r;
    }

    if (del_c < 0) {
        del_c = -del_c;
    }

    if (del_r == del_c) {
        if (start_row < end_row) {
            step_r = 1;
        }
        else {
            step_r = -1;
        }

        if (start_col < end_col) {
            step_c = 1;
        }
        else {
            step_c = -1;
        }

        for (r = 0; r <= del_r; r++) {
            plot_pixel((UINT8 *)base, start_row, start_col);
            start_row += step_r;
            start_col += step_c;
        }

    }
}


/*----- Function: plot_rectangle -----

 PURPOSE: Plots a rectangle on the screen given by the top left pixel, and the length and width of the rectangle.

 INPUT: Address(UINT32*): to the start of the screen
        Position(row,col): the coordinates of the top left pixel of the rectangle
        Length: the lenth (number of rows) in pixels of the rectangle
        Width: the width (number of columns) in pixels of the rectangle

 OUTPUT: None
*/
void plot_rectangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width)
{
    UINT16 i;
    UINT32 *draw;

    if (row >= SCREEN_HEIGHT || col >= SCREEN_WIDTH)
        return;

    if (row + length > SCREEN_HEIGHT)
        length = SCREEN_HEIGHT - row;

    for (i = 0; i < length; i++)
    {
        draw = base + ((row + i) * 20);
        plot_horizontal_line(base, row + i, col, width);
    }
}

/*----- Function: plot_square -----

 PURPOSE: Plots a square on the screen given by the top left pixel, and the length of the sides of the square.

 INPUT: Address(UINT32*): to the start of the screen
        Position(row,col): the coordinates of the top left pixel of the square
        Side: the lenth of each side, in pixels, of the square

 OUTPUT: None
*/
void plot_square(UINT32 *base, UINT16 row, UINT16 col, UINT16 side) {
    /* 
    A square is a type of rectangle with the height = width
    So we can use plot_rectangle by using the same value (side) for length and width
    */
    plot_rectangle(base, row, col, side, side);
}

/*----- Function: plot_triangle -----

 PURPOSE: Plots a triangle on the screen given by the coordinate of the 90° angle, the length of the base, the length of the height, and the direction of the triangle.

 INPUT: Address(UINT8*): to the start of the screen
        Position(row,col): the coordinates of the pixel of the 90° angle of the triangle
        Height: the lenth (number of rows) of the height in pixels of the triangle
        Direction: Describes where the coordinate is relative to the rest of the triangle
              0 - Coordinate is the top left point of the triangle
              1 - Coordinate is the top right point of the triangle
              2 - Coordinate is the bottom left point of the triangle
              3 - Coordinate is the bottom right point of the triangle


 OUTPUT: None
*/
void plot_triangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 base, UINT16 height, UINT8 direction)
{
    UINT16 i;
    UINT16 width;
    UINT16 draw_row;
    UINT16 start_col;

    if (height == 0 || base == 0)
        return;

    for (i = 0; i < height; i++)
    {
        /* width grows as we go down */
        width = (base * (i + 1)) / height;

        switch (direction)
        {
            /* top-left right angle */
            case 0:
                draw_row = row + i;
                start_col = col;
                break;

            /* top-right right angle */
            case 1:
                draw_row = row + i;
                start_col = col - width + 1;
                break;

            /* bottom-left right angle */
            case 2:
                draw_row = row - i;
                start_col = col;
                break;

            /* bottom-right right angle */
            case 3:
                draw_row = row - i;
                start_col = col - width + 1;
                break;

            default:
                return;
        }

        plot_horizontal_line(base, draw_row, start_col, width);
    }
}


/*----- Function: plot_bitmap_8 -----

 PURPOSE: Plots a bitmap to the screen given by the top left pixel of the bitmap and the height of bitmap.

 INPUT: Address(UINT16*): to the start of the screen
        Position(row,col): the coordinates of the top left pixel of the bitmap
        Height: the lenth (number of rows) of the height in pixels of the bitmap

 OUTPUT: None
*/
void plot_bitmap_8(UINT8 *base, UINT16 row, UINT16 col, UINT16 height) {
    UINT16 r, c;
    
    for (r = 0; r < height; r++) {
        for (c = 0; c < 8; c++) {
            if (base[r] & (0x80 >> c)) {
                plot_pixel(base, row + r, col +c);
            }
        }
    }
}


/*----- Function: plot_bitmap_16 -----

 PURPOSE: Plots a bitmap to the screen given by the top left pixel of the bitmap and the height of bitmap.

 INPUT: Address(UINT16*): to the start of the screen
        Position(row,col): the coordinates of the top left pixel of the bitmap
        Height: the lenth (number of rows) of the height in pixels of the bitmap

 OUTPUT: None
*/
void plot_bitmap_16(UINT16 *base, UINT16 row, UINT16 col, UINT16 height) {
    UINT16 r, data[r], c;

    for (r = 0; r < height; r++)
    {
        for (c = 0; c < 16; c++)
        {
            if (data[r] & (0x8000 >> c))
            {
                plot_pixel(base, row + r, col + c);
            }
        }
    }
}


/*----- Function: plot_bitmap_32 -----

 PURPOSE: Plots a bitmap to the screen given by the top left pixel of the bitmap and the height of bitmap.

 INPUT: Address(UINT32*): to the start of the screen
        Position(row,col): the coordinates of the top left pixel of the bitmap
        Height: the lenth (number of rows) of the height in pixels of the bitmap

 OUTPUT: None
*/
void plot_bitmap_32(UINT32 *base, UINT16 row, UINT16 col, UINT16 height) {
    UINT16 r, c;
    
    for (r = 0; r < height; r++) {
        for (c = 0; c < 32; c++) {
            if (base[r] & (0x8000000 >> c)) {
                plot_pixel((UINT8 *)base, row + r, col +c);
            }
        }
    }
}


/*----- Function: plot_character -----

 PURPOSE: Plots a single character, as a bitmap from a font table, to the screen.

 INPUT: Address(UINT32*): to the start of the screen
        Position(row,col): the coordinates of the top left pixel of the character
        ch(char): the character to be written to the screen

 OUTPUT: None
*/
void plot_character(UINT8 *base, UINT16 row, UINT16 col, char ch)
{
    UINT8 *font = (UINT8 *)V_FNT_AD;
    UINT16 r;
    UINT16 byte_offset;
    UINT16 shift;

    /* starting byte in framebuffer */
    byte_offset = (row * 80) + (col >> 3);

    /* bit shift inside byte */
    shift = col & 7;

    for (r = 0; r < 16; r++)
    {
        UINT8 bits = font[(ch * 16) + r];

        base[byte_offset + r * 80]     |= bits >> shift;
        base[byte_offset + r * 80 + 1] |= bits << (8 - shift);
    }
}

/*----- Function: plot_string -----

 PURPOSE: Plots a string, as a sequence of bitmaps from a font table, to the screen.

 INPUT: Address(UINT32*): to the start of the screen
        Position(row,col): the coordinates of the top left pixel of the string
        ch(c-string): the string to be written to the screen

 OUTPUT: None
*/
void plot_string(UINT8 *base, UINT16 row, UINT16 col, char *ch) {
    
    while (*ch) {
        plot_character(base, row, col, *ch++);
        col += 8;
    }
}
