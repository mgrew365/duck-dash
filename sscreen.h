/*
File: SSCREEN.H
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 4 - COMP 2659 
Date Modified: April 2, 2026
File Description: This is a header file that declares the functions implemented in sscreen.c                 
*/
#ifndef SSCREEN_H
#define SSCREEN_H
#include "font.h"

/* ----- Function: initilize_splash_screen -----

Purpose: Renders the splash screen graphics to the screen, including
         the game title ("DUCK DASH") and menu buttons for user
         input.

Input: UINT32 *base: pointer to the base of the screen memory

Output: None
*/
void initilize_splash_screen(UINT32 *base);


/* ----- Function: run_splash_screen -----

Purpose: Displays the splash screen and waits for user input to 
         select a menu option. Handles keyboard input for menu navigation.

Input: UINT32 *base: pointer to the base of the screen memory

Output: int:
        1 → user selected "1 Player"
        0 → user selected "Quit" (ESC key)
*/
int run_splash_screen(UINT32 *base);

#endif
