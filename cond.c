/*
File: COND.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: March 15, 2026
File Description: This file implements all conditional game event functions for Duck Dash. These events are used
                  to check the current game state hence they are boolean values to indicate whether a condition is met.

                  The conditional events include:
                    - Duck colliding with building
                    - Duck reaching its maximum jump height
                    - Duck colliding with ground
                    - Buildings leaving the screen
                    - Game restart conditions

*/

#include "cond.h"


/* ----- Function: duck_building_collision -----

Purpose: This function checks if the duck has colliding with the building. If the output is true, game over. 

Input: Model *model: A pointer to the game's current model

Output: boolean value: true if collision occurs, else false
*/
bool duck_building_collision(const Model *model) {
    int i;

    int duck_left = model->duck.x;
    int duck_right = model->duck.x + DUCK_WIDTH;
    int duck_top = model->duck.y;
    int duck_bottom = model->duck.y + DUCK_HEIGHT;

    for (i = 0; i < MAX_BUILDINGS; i++) {
        int b_left = model->buildings[i].x;
        int b_right = model->buildings[i].x + model->buildings[i].width;
        int b_top = model->buildings[i].y;
        int b_bottom = model->buildings[i].y + model->buildings[i].height;

        if (duck_right > b_left &&
            duck_left < b_right &&
            duck_bottom > b_top &&
            duck_top < b_bottom) {
            return true;
        }
    }

    return false;
}
/* ----- Function: building_left_border -----

Purpose: This function checks if the building has collided with the left border of the screen to then be removed from the screen
         if the output is true.

Input: Building *building: A pointer to the Building object

Output: boolean value: true if building is of the screen, else false
*/
bool building_left_border(const Building *building) {
    return (building->x + building->width) <= 0;
}

/* ----- Function: duck_max_height -----

Purpose: This function checks if the duck has reached its maximum jump height for it then to descend.

Input: Duck *duck: pointer to Duck object 

Output: boolean value: true if duck has reached the maximum jump height, else false
*/
bool duck_max_height(const Duck *duck) {
    return duck->y <= MAX_JUMP_Y;
}

/* ----- Function: duck_ground_collision -----

Purpose: This function checks if the duck has collided with the ground.

Input: Duck *duck: pointer to Duck object

Output: boolean value: true if duck has hit the ground, else false
*/
bool duck_ground_collision(const Duck *duck) {
    return duck->y >= (SCREEN_HEIGHT - FLOOR_BUFFER - DUCK_HEIGHT);
}


/* ----- Function: process_cond_events -----

Purpose: Checks for conditional game events based on the current model state,
         such as collisions/game ending conditions. The model updates accordingly.

Input: Model *model: pointer to current game state

Output: None

*/
void process_cond_events(Model *model) {
    int i;

    if (duck_building_collision(model)) {
        model->quit = true;
    }

    for (i = 0; i < MAX_BUILDINGS; i++) {
        if (building_left_border(&model->buildings[i])) {
            model->buildings[i] = model_create_building();
        }
    }
}