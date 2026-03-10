#include "model.h"
#include "renderer.h"
#include "input.h"
#include "asynch.h"
#include "synch.h"
#include "cond.h"

#define CLOCK_ADDRESS 0x462

/* ----- Function: get_time -----
Purpose: Safely reads the TOS 70Hz system clock by entering supervisor mode.
Input: None
Output: Current value of the system clock (UINT32)
*/
UINT32 get_time() {
    UINT32 time;
    long old_ssp = Super(0);    /* enter supervisory model */
    time = *((UINT32 *)CLOCK_ADDRESS);
    Super(old_ssp);            /* exit supervisory mode */
    return time;
}

/* ----- Function: main -----
Purpose: Entry point of the game. Initializes state and runs the main loop.
Input: None
Output: 0 on successful termination
*/
int main() {
    Model model;
    UINT32 timeThen, timeNow, timeElapsed;
    char key;

    init_model(&model);
    render(&model, get_video_base()); /* Initial render */
    timeThen = get_time();
    model.quit = 0;

    /*Main Game Loop */
    while (!model.quit) {
        
        /* checking keyboard input*/
        if (has_input()) {
            key = get_input();
            if (key == 27) {         /* ESC key to quit */
                quit_game(&model);
            } else if (key == ' ') {  /* Space/Up to jump */
                duck_jump(&model);
            }
        }

        /* Check for Clock Ticks */
        timeNow = get_time();
        timeElapsed = timeNow - timeThen;

        if (timeElapsed > 0) {
            building_appearance(&model, timeNow);
            speed_increase(&model, timeNow);
            update_score(&model, timeNow);

            if (duck_building_collision(&model)) {
                model.quit = 1;
            }

            render(&model, get_video_base());
            
            timeThen = timeNow;
        }
    }

    return 0;
}