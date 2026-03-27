/*
File: DUCKDASH.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 3 - COMP 2659 
Date Modified: March 27, 2026
File Description: Contains the main game loop for DuckDash. This file handles
                  initialization, timing, input processing, model updates,
                  conditional event processing, rendering, and buffer copying.
*/
#include "duckdash.h"
#include "model.h"
#include "renderer.h"
#include "input.h"
#include "asynch.h"
#include "synch.h"
#include "cond.h"
#include "music.h"
#include "effects.h"
#include <osbind.h>

#define CLOCK_ADDRESS 0x462
#define SCREEN_SIZE 32000

UINT32 screen_buffer[SCREEN_SIZE / 4];

/*----- Function: get_time -----
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

/* ----- Function: copy_buffer -----
Purpose: Copies the contents of the source screen buffer into the destination
         screen buffer for rendering.

Input: src (UINT32*): pointer to the source buffer
       dst (UINT32*): pointer to the destination buffer

Output: None
*/
void copy_buffer(UINT32 *src, UINT32 *dst) {
    int i;
    for (i = 0; i < SCREEN_SIZE / 4; i++) {
        dst[i] = src[i];
    }
}


/* ----- Function: main -----
Purpose: Entry point of the game. Initializes state and runs the main loop.

Input: None

Output: 0 on successful termination
*/
int main() {
    /* Initialize model*/
    Model model = model_create_initial();

    UINT32 timeThen, timeNow;
    UINT32 elapsed_ticks = 0;
    char key;
    UINT32 *video_base;

    int collision_played = 0;

    video_base = (UINT32 *)get_video_base();

    /* Render model (first frame)*/
    render(&model, screen_buffer);
    copy_buffer(screen_buffer, video_base);

    /*Start sound*/
    start_music();
    play_game_start();

    /* Set quit = false*/
    model.quit = false;

    timeThen = get_time();

    /* Main game loop which will be repeated until quit*/
    while (!model.quit) {
        /* Async events: process input if given */
        if (has_input()) {
            key = get_input();

            while (has_input()) {
                get_input();
            }

            if (key == ESC_KEY) {
                quit_game(&model);
            }
            else if (key == SPACE_BAR) {
                duck_jump(&model);
                play_jump();
            }
        }

        /* Sync events: processes on clock ticks*/
        timeNow = get_time();
        if (timeNow != timeThen) {

            elapsed_ticks++;

            update_duck(&model);
            update_buildings(&model);
            building_appearance(&model, elapsed_ticks);
            speed_increase(&model, elapsed_ticks);
            update_score(&model, elapsed_ticks);

            /* Cond events */
            process_cond_events(&model);

            /* When the duck collides with a building, sound is played*/
            if (model.quit && !collision_played) {
                play_collision();
                collision_played = 1;
            }

            /* Render model (next frame)*/
            render(&model, screen_buffer);
            copy_buffer(screen_buffer, video_base);

            update_music(elapsed_ticks);

            /* Update clock*/
            timeThen = timeNow;
        }
    }

    stop_sound();

    return 0;
}