#ifndef SYNCH_H
#define SYNCH_H

#include "model.h"

/* Building appearing gradually with speed of appearence increasing over time */
void building_appearance(Model *model, unsigned int elapsed_ticks);

/* Speed increase at intervals: 20s, 40s, 80s, etc */
void speed_increase(Model *model, unsigned int elapsed_ticks);

/* Score updates based on elapsed gameplay time */
void update_score(Model *model, unsigned int elapsed_ticks);


#endif 
