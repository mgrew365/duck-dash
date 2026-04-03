/*
File: EFFECTS.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 4 - COMP 2659 
Date Modified: April 2, 2026
File Description: This file declares all sound effect functions used in the game.
                  These effects are triggered by gameplay events such as jumping,
                  collisions, and game start.
*/
#include "psg.h"
#include "effects.h"
#include "types.h"

/* ----- Function: play_game_start -----

Purpose: Plays the game start sound effect when the game begins.
         Produces a short tone on channel 2.

Input: None

Output: None
*/
void play_game_start() {
    enable_channel(2, 1, 0);
    set_tone(2, 800);

    set_envelope(0x0A, 2000);
    set_volume(2, 16);   
}

/* ----- Function: play_jump -----

Purpose: Plays the jump sound effect when the player jumps.
         Uses a short tone on channel 2 to indicate action feedback.

Input: None

Output: None
*/
void play_jump() {
    enable_channel(2, 1, 0);
    set_tone(2, 600);

    set_envelope(0x09, 1000);
    set_volume(2, 16);
}

/* ----- Function: play_collision -----

Purpose: Plays the collision sound effect when the player hits an object.
         Uses noise and a low tone to simulate impact.

Input: None

Output: None
*/
void play_collision() {
    enable_channel(2, 1, 1);
    set_noise(20);
    set_tone(2, 200);

    set_envelope(0x0E, 4000);
    set_volume(2, 16);
}