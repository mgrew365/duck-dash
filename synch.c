#include "synch.h"

#define TICKS_PER_SECOND 70

/* Change below as need be */
#define SPEED_UP_1 20
#define SPEED_UP_2 40
#define SPEED_UP_3 80

/* Building appearing gradually with speed of appearence increasing over time 
   This function is not complete at the moment as we cant actually test this aspect yet
*/
void building_appearance(Model *model, unsigned int elapsed_ticks) {
    (void)model;
    (void)elapsed_ticks;
}

/* Speed increase at intervals: 20s, 40s, 80s, etc */
void speed_increase(Model *model, unsigned int elapsed_ticks) {
    unsigned int elapsed_seconds = elapsed_ticks / TICKS_PER_SECOND;
    unsigned int i;

    if (elapsed_seconds == SPEED_UP_1 || elapsed_seconds == SPEED_UP_2 || elapsed_seconds == SPEED_UP_3)
    {
        for (i = 0; i < MAX_BUILDINGS; i++) {
            /* Increase speed by making delta_x more negative */
            model->buildings[i].delta_x -= 1;
        }
    }
}
  
/* Score updates based on elapsed gameplay time */
void update_score(Model *model, unsigned int elapsed_ticks) {
    model->score = elapsed_ticks / TICKS_PER_SECOND;
}