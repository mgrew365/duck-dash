#ifndef COND_H
#define COND_H

#include "model.h"

/* Define bool */
#ifndef BOOL_DEFINED
#define BOOL_DEFINED
typedef enum { false = 0, true = 1 } bool;
#endif

/* Duck collides with building resulting in game over */
bool duck_building_collision(const Model *model);

/* Building collides with left border to be rem oved from the screen */
bool building_left_border(const Building *building);

/* Duck reaches its maximum jump height and starts to descend afterwords */
bool duck_max_height(const Duck *duck);

/* Duck collides with ground stopping descent */
bool duck_ground_collision(const Duck *duck);

/* Restart game when gameplay has ended */
bool restart_game(const Model *model);

#endif 