/*
File: ASYNCH.H
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: February 21, 2026
File Description: This header file declares all asynchronous events included in Duck Dash.
                  The functions in this file are implemented in asynch.c which modify game play from user input.

*/


#ifndef ASYNCH_H
#define ASYNCH_H

#include "model.h"

/* ----- Function: duck_jump -----

Purpose: This functionis the asyncronous event being when the duck jumps (when the up key is pressed by a user)
         and the game model is updated right when triggered.

Input: Model *model: A pointer to the game's current model which is used to modify the ducks state including position, jump state, etc.

Output: None
*/
void duck_jump(Model *model);

/* ----- Function: quit_game -----

Purpose: This function handles the termination of gameplay when the ESC key is pressed by the user.

Input: Model *model: A pointer to the game's current model.

Output: None
*/
void quit_game(Model *model);

#endif 
