#ifndef COND_H
#define COND_H

#include "model.h"
#include <stdbool.h>

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
