/*
File: TSTSPLA.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 4 - COMP 2659 
Date Modified: April 2, 2026
File Description: This file is used to test the splash game before implementing
                  it in duckdash.c (main game).
*/
#include <osbind.h>
#include "sscreen.h"

/* ----- Function: main -----

Purpose: Entry point for the splash screen test program. It retrieves 
         the screen base address, calls the splash screen rendering 
         function, and pauses execution until a key is pressed.

Input: None

Output: int: 0 if program terminated successfully
*/
int main() {

    UINT32 *base = (UINT32 *)Physbase();
    initilize_splash_screen(base);
    
    /* Wait for key press */
    while (!Cconis()) {
        /* do nothing */
    }

    return 0;
}
