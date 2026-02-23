/*
File: ASYNCH.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: February 22, 2026
File Description: This module defines asynchronous game events for Duck Dash which these events
                  are the outcome of user input. For example, when a key is pressed,game state is modified
                  which is independent of the game clock

                  The asynchronous events include:
                     - The duck jump
                     - Quit game
*/

#include "asynch.h"

/* Duck Jump - triggered when up key is pressed */
void duck_jump(Model *model) {
    /* Only jump if duck is not already moving upward */
    if (model->duck.delta_y >= 0) {
        model->duck.delta_y = -8;   /* jump strength (change as need be) */
    }
}

/* Quit game - triggered when ESC key is pressed */
void quit_game(Model *model) {
    (void)model; 
}