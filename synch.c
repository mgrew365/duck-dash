/*
File: SYNCH.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: February 22, 2026
File Description: This file defines all synchronous events for Duck Dash which are events that occur regularly
                  at each clock tick. These evnts include updating building movement, game speed and score. 
*/
#include "synch.h"

#define TICKS_PER_SECOND 70

/* Time intervals to increase speed (seconds) */
#define SPEED_UP_1 20
#define SPEED_UP_2 40
#define SPEED_UP_3 80

/* ----- Function: building_appearence -----

Purpose: This function handles the gradual appearance of buildings overtime.

Input: Model *model: A pointer to the game's current model
       elapsed_ticks (int): number of ticks since start game

Output: None
*/
void building_appearance(Model *model, unsigned int elapsed_ticks) {
    (void)model;
    (void)elapsed_ticks;
}

/* ----- Function: speed_increase -----

Purpose: This function allows for speed to be increased at predefined time intervals.

Input: Model *model: A pointer to the game's current model 
       elapsed_ticks (int): number of ticks since game start
Output: None
*/
void speed_increase(Model *model, unsigned int elapsed_ticks) {
    unsigned int elapsed_seconds = elapsed_ticks / TICKS_PER_SECOND;
    unsigned int i;

    if (elapsed_seconds == SPEED_UP_1 || elapsed_seconds == SPEED_UP_2 || elapsed_seconds == SPEED_UP_3)
    {
        for (i = 0; i < MAX_BUILDINGS; i++) {
            /* Increase speed by making delta_x more negative */
            model->buildings[i].delta_x -= 1;
        }
    }
}
  
/* ----- Function: update_score -----

Purpose: This function allows for the update of the players score based on elapsed gameplay time.

Input: Model *model: A pointer to the game's current model 
       elapsed_ticks (int): number of ticks since game start
Output: None
*/
void update_score(Model *model, unsigned int elapsed_ticks) {
    model->score = elapsed_ticks / TICKS_PER_SECOND;
}