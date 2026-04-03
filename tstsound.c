/*
File: TSTSOUND.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 4 - COMP 2659 
Date Modified: April 2, 2026
File Description: This is a test driver for the PSG sound/effects.
                  This file tests sound that is later implemented in 
                  the main game.
*/

#include <osbind.h>
#include "psg.h"
#include "music.h"
#include "effects.h"

/* ----- Function: delay -----

Purpose: Provides a simple blocking delay for testing sound playback timing.

Input: long time: Delay duration multiplier

Output: None
*/
void delay(long time) {
    long i;
    for (i = 0; i < time * 1000; i++);
}

/* ----- Function: test_psg -----

Purpose: Tests basic PSG functionality including tone, volume control, and channel enabling.

Input: None

Output: None
*/
void test_psg() {
    Cconws("Testing PSG...\r\n");

    enable_channel(0, 1, 0);
    set_volume(0, 10);
    set_tone(0, 500);

    delay(2000);

    set_tone(0, 800);
    delay(2000);

    stop_sound();

    Cconws("PSG test done.\r\n\n");
}


/* ----- Function: test_effects -----

Purpose: Tests game sound effects such as start, jump, and collision sounds.

Input: None

Output: None
*/
void test_effects() {
    Cconws("Testing Effects...\r\n");

    Cconws("Game Start Sound\r\n");
    play_game_start();
    delay(2000);

    Cconws("Jump Sound\r\n");
    play_jump();
    delay(2000);

    Cconws("Collision Sound\r\n");
    play_collision();
    delay(3000);

    stop_sound();

    Cconws("Effects test done.\r\n\n");
}


/* ----- Function: main -----

Purpose: Entry point for the sound test program. Runs PSG and effects tests.

Input: None

Output: Program exit status (int)
*/
int main() {

    Cconws("SOUND TEST DRIVER\r\n\n");

    test_psg();
    test_effects();

    Cconws("All tests complete.\r\n");

    return 0;
}