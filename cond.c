/*
File: COND.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: February 21, 2026
File Description: This file implements all conditional game event functions for Duck Dash. These events are used
                  to check the current game state hence they are boolean values to indicate whether a condition is met.

                  The conditional events include:
                    - Duck colliding with building
                    - Duck reaching its maximum jump height
                    - Duck colliding with ground
                    - Buildings leaving the screen
                    - Game restart conditions

*/
/*
File: COND.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: February 21, 2026
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
#define SCREEN_WIDTH   640
#define SCREEN_HEIGHT  400
#define FLOOR_BUFFER   40      /* duck stands on floor above bottom */
#define DUCK_WIDTH    16
#define DUCK_HEIGHT   16
#define MAX_JUMP_Y    80 


/* ----- Function: duck_building_collision -----

Purpose: This function checks if the duck has colliding with the building. If the output is true, game over. 

Input: Model *model: A pointer to the game's current model

Output: boolean value: true if collision occurs, else false
*/
bool duck_building_collision(const Model *model) {
    unsigned int i;

    unsigned int duck_left = model->duck.x;
    unsigned int duck_right = model->duck.x + DUCK_WIDTH;
    unsigned int duck_top = model->duck.y;
    unsigned int duck_bottom = model->duck.y + DUCK_HEIGHT;

    for (i = 0; i < MAX_BUILDINGS; i++) {
        unsigned int b_left = model->buildings[i].x;
        unsigned int b_right = model->buildings[i].x + model->buildings[i].width;
        unsigned int b_top = model->buildings[i].y;
        unsigned int b_bottom = model->buildings[i].y + model->buildings[i].height;

        if (duck_right > b_left  && duck_left < b_right && duck_bottom > b_top && duck_top < b_bottom) {
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

/* ----- Function: restart_game -----

Purpose: This function determines if a game should be restarted.

Input: Model *model: A pointer to current game model

Output: boolean value: The restart_game logic hasn't been fully implemented yet, so false at the current moment
*/
bool restart_game(const Model *model) {
    (void)model;

    return false;
}

void process_cond_events(Model *model) {
    int i;
    if (duck_max_height(&model->duck)) {
        model->duck.delta_y = 1; 
    }

    for (i = 0; i < MAX_BUILDINGS; i++) {
        if (building_left_border(&model->buildings[i])) {
            model->buildings[i] = model_create_building(); 
        }
    }

}