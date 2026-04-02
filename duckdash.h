/*
File: DUCKDASH.H
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 3 - COMP 2659 
Date Modified: April 2, 2026
File Description: Declares helper functions that are implemented in duckdash.c.
                  Specifically, for timer and screen buffering.
*/

#ifndef DUCKDASH_H
#define DUCKDASH_H

#include "types.h"
#include "model.h"

#include <osbind.h>

/* ----- Function: get_time -----

Purpose: Reads the system 70Hz TOS clock safely using supervisor mode.

Input: None

Output: Current system time (UINT32)
*/
UINT32 get_time(void);


/* ----- Function: wait_for_vbl -----

Purpose: Waits for vertical blanking interval to synchronize screen updates.

Input: None

Output: None
*/
void wait_for_vbl(void);


/* ----- Function: run_game -----

Purpose: Runs the main game loop including input handling, model updates,
         rendering, and music updates.

Input: None

Output: None
*/
void run_game(void);

#endif
