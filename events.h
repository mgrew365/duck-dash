/*
File: EVENTS.H
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: February 21, 2026
File Description: This header file declares all event handling functions used to
                  update the game model in response to user input, elapsed time, and
                  in game conditions. Specifically the events include asynchronous, 
                  synchronous, and conditional based events. Additionally, these functions
                  operate on the Mode structure.The implementation of this file is in asynch.c,
                  synch.c, and cond.c.
*/

#ifndef EVENTS_H
#define EVENTS_h

#include "model.h"

/* Asynchronous Events */

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


/* Synchronous Events */

/* ----- Function: building_appearence -----

Purpose: This function handles the gradual appearance of buildings overtime.

Input: Model *model: A pointer to the game's current model
       elapsed_ticks (int): number of ticks since start game

Output: None
*/
void building_appearance(Model *model, unsigned int elapsed_ticks);

/* ----- Function: speed_increase -----

Purpose: This function allows for speed to be increased at predefined time intervals.

Input: Model *model: A pointer to the game's current model 
       elapsed_ticks (int): number of ticks since game start
Output: None
*/
void speed_increase(Model *model, unsigned int elapsed_ticks);

 
/* ----- Function: update_score -----

Purpose: This function allows for the update of the players score based on elapsed gameplay time.

Input: Model *model: A pointer to the game's current model 
       elapsed_ticks (int): number of ticks since game start
Output: None
*/
void update_score(Model *model, unsigned int elapsed_ticks);


/* Conditional Events */

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
bool building_left_corder_collision(const Model *model);

/* ----- Function: duck_max_height -----

Purpose: This function checks if the duck has reached its maximum jump height for it then to descend.

Input: Duck *duck: pointer to Duck object 

Output: boolean value: true if duck has reached the maximum jump height, else false
*/
bool duck_max_height(const Model *model);


/* ----- Function: duck_ground_collision -----

Purpose: This function checks if the duck has collided with the ground.

Input: Duck *duck: pointer to Duck object

Output: boolean value: true if duck has hit the ground, else false
*/
bool duck_ground_collision(const Model *model);


/* ----- Function: restart_game -----

Purpose: This function determines if a game should be restarted.

Input: Model *model: A pointer to current game model

Output: boolean value: boolean value: true if the game has ended and should be restarted, else false
*/
bool restart_game(const Model *model);

#endif
