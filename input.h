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

/* Key Constants */
#define ESC_KEY   27    /* ASCII value for the Escape key to trigger quit */
#define SPACE_BAR 32    /* ASCII value for Space Bar to trigger jump */

/* ----- Function: has_input -----

Purpose:Checks if a key is waiting in the keyboard buffer.

Input: None

Output: true if a key is available, else false
*/
int has_input();

/* ----- Function: get_input -----

Purpose: Gets the next key from the keyboard buffer.

Input: None

Output:ASCII character of key pressed
*/
char get_input();

#endif
