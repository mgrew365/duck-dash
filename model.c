/*
File: MODEL.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: March 15, 2026
File Description: This file defines the game model and basic movement functions required for Duck Dash.
                  It includes a test snapshot of the intial game state for testing purposes,
                  fucntions to move the duck and buildings during gameplay and a function to create
                  an initial model state. Together, these functions modify or return the game model to update 
                  game state in response to asyncronous, conditional or synchronous events
*/
#include <osbind.h>
#include "model.h"

/* Sprite Data*/
const UINT32 duck_bitmap[32] = {
    0x0007FFC0,
    0x0007FFC0,
    0x0007FFC0,

    0x00380038,
    0x00380038,
    0x00380038,

    0x00387038,

    0x01C07007,
    0x01C07007,
    0x01C07007,

    0x01C00007,

    0x01C00038,
    0x01C00038,
    0x01C00038,
    0x01C00038,

    0xFE0001C0,

    0xFE1C01C0,
    0xFE1C01C0,
    0xFE1C01C0,


    0xE01C0E00,

    0xE0E00E00,
    0xE0E00E00,
    0xE0E00E00,
    0xE0E00E00,

    0xE01C0E00,

    0x1C1C0E00,
    0x1C1C0E00,
    0x1C1C0E00,

    0x1C000E00,

    0x03FFF000,
    0x03FFF000,
    0x03FFF000
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
        328,    /* y */
        0       /* delta_y */
    },

    /* Buildings */
    {
        { 200, 328, -2, 32, 32 },
        { 400, 328, -2, 32, 32 },
        { 600, 328, -2, 32, 32 }
        /*{ 600, 328, -2, 32, 32 }*/
    },

    /* Score */
    0,
    false /* quit*/
};

/* ----- Function: move_duck -----

Purpose: Updates the vertical position of the duck.

Input: Duck *duck: a pointer to duck object

Output: None
*/
void move_duck(Duck *duck) {
    duck->y += duck->delta_y;
    duck->delta_y += 1;

    if (duck->y >= SCREEN_HEIGHT - FLOOR_BUFFER - DUCK_HEIGHT) {
        duck->y = SCREEN_HEIGHT - FLOOR_BUFFER - DUCK_HEIGHT;
        duck->delta_y = 0;
    }

    if (duck->y < 0) {
        duck->y = 0;
    }
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

/* ----- Function: model_create_building -----

Purpose: Creates and returns a new building with its starting position,
         size, and movement values initialized. The building is placed at
         the right side of the screen and aligned with the ground so it can
         move left across the screen as an obstacle.

Input: None

Output: Building object with initialized x/y position, width, height,
        and horizontal movement
*/
Building model_create_building(void) {
    static int next_height = 32;
    Building b;

    b.width = 32;
    b.height = next_height;
    b.delta_x = -2;

    next_height += 16;
    if (next_height > 64) {
        next_height = 32;
    }

    b.x = 640;
    b.y = SCREEN_HEIGHT - FLOOR_BUFFER - b.height;

    return b;
}