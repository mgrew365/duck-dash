#include <osbind.h>
#include "model.h"

/* Leave extra space at the bottom of screen so duck doesnt land on edge of screen, lands on floor */
#define FLOOR_BUFFER 40

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

/* Ducks movement (jump/fall)*/
void move_duck(Duck *duck) {
    duck->y += duck->delta_y;
}
/* Move buildings left towards the duck*/
void move_buildings(Building buildings[], unsigned int count) {
    unsigned int i;

    for (i = 0; i < count; i++) {
        buildings[i].x += buildings[i].delta_x;
    }
}

Model model_create_initial()
{
    return testDuckDashSnapshot;
}
