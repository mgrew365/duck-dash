#include "model.h"
#include "renderer.h"
#include "input.h"
#include "asynch.h"
#include "synch.h"
#include "cond.h"

#define CLOCK_ADDRESS 0x462

/*extern long Super(int level);
extern void* get_video_base(void);
*/
/* ----- Function: get_time -----
Purpose: Safely reads the TOS 70Hz system clock by entering supervisor mode.
Input: None
Output: Current value of the system clock (UINT32)
*/
UINT32 get_time() {
    UINT32 time;
    long old_ssp = Super(0);
    time = *((UINT32 *)CLOCK_ADDRESS);
    Super(old_ssp);
    return time;
}

/* ----- Function: main -----
Purpose: Entry point of the game. Initializes state and runs the main loop.
Input: None
Output: 0 on successful termination
*/
int main() {
    Model model = model_create_initial();
    UINT32 timeThen, timeNow;
    char key;

    model.quit = false; 
    render(&model, get_video_base()); 

    timeThen = get_time();

    while (!model.quit) {
        if (has_input()) {
            key = get_input();
            if (key == ESC_KEY) {
                quit_game(&model);
            } else if (key == SPACE_BAR) {
                duck_jump(&model);
            }
        }

        timeNow = get_time();
        if (timeNow != timeThen) {
            move_duck(&model.duck); 
            move_buildings(model.buildings, MAX_BUILDINGS);
            
            if (duck_building_collision(&model)) {
                model.quit = true;
            }

            if (duck_ground_collision(&model.duck)) {
                model.duck.y = (400 - 40 - 16);
                model.duck.delta_y = 0;
            }

            render(&model, (UINT32*) get_video_base());
            timeThen = timeNow;
        }
    }

    return 0;
}