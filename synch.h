/*
File: SYNCH.H
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: February 22, 2026
File Description: This is a header file which declares prototypes for all synchronous events in Duck Dash.
                  These functions are implemented in synch.c.
*/
#ifndef SYNCH_H
#define SYNCH_H

#include "model.h"

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


/* ----- Function: update_duck -----

Purpose: Controls duck vertical movement (NO GRAVITY).
         Duck moves up when jumping and moves down once max height is reached.

Input: Model *model

Output: None
*/
void update_duck(Model *model);


/* ----- Function: update_buildings -----

Purpose: Moves buildings left across the screen.

Input: Model *model

Output: None
*/
void update_buildings(Model *model);

#endif 
