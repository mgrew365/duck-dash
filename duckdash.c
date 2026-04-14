/*
File: DUCKDASH.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 3 - COMP 2659 
Date Modified: April 2, 2026
File Description: Contains the main game loop for DuckDash. This file handles
                  initialization, timing, input processing, model updates, sound
                  conditional event processing, rendering, and double buffering.
Limitations: The duck speed is not optimal, this is possibly issue in rendering and the clear screen. 
*/
#include "duckdash.h"
#include "model.h"
#include "renderer.h"
#include "input.h"
#include "asynch.h"
#include "synch.h"
#include "cond.h"
#include "sscreen.h"
#include "raster.h"

#include "music.h"
#include "psg.h"
#include "effects.h"

#include <osbind.h>

#define CLOCK_ADDRESS 0x462
#define SCREEN_SIZE 32000

/* Raw buffers for alignment */
UINT8 raw_buffer1[SCREEN_SIZE + 256];
UINT8 raw_buffer2[SCREEN_SIZE + 256];

/* Aligned buffers */
UINT32 *buffer1;
UINT32 *buffer2;

/* ----- Function: get_time -----

Purpose: Reads the system 70Hz TOS clock safely using supervisor mode.

Input: None

Output: Current system time (UINT32)
*/
UINT32 get_time() {
    UINT32 time;
    long old_ssp = Super(0);
    time = *((UINT32 *)CLOCK_ADDRESS);
    Super(old_ssp);
    return time;
}

/* ----- Function: wait_for_vbl -----

Purpose: Waits for vertical blanking interval to synchronize screen updates.

Input: None

Output: None
*/
void wait_for_vbl() {
    long old_ssp = Super(0);

    while (!(*((volatile UINT8 *)0xFFFF8209) & 0x80));
    while (*((volatile UINT8 *)0xFFFF8209) & 0x80);

    Super(old_ssp);
}


/* ----- Function: run_game -----

Purpose: Runs the main game loop including input handling, model updates,
         rendering, and music updates.

Input: None

Output: None
*/
void run_game() {
    /* Initialize model*/
    Model model = model_create_initial();

    UINT32 timeThen, timeNow;
    UINT32 elapsed_ticks = 0;

    char key;

    UINT32 *front;
    UINT32 *back;
    UINT32 *temp;

    /* Buffer setup */
    front = buffer1;
    back  = buffer2;

    /* Render first frame */
    render(&model, back);
    wait_for_vbl();
    Setscreen(back, back, -1);

    temp = front;
    front = back;
    back = temp;

    /* Start music */
    start_music();

    /* Set quit = false */
    model.quit = false;
    timeThen = get_time();

    /* MAIN LOOP */
    while (!model.quit) {

        /* Process Async input if input is pending */
        if (has_input()) {
            key = get_input();

            while (has_input())
                get_input();

            if (key == ESC_KEY)
                quit_game(&model);
            else if (key == SPACE_BAR)
                duck_jump(&model);
        }

        /* If the clock has ticked */
        timeNow = get_time();

        if (timeNow > timeThen) {

            elapsed_ticks++;

            /* Process sync events */
            update_duck(&model);
            update_buildings(&model);

            /* Process cond events */
            building_appearance(&model, elapsed_ticks);
            speed_increase(&model, elapsed_ticks);
            update_score(&model, elapsed_ticks);
            process_cond_events(&model);

            /* Render next frame*/
            render(&model, back);

            wait_for_vbl();
            Setscreen(back, back, -1);

            temp = front;
            front = back;
            back = temp;

            /* Update music*/
            update_music(timeNow);
        }
    }

    /* -------- GAME OVER SCREEN -------- */

    clear_screen(front);

    plot_string((UINT8*)front, 180, 260, "GAME OVER");
    plot_string((UINT8*)front, 280, 240, "PRESS ESC TO QUIT");

    wait_for_vbl();
    Setscreen(front, front, -1);

    /* wait for key press */
    while (!has_input());

    /* clear input buffer */
    while (has_input())
        get_input();

    stop_music();
}

/* ----- Function: main -----

Purpose: Entry point of the program. Runs splash screen and starts game loop.

Input: None

Output: Program exit code (int)
*/
int main() {
    UINT32 *base;
    int choice;

    buffer1 = (UINT32 *)(((long)raw_buffer1 + 255) & ~255);
    buffer2 = (UINT32 *)(((long)raw_buffer2 + 255) & ~255);

    base = (UINT32 *)Physbase();

    while (1) {
        choice = run_splash_screen(base);

        if (choice == 0)
            break;

        run_game();
    }

    return 0;
}