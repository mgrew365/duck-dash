/*
File: MODEL.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: March 1, 2026
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

/* Sprite Data*/
const UINT16 duck_bitmap[16] = {
    0x0000, 0x0060, 0x0090, 0x0108,
    0x0104, 0x0108, 0x0E10, 0x0890,
    0x0910, 0x0890, 0x0410, 0x03E0,
    0x0000, 0x0000, 0x0000, 0x0000
};

/* Temporary Building Bitmap*/
const UINT32 building_bitmap[32] = {
    0xFFFFFFFF, 0x80000001, 0x80000001, 0x80000001,
    0x80F00F01, 0x80F00F01, 0x80000001, 0x80000001,
    0x80F00F01, 0x80F00F01, 0x80000001, 0x80000001,
    0x80F00F01, 0x80F00F01, 0x80000001, 0x80000001,
    0x80F00F01, 0x80F00F01, 0x80000001, 0x80000001,
    0x80F00F01, 0x80F00F01, 0x80000001, 0x80000001,
    0x80F00F01, 0x80F00F01, 0x80000001, 0x80000001,
    0x80F00F01, 0x80F00F01, 0x80000001, 0xFFFFFFFF
};


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
        { 200, 360, -2, 32, 32 },
        { 300, 360, -2, 32, 32 },
        { 400, 360, -2, 32, 32 },
        { 500, 360, -2, 32, 32 }
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
