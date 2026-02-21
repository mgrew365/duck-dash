#include "asynch.h"

/* Duck Jump - triggered when up key is pressed */
void duck_jump(Model *model) {
    /* Only jump if duck is not already moving upward */
    if (model->duck.delta_y >= 0) {
        model->duck.delta_y = -8;   /* jump strength (change as need be) */
    }
}

/* Quit game - triggered when ESC key is pressed 
   This function is not complete at the moment as we cant actually test this aspect yet
*/
void quit_game(Model *model) {
    (void)model; 
}