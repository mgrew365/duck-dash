/*
File: EFFECTS.H
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 4 - COMP 2659 
Date Modified: April 2, 2026
File Description: This file declares all functions that are implemented in effects.c

*/
#ifndef EFFECTS_H
#define EFFECTS_H

#include "psg.h"

/* ----- Function: play_game_start -----

Purpose: Plays the game start sound effect when the game begins.
         Produces a short tone on channel 2.

Input: None

Output: None
*/
void play_game_start(void);


/* ----- Function: play_jump -----

Purpose: Plays the jump sound effect when the player jumps.
         Uses a short tone on channel 2 to indicate action feedback.

Input: None

Output: None
*/
void play_jump(void);


/* ----- Function: play_collision -----

Purpose: Plays the collision sound effect when the player hits an object.
         Uses noise and a low tone to simulate impact.

Input: None

Output: None
*/
void play_collision(void);

#endif
