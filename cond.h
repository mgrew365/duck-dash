/*
File: COND.H
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: February 21, 2026
File Description: This header file declares all conditional game events for Duck Dash.
                  The functions in this file are implemented in cond.c to check current game state.
*/

#ifndef COND_H
#define COND_H

#include "model.h"

/* Define bool */
#ifndef BOOL_DEFINED
#define BOOL_DEFINED
typedef enum { false = 0, true = 1 } bool;
#endif


/* ----- Function: duck_building_collision -----

Purpose: This function checks if the duck has colliding with the building. If the output is true, game over. 

Input: Model *model: A pointer to the game's current model

Output: boolean value: true if collision occurs, else false
*/
bool duck_building_collision(const Model *model);


/* ----- Function: building_left_border -----

Purpose: This function checks if the building has collided with the left border of the screen to then be removed from the screen
         if the output is true.

Input: Building *building: A pointer to the Building object

Output: boolean value: true if building is of the screen, else false
*/
bool building_left_border(const Building *building);


/* ----- Function: duck_max_height -----

Purpose: This function checks if the duck has reached its maximum jump height for it then to descend.

Input: Duck *duck: pointer to Duck object 

Output: boolean value: true if duck has reached the maximum jump height, else false
*/
bool duck_max_height(const Duck *duck);


/* ----- Function: duck_ground_collision -----

Purpose: This function checks if the duck has collided with the ground.

Input: Duck *duck: pointer to Duck object

Output: boolean value: true if duck has hit the ground, else false
*/
bool duck_ground_collision(const Duck *duck);

/* ----- Function: restart_game -----

Purpose: This function determines if a game should be restarted.

Input: Model *model: A pointer to current game model

Output: boolean value: boolean value: true if the game has ended and should be restarted, else false
*/
bool restart_game(const Model *model);

#endif 