#include "cond.h"
#define SCREEN_WIDTH   640
#define SCREEN_HEIGHT  400

/* Change below as need be*/
#define FLOOR_BUFFER   40      /* duck stands on floor above bottom */
#define DUCK_WIDTH    16
#define DUCK_HEIGHT   16
#define MAX_JUMP_Y    80 

/* Duck collides with building resulting in game over */
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


/* Building collides with left border to be removed from the screen */
bool building_left_border(const Building *building) {
    return (building->x + building->width) <= 0;
}


/* Duck reaches its maximum jump height and starts to descend afterwords */
bool duck_max_height(const Duck *duck) {
    return duck->y <= MAX_JUMP_Y;
}


/* Duck collides with ground stopping descent */
bool duck_ground_collision(const Duck *duck) {
    return duck->y >= (SCREEN_HEIGHT - FLOOR_BUFFER - DUCK_HEIGHT);
}


/* Restart game when gameplay has ended */
bool restart_game(const Model *model) {
    (void)model;

    return false;
}
