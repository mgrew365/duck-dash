/*
File: INPUT.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 3 - COMP 2659 
Date Modified: March 15, 2026
File Description:  Contains the input handling functions for DuckDash. This file is
                   responsible for detecting keyboard input and returning player key
                   presses so the game can respond to actions such as jumping or quitting.

*/

#include <osbind.h>
#include <stdio.h>
#include "input.h"

/* ----- Function: has_input -----

Purpose:Checks if a key is waiting in the keyboard buffer.

Input: None

Output: true if a key is available, else false
*/
bool has_input(void) {
    return (Cconis() != 0);
}


/* ----- Function: get_input -----

Purpose: Gets the next key from the keyboard buffer.

Input: None

Output:ASCII character of key pressed
*/
char get_input(void) {
    return (char)Cnecin();
}
