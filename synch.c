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
#include "cond.h"
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
    unsigned int i;

    (void)elapsed_ticks;

    for (i = 0; i < MAX_BUILDINGS; i++)
    {
        if (building_left_border(&model->buildings[i]))
        {
            /* reset building to right side of screen */
            model->buildings[i].x = SCREEN_WIDTH;
        }
    }
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

/* ----- Function: update_duck -----

Purpose: Controls duck vertical movement (NO GRAVITY).
         Duck moves up when jumping and moves down once max height is reached.

Input: Model *model

Output: None
*/
void update_duck(Model *model) {
    /* move duck */
    model->duck.y += model->duck.delta_y;

    /* reached maximum jump height */
    if (duck_max_height(&model->duck)) {
        model->duck.delta_y = 4;   /* start descending */
    }

    /* reached ground */
    if (duck_ground_collision(&model->duck)) {
        model->duck.delta_y = 0;   /* stop movement */
    }
}


/* ----- Function: update_buildings -----

Purpose: Moves buildings left across the screen.

Input: Model *model

Output: None
*/
void update_buildings(Model *model) {
    unsigned int i;

    for (i = 0; i < MAX_BUILDINGS; i++) {
        model->buildings[i].x += model->buildings[i].delta_x;
    }
}