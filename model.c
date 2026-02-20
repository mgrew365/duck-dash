#include <osbind.h>
#include "model.h"

/* Leave extra space at the bottom of screen so duck doesnt land on edge of screen, lands on floor */
#define FLOOR_BUFFER 40

/* What is the actual size of the duck?*/
#define DUCK_WIDTH 32
#define DUCK_HEIGHT 32

/* Maybe we add a helper function to help detect collisions and call this function within move_duck*/

/* Ducks movement (jump/fall)*/
void move_duck(Duck *duck) {
    /* Ensure duck stays in the screen*/
    if (duck->y < 0) {
        duck->y = 0;
    }

    if (duck->y > 400 - FLOOR_BUFFER) {
        duck->y = 400 - FLOOR_BUFFER;
    }
    
}
/* Move buildings left towards the duck*/
/*idek how to start this*/
void move_buildings(Building buildings[], int count) {

}

/* Increment score */
void increment_score(Model *model) {
    model->score++;
}