/*
File: MODEL.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: February 21, 2026
File Description: This file defines the game model and basic movement functions required for Duck Dash.
                  It includes a test snapshot of the intial game state for testing purposes,
                  fucntions to move the duck and buildings during gameplay and a function to create
                  an initial model state. Together, these functions modify or return the game model to update 
                  game state in response to asyncronous, conditional or synchronous events
*/
#include <osbind.h>
#include "model.h"

/* Leave extra space at the bottom of screen so duck doesnt land on edge of screen, lands on floor */
#define FLOOR_BUFFER 40

/* Initial game snapshot of game state for testing purposes*/
Model testDuckDashSnapshot = {
    /* Duck */
    {
        40,     /* x */
        180,    /* y */
        0       /* delta_y */
    },

    /* Buildings */
    {
        { 700, 360, 32, 32 },
        { 860, 360, 32, 32 },
        { 1020, 360, 32, 32 },
        { 1180, 360, 32, 32 }
    },

    /* Score */
    0
};

/* ----- Function: move_duck -----

Purpose: Updates the vertical position of the duck.

Input: Duck *duck: a pointer to duck object

Output: None
*/
void move_duck(Duck *duck) {
    duck->y += duck->delta_y;
}


/* ----- Function: move_buildings -----

Purpose: Updates the horizontal position of the buildings and moves them left towards
         the duck.

Input: buildings[]: an array of building objects
       count: number of buildings in the array

Output: None
*/
void move_buildings(Building buildings[], unsigned int count) {
    unsigned int i;

    for (i = 0; i < count; i++) {
        buildings[i].x += buildings[i].delta_x;
    }
}

/* ----- Function: model_create_initial -----

Purpose: This function returns a copy of the initial game model for testing or restarting the game. 

Input: None

Output: Model object which contains initial duck, building position, and score
*/
Model model_create_initial() {
    return testDuckDashSnapshot;
}
