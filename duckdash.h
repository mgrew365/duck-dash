/*
File: DUCKDASH.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 3 - COMP 2659 
Date Modified: March 15, 2026
File Description: Declares helper functions that are implemented in duckdash.c.
                  SPecifically, for timer and screen buffering.
*/

#ifndef DUCKDASH_H
#define DUCKDASH_H

#include "model.h"

/*----- Function: get_time -----
Purpose: Safely reads the TOS 70Hz system clock by entering supervisor mode.

Input: None

Output: Current value of the system clock (UINT32)
*/
UINT32 get_time(void);

/* ----- Function: copy_buffer -----
Purpose: Copies the contents of the source screen buffer into the destination
         screen buffer for rendering.

Input: src (UINT32*): pointer to the source buffer
       dst (UINT32*): pointer to the destination buffer

Output: None
*/
void copy_buffer(UINT32 *src, UINT32 *dst);

#endif