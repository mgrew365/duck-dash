/*
File: RASTER.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: February 23, 2026
File Description: This file implements a raster graphics library in which the routines 
                  plot images including pixels, lines, bitmaps, etc. 
*/

#include "raster.h"
#include "font.h"
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
    int i;
    for (i = 0; i < 400 * 20; i++)
        base[i] = 0;
}

/*----- Function: clear_region -----

 PURPOSE: Clear a region of the screen. The section is specified by the coordinates of the top left corner, and the height and width of the region.

 INPUT: Address(UINT32*): to the start of the screen
        Position(row,col): the coordinates of the top left pixel of the region
        Length: the lenth (number of rows) in pixels of the region
        Width: the width (number of columns) in pixels of the region

 OUTPUT: None

*/
       
void clear_region(UINT32 *base, int row, int col, UINT16 length, UINT16 width) {
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
void plot_pixel(UINT8 *base, int row, int col){
    UINT16 *word;
    int r;

    /* Handles bounds and clipping */
    if (row < 0 || row >= SCREEN_HEIGHT)
        return;
    if (col < 0 || col >= SCREEN_WIDTH)
        return;

    word = (UINT16 *)base;

    /* Move down row rows (40 words per row) */
    for (r = 0; r < row; r++)
        word += 40;

    /* Move to correct word in the row */
    word += (col >> 4);

    /* Set the pixel bit */
    *word |= (1 << (15 - (col & 15)));
}

/*----- Function: plot_horizontal_line -----

 PURPOSE: Plot a hoizontal line on the screen. The horizontal line is specified by the leftmost pixel of the line and the length of the line.

 INPUT: Address(UINT8*): to the start of the screen
        Position(row,col): the coordinates of the leftmost pixel of the horizontal line
        Length: the lenth in pixels of the line

 OUTPUT: None
*/
void plot_horizontal_line(UINT32 *base, int row, int col, UINT16 length) {
    UINT16 i;

    /* bounds checking */
    if (row < 0 || row >= SCREEN_HEIGHT)
        return;

    if (col < 0) {
        length += col; /* reduce length if starting before 0*/
        col = 0;
    }

    if (col + length > SCREEN_WIDTH)
        length = SCREEN_WIDTH - col;

    for (i = 0; i < length; i++) {
        plot_pixel((UINT8 *)base, row, col + i);
    }
}

/*----- Function: plot_vertical_line -----

 PURPOSE: Plot a vertical line on the screen. The vertical line is specified by the topmost pixel of the line and the length of the line.

 INPUT: Address(UINT32*): to the start of the screen
        Position(row,col): the coordinates of the topmost pixel of the vertical line
        Length: the lenth in pixels of the line

 OUTPUT: None
*/

void plot_vertical_line(UINT32 *base, int row, int col, UINT16 length) {
    int clipped_length;
    UINT16 i;

    /* Column bounds */
    if (col < 0 || col >= SCREEN_WIDTH)
        return;

    clipped_length = length;

    /* Top clipping */
    if (row < 0) {
        clipped_length += row;   /* row is negative */
        row = 0;
    }

    /* Bottom clipping */
    if (row + clipped_length > SCREEN_HEIGHT)
        clipped_length = SCREEN_HEIGHT - row;

    /* Fully clipped */
    if (clipped_length <= 0)
        return;

    for (i = 0; i < (UINT16)clipped_length; i++)
        plot_pixel((UINT8 *)base, row + i, col);
}

/*----- Function: plot_horizontal_segment -----

 PURPOSE: A  helper function for plot_line. Draws a horizontal line on the screen with a specified length.

 INPUT: base (UINT32*): address of the framebuffer
        row (int): row of the starting pixel
        col (int): column of starting pixel
        length (int): length of the line segment in pixels

 OUTPUT: None
*/
static void plot_horizontal_segment(UINT32 *base, int row, int col, int length) {
    int i;
    for (i = 0; i <= length; i++)
        plot_pixel((UINT8 *)base, row, col + i);
}


/*----- Function: plot_vertical_segment -----

 PURPOSE: A  helper function for plot_line. Draws a vertical line on the screen with a specified length.
          It uses unit row and column steps.

 INPUT: base (UINT32*): address of the framebuffer
        row (int): row of the starting pixel
        col (int): column of starting pixel
        length (int): length of the line segment in pixels

 OUTPUT: None
*/
static void plot_vertical_segment(UINT32 *base, int row, int col, int length) {
    int i;
    for (i = 0; i <= length; i++)
        plot_pixel((UINT8 *)base, row + i, col);
}


/*----- Function: plot_diagonal_segment -----

 PURPOSE: A  helper function for plot_line. Draws a 45 degree diagonal line line on the screen with a specified length.

 INPUT: base (UINT32*): address of the framebuffer
        row (int): starting row of the line 
        col (int): starting column of the line 
        steps (int): Number of pixels that must be drawn
        step_r (int): row direction (either +1 or -1)
        step_c (int): column direction (either +1 or -1)

 OUTPUT: None
*/
static void plot_diagonal_segment(UINT32 *base, int row, int col, int steps, int step_r, int step_c) {
    int i;
    for (i = 0; i <= steps; i++) {
        plot_pixel((UINT8 *)base, row, col);
        row += step_r;
        col += step_c;
    }
}

/*----- Function: abs  -----

 PURPOSE: This helper function commutes the absolute value of an integer.

 INPUT: x (int): integer value

 OUTPUT: int: absolute value of x
*/
static int abs(int x) {
    return (x < 0) ? -x : x;
}
/*----- Function: plot_line -----

 PURPOSE: Plots a line on the screen between the two given points.

 INPUT: Address(UINT32*): to the start of the screen
        Position(start_row,start_col): the coordinates of the start of the line
        Position(end_row,end_col): the coordinates of the end of the line

 OUTPUT: None
 */
void plot_line(UINT32 *base, int start_row, int start_col, int end_row, int end_col) {
    int del_r = end_row - start_row;
    int del_c = end_col - start_col;

    if (del_r == 0) {
        if (del_c < 0) { start_col = end_col; del_c = -del_c; }
        plot_horizontal_segment(base, start_row, start_col, del_c);
        return;
    }

    if (del_c == 0) {
        if (del_r < 0) { start_row = end_row; del_r = -del_r; }
        plot_vertical_segment(base, start_row, start_col, del_r);
        return;
    }

    if (abs(del_r) == abs(del_c)) {
        plot_diagonal_segment(
            base,
            start_row, start_col,
            abs(del_r),
            (del_r > 0) ? 1 : -1,
            (del_c > 0) ? 1 : -1
        );
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
void plot_rectangle(UINT32 *base, int row, int col, UINT16 length, UINT16 width) {
    
void plot_rectangle(UINT32 *base, int row, int col, UINT16 length, UINT16 width) {
    UINT16 r;
    if (row >= SCREEN_HEIGHT || col >= SCREEN_WIDTH)
        return;

    if (row < 0) { length += row; row = 0; }
    if (col < 0) { width += col; col = 0; }

    if (row + length > SCREEN_HEIGHT)
        length = SCREEN_HEIGHT - row;
    if (col + width > SCREEN_WIDTH)
        width = SCREEN_WIDTH - col;

    for (r = 0; r < length; r++)
        plot_horizontal_line(base, row + r, col, width);
}

}

/*----- Function: plot_square -----

 PURPOSE: Plots a square on the screen given by the top left pixel, and the length of the sides of the square.

 INPUT: Address(UINT32*): to the start of the screen
        Position(row,col): the coordinates of the top left pixel of the square
        Side: the lenth of each side, in pixels, of the square

 OUTPUT: None
*/
void plot_square(UINT32 *base, int row, int col, UINT16 side) {
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
void plot_triangle(UINT32 *base, int row, int col, UINT16 triangle_base, UINT16 height, UINT8 direction) {
    UINT16 i;
    UINT16 width;
    UINT16 draw_row;
    UINT16 start_col;

    if (height == 0 || triangle_base == 0)
        return;

    for (i = 0; i < height; i++)
    {
        /* width grows as we go down */
        width = (triangle_base * (i + 1)) / height;

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
void plot_8bit_bitmap(UINT8 *base, int row, int col, const UINT8 *bitmap, UINT16 height) {
    UINT16 r, c;

    for (r = 0; r < height; r++) {
        for (c = 0; c < 8; c++) {
            if (bitmap[r] & (0x80 >> c)) {
                plot_pixel(base, row + r, col + c);
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
void plot_16bit_bitmap(UINT16 *base, int row, int col, const UINT16 *bitmap, UINT16 height) {
    UINT16 r, c;

    for (r = 0; r < height; r++) {
        for (c = 0; c < 16; c++) {
            if (bitmap[r] & (0x8000 >> c)) {
                plot_pixel((UINT8 *)base, row + r, col + c);
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
void plot_32bit_bitmap(UINT32 *base, int row, int col, const UINT32 *bitmap, UINT16 height) {
    UINT16 r, c;

    for (r = 0; r < height; r++) {
        for (c = 0; c < 32; c++) {
            if (bitmap[r] & (0x80000000UL >> c)) {
                plot_pixel((UINT8 *)base, row + r, col + c);
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
void plot_character(UINT8 *base, int row, int col, char ch) {
    UINT16 i;
    UINT8 *glyph = (UINT8 *)GLYPH_START(ch);

    for (i = 0; i < 8; i++, glyph++)
    {
        *(base + (row + i) * 80 + (col >> 3)) |= *glyph;
    }
}

/*----- Function: plot_string -----

 PURPOSE: Plots a string, as a sequence of bitmaps from a font table, to the screen.

 INPUT: Address(UINT32*): to the start of the screen
        Position(row,col): the coordinates of the top left pixel of the string
        ch(c-string): the string to be written to the screen

 OUTPUT: None
*/
void plot_string(UINT8 *base, int row, int col, char *ch) {
    
    while (*ch) {
        plot_character(base, row, col, *ch++);
        col += 8;
    }
}
