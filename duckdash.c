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
#include "sscreen.h"
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


void run_game()
{
    Model model = model_create_initial();

    UINT32 timeThen, timeNow;
    UINT32 elapsed_ticks = 0;
    char key;

    UINT32 *front;
    UINT32 *back;
    UINT32 *temp;

    /* ===== initialize model ===== */
    model.quit = false;

    /* ===== buffer setup ===== */
    front = buffer1;
    back  = buffer2;

    /* ===== render first frame ===== */
    render(&model, back);
    wait_for_vbl();
    Setscreen(back, back, -1);

    temp = front;
    front = back;
    back = temp;

    timeThen = get_time();

    /* ===== main game loop ===== */
    while (!model.quit)
    {
        /* ===== ASYNC INPUT ===== */
        if (has_input())
        {
            key = get_input();
            while (has_input()) get_input();

            /* process async event */
            if (key == ESC_KEY)
                quit_game(&model);
            else if (key == SPACE_BAR)
                duck_jump(&model);
        }

        /* ===== CLOCK CHECK ===== */
        timeNow = get_time();

        if (timeNow > timeThen)
        {
            elapsed_ticks++;

            /* ===== SYNC EVENTS ===== */
            update_duck(&model);
            update_buildings(&model);

            /* ===== CONDITIONAL EVENTS ===== */
            building_appearance(&model, elapsed_ticks);
            speed_increase(&model, elapsed_ticks);
            update_score(&model, elapsed_ticks);
            process_cond_events(&model);

            timeThen = timeNow;

            /* ===== RENDER NEXT FRAME ===== */
            render(&model, back);
            wait_for_vbl();
            Setscreen(back, back, -1);

            temp = front;
            front = back;
            back = temp;
        }
    }
}


int main()
{
    UINT32 *base;
    int choice;

    /* ALIGN BUFFERS */
    buffer1 = (UINT32 *)(((long)raw_buffer1 + 255) & ~255);
    buffer2 = (UINT32 *)(((long)raw_buffer2 + 255) & ~255);

    base = (UINT32 *)Physbase();

    /* ===== MAIN PROGRAM LOOP ===== */
    while (1)
    {
        /* splash screen */
        choice = run_splash_screen(base);

        if (choice == 0)
            break;

        /* run game */
        run_game();
    }

    return 0;
}