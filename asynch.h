#ifndef ASYNCH_H
#define ASYNCH_H

#include "model.h"

/* Duck Jump - triggered when up key is pressed */
void async_duck_jump(Model *model);

/* Quit game - triggered when ESC key is pressed */
void async_quit_game(Model *model);

#endif 
