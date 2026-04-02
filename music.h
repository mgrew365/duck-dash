#ifndef MUSIC_H
#define MUSIC_H

#include "psg.h"
#include "types.h"

/* ----- Function: start_music -----

Purpose: Initializes and starts the background music by resetting
         all channel indices, configuring PSG channels, and setting initial tones.

Input: None

Output: None
*/
void start_music(void);


/* ----- Function: update_music -----

Purpose: Updates the music over time by advancing melody,
         bass, and rhythm patterns based on elapsed time.

Input: UINT32 time_elapsed: Current system time used to control music timing

Output: None
*/
void update_music(UINT32 time_elapsed);


/* ----- Function: stop_music -----

Purpose: Stops all sound output by disabling audio channels.

Input: None

Output: None
*/
void stop_music(void);

#endif