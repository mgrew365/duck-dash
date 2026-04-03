/*
File: PSG.H
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 4 - COMP 2659 
Date Modified: April 2, 2026
File Description: This file declares all functions that are implemented in psg.h.
*/
#ifndef PSG_H
#define PSG_H

#include "types.h"


/* ----- Function: write_psg -----

Purpose: Writes a value to a PSG register.

Input: int reg: PSG register number (0–15)
       UINT8 val: Value to write

Output: None
*/
void write_psg(int reg, UINT8 val);


/* ----- Function: read_psg -----

Purpose: Reads a value from a PSG register.

Input: int reg: PSG register number (0–15)

Output: UINT8: Value stored in the register
*/
UINT8 read_psg(int reg);


/* ----- Function: set_tone -----

Purpose: Sets the frequency (pitch) of a PSG channel.

Input: int channel: Channel number (0–2)
       int tuning: Frequency value

Output: None
*/
void set_tone(int channel, int tuning);


/* ----- Function: set_volume -----

Purpose: Sets the volume level of a PSG channel.

Input: int channel: Channel number (0–2)
       int volume: Volume level (0–15)

Output: None
*/
void set_volume(int channel, int volume);


/* ----- Function: enable_channel -----

Purpose: Enables or disables tone and noise for a PSG channel.

Input: int channel: Channel number (0–2)
       int tone_on: 1 = enable tone, 0 = disable
       int noise_on: 1 = enable noise, 0 = disable

Output: None
*/
void enable_channel(int channel, int tone_on, int noise_on);


/* ----- Function: set_noise -----

Purpose: Sets noise generator frequency for percussion effects.

Input: int tuning: Noise frequency (0–31)

Output: None
*/
void set_noise(int tuning);


/* ----- Function: set_envelope -----
Purpose: Configures PSG envelope generator for special sound effects.

Input: int shape: Envelope shape type
       unsigned int sustain: Envelope duration

Output: None
*/
void set_envelope(int shape, unsigned int sustain);


/* ----- Function: stop_sound -----
Purpose: Stops all sound output by muting all PSG channels.

Input: None

Output: None
*/
void stop_sound(void);

#endif