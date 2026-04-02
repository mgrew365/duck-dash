/*
File: DUCKDASH.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 3 - COMP 2659 
Date Modified: March 15, 2026
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
#include <osbind.h>

#define CLOCK_ADDRESS 0x462
#define SCREEN_SIZE 32000

/* Raw buffers for alignment */
UINT8 raw_buffer1[SCREEN_SIZE + 256];
UINT8 raw_buffer2[SCREEN_SIZE + 256];

/* Aligned buffers */
UINT32 *buffer1;
UINT32 *buffer2;

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

/*----- Function: wait_for_vbl -----*/
void wait_for_vbl() {
    long old_ssp = Super(0);

    while (!(*((volatile UINT8 *)0xFFFF8209) & 0x80));
    while (*((volatile UINT8 *)0xFFFF8209) & 0x80);

    Super(old_ssp);
}

/* ----- Function: main -----
Purpose: Entry point of the game. Initializes state and runs the main loop.

Input: None

Output: 0 on successful termination
*/
int main() {
    Model model = model_create_initial();

    UINT32 timeThen, timeNow;
    UINT32 elapsed_ticks = 0;
    char key;

    UINT32 *front;
    UINT32 *back;
    UINT32 *temp;

    /* C89 variable declarations */
    int max_updates;
    int updates;
    int updated;

    /* -------- ALIGN BUFFERS -------- */
    buffer1 = (UINT32 *)(((long)raw_buffer1 + 255) & ~255);
    buffer2 = (UINT32 *)(((long)raw_buffer2 + 255) & ~255);

    front = buffer1;
    back  = buffer2;

    model.quit = false;

    /* -------- INITIAL FRAME -------- */
    render(&model, back);
    wait_for_vbl();
    Setscreen(back, back, -1);

    temp = front;
    front = back;
    back = temp;

    timeThen = get_time();

    /* -------- MAIN LOOP -------- */
    while (!model.quit) {

        /* -------- INPUT -------- */
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
            }
        }

        /* -------- TIMING -------- */
        timeNow = get_time();

        max_updates = 2;
        updates = 0;
        updated = 0;

        while (timeNow > timeThen && updates < max_updates) {

            elapsed_ticks++;

            update_duck(&model);
            update_buildings(&model);
            building_appearance(&model, elapsed_ticks);
            speed_increase(&model, elapsed_ticks);
            update_score(&model, elapsed_ticks);

            process_cond_events(&model);

            timeThen++;
            updates++;
            updated = 1;
        }

        /* -------- RENDER -------- */
        if (updated) {
            render(&model, back);

            wait_for_vbl();

            Setscreen(back, back, -1);

            /* swap buffers */
            temp = front;
            front = back;
            back = temp;
        }
    }

    return 0;
}