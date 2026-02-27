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
/* Duck Jump - triggered when up key is pressed */
void duck_jump(Model *model);

/* Quit game - triggered when ESC key is pressed */
void quit_game(Model *model);


/* Synchronous Events */
/* Building appearing gradually with speed of appearence increasing over time */
void building_appearance(Model *model, unsigned int elapsed_ticks);

/* Speed increase at intervals: 20s, 40s, 80s, etc */
void speed_increase(Model *model, unsigned int elapsed_ticks);

/* Score updates based on elapsed gameplay time */
void update_score(Model *model, unsigned int elapsed_ticks);


/* Conditional Events */
/* Duck collides with building resulting in game over */
bool duck_building_collision(const Model *model);

/* Building collides with left border to be removed from the screen */
bool building_left_corder_collision(const Model *model);

/* Duck reaches its maximum jump height and starts to descend afterwords */
bool duck_max_height(const Model *model);

/* Duck collides with ground stopping descent */
bool duck_ground_collision(const Model *model);

/* Restart game when gameplay has ended */
bool restart_game(const Model *model);

#endif
