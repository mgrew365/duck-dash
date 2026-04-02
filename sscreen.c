/*
File: SSCREEN.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: April 2, 2026
File Description: This is handles a splash screen for Duck Dash.
                  This includes redering, drawing the title, menu 
                  buttons, and handling user input for menu selection.
                  The user has a choice to play the game by pressing 1 key 
                  or quitting the game using ESC key.    
*/
#include <stdio.h>
#include "sscreen.h"
#include "raster.h"
#include "font.h"

/* BITMAPS */

UINT16 capitalD[] = {
    0xFFF8, 0xFFFC, 0xFFFE, 0xF01F,
    0xF00F, 0xF007, 0xF007, 0xF007,
    0xF007, 0xF007, 0xF007, 0xF00F,
    0xF01F, 0xFFFE, 0xFFFC, 0xFFF8
};

UINT16 capitalU[] = {
    0x0000, 0xC003, 0xC003, 0xC003,
    0xC003, 0xC003, 0xC003, 0xC003,
    0xC003, 0xC003, 0xC003, 0xC003,
    0xC003, 0x3FFC, 0x3FFC, 0x0000
};

UINT16 capitalC[] = {
    0x0000, 0x1FFE, 0x1FFE, 0x6000,
    0x6000, 0x6000, 0x6000, 0x6000,
    0x6000, 0x6000, 0x6000, 0x6000,
    0x6000, 0x1FFE, 0x1FFE, 0x0000
};

UINT16 capitalK[] = {
    0x0000, 0x6010, 0x6030, 0x6060,
    0x60C0, 0x6180, 0x6300, 0x7E00,
    0x7E00, 0x6300, 0x6180, 0x60C0,
    0x6060, 0x6030, 0x0000, 0x0000
};

UINT16 capitalA[] = {
    0x1FF8, 0x1FF8, 0x6006, 0x6006,
    0x6006, 0x6006, 0x6006, 0x6006,
    0x6006, 0x7EFE, 0x7EFE, 0x6006,
    0x6006, 0x6006, 0x6006, 0x6006
};

UINT16 capitalS[] = {
    0x0000, 0x0FFE, 0x0FFE, 0x3000,
    0x3000, 0x3000, 0x3000, 0x0FF0,
    0x0FF0, 0x0006, 0x0006, 0x0006,
    0x0006, 0x3FF8, 0x3FF8, 0x0000
};

UINT16 capitalH[] = {
    0x0000, 0x6006, 0x6006, 0x6006,
    0x6006, 0x6006, 0x6006, 0x7FFE,
    0x7FFE, 0x6006, 0x6006, 0x6006,
    0x6006, 0x6006, 0x6006, 0x0000
};

/* ----- Function: initilize_splash_screen -----

Purpose: Renders the splash screen graphics to the screen, including
         the game title ("DUCK DASH") and menu buttons for user
         input.

Input: UINT32 *base: pointer to the base of the screen memory

Output: None
*/
void initilize_splash_screen(UINT32 *base) {
    clear_screen(base);

    /* DUCK */
    plot_16bit_bitmap((UINT16 *) base, 50, 50, capitalD, 16);
    plot_16bit_bitmap((UINT16 *) base, 50, 100, capitalU, 16);
    plot_16bit_bitmap((UINT16 *) base, 50, 150, capitalC, 16);
    plot_16bit_bitmap((UINT16 *) base, 50, 200, capitalK, 16);

    /* DASH */
    plot_16bit_bitmap((UINT16 *) base, 50, 300, capitalD, 16);
    plot_16bit_bitmap((UINT16 *) base, 50, 350, capitalA, 16);
    plot_16bit_bitmap((UINT16 *) base, 50, 400, capitalS, 16);
    plot_16bit_bitmap((UINT16 *) base, 50, 450, capitalH, 16);

    /* 1 player box */
    plot_rectangle(base, 140, 60, 40, 200);

    /* Quit Game box */
    plot_rectangle(base, 200, 60, 40, 200);

    /* Center text inside boxes */
    plot_string((UINT8 *)base, 155, 90, "1-Player (1)");
    plot_string((UINT8 *)base, 215, 80, "Quit Game (ESC)");
}

/* ----- Function: run_splash_screen -----

Purpose: Displays the splash screen and waits for user input to 
         select a menu option. Handles keyboard input for menu navigation.

Input: UINT32 *base: pointer to the base of the screen memory

Output: int:
        1 → user selected "1 Player"
        0 → user selected "Quit" (ESC key)
*/
int run_splash_screen(UINT32 *base) {
    char key = 0;

    initilize_splash_screen(base);

    while (1)
    {
        if (has_input())
        {
            key = get_input();

            /* clear extra inputs */
            while (has_input()) get_input();

            if (key == '1')
                return 1;   /* start game */

            if (key == ESC_KEY)
                return 0;   /* quit */
        }
    }
}