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
                     - Duck jump
                     - Quit game
*/

#include "asynch.h"

/* ----- Function: duck_jump -----

Purpose: This functionis the asyncronous event being when the duck jumps (when the up key is pressed by a user)
         and the game model is updated right when triggered.

Input: Model *model: A pointer to the game's current model which is used to modify the ducks state including position, jump state, etc.

Output: None
*/
void duck_jump(Model *model) {
    /* Only jump if duck is not already moving upward */
    if (model->duck.delta_y >= 0) {
        model->duck.delta_y = -8;   /* jump strength (change as need be) */
    }
}


/* ----- Function: quit_game -----

Purpose: This function handles the termination of gameplay when the ESC key is pressed by the user.

Input: Model *model: A pointer to the game's current model.

Output: None
*/
void quit_game(Model *model) {
    (void)model; 
}