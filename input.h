/*
File: INPUT.H
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 3 - COMP 2659 
Date Modified: March 10, 2026
File Description: This header file defines constants and function prototypes 
                  for handling keyboard input in Duck Dash.
*/

#ifndef INPUT_H
#define INPUT_H

#include "types.h"
#include "events.h"

void read_key(int key, const Model *model);



/* Key Constants */
/*
#define ESC_KEY   27    /* ASCII value for the Escape key to trigger quit */
/*#define SPACE_BAR 32    /* ASCII value for Space Bar to trigger jump */


/* ----- Function: has_input -----
Purpose: Checks if a key has been pressed (non-blocking).
Output: True (1) if a character is waiting in the buffer, else false (0).
*/
/*
int has_input();
*/

/* ----- Function: get_input -----
Purpose: Retrieves the character from the keyboard buffer.
Output: The ASCII value of the key pressed.
*/
/*
char get_input();

#endif
*/