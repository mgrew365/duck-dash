/*
File: MUSIC.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 4 - COMP 2659 
Date Modified: April 2, 2026
File Description: Implements the game music using the Yamaha PSG chip.
                  It handles melody, bass, and rhythm sequencing and updates
                  sound output over gameplay.
*/

#include "psg.h"
#include "music.h"

typedef struct {
    int tone;
    int duration;
} Note;

/* MELODY (Channel A) */
Note melody[] = {
    {600,2},{700,2},{800,2},{700,2},
    {750,2},{700,2},{600,3},{0,1},

    {800,2},{900,2},{1000,2},{900,2},
    {800,2},{700,2},{600,3},{0,1}
};

/* BASS (Channel B)  */
Note bass[] = {
    {1000,4},{900,4},{800,4},{900,4},
    {1000,4},{900,4},{800,4},{900,4}
};

/* RHYTHM (Channel C) */
Note rhythm[] = {
    {1,1},{0,1},{1,1},{0,1},
    {1,1},{0,1},{1,1},{0,1}
};

int m_index = 0;
int b_index = 0;
int r_index = 0;

UINT32 last_time = 0;

/* ----- Function: start_music -----

Purpose: Initializes and starts the background music by resetting
         all channel indices, configuring PSG channels, and setting initial tones.

Input: None

Output: None
*/
void start_music() {

    m_index = b_index = r_index = 0;
    last_time = 0;

    enable_channel(0, 1, 0);  /* melody */
    enable_channel(1, 1, 0);  /* bass */
    enable_channel(2, 0, 1);  /* rhythm */

    set_volume(0, 12);
    set_volume(1, 9);
    set_volume(2, 6);

    set_tone(0, melody[0].tone);
    set_tone(1, bass[0].tone);
}

/* ----- Function: update_music -----

Purpose: Updates the music over time by advancing melody,
         bass, and rhythm patterns based on elapsed time.

Input: UINT32 time_elapsed: Current system time used to control music timing

Output: None
*/
void update_music(UINT32 time_elapsed) {

    int speed = 1;

    /* dynamic speed */
    if (time_elapsed > 200) speed = 1;
    if (time_elapsed > 400) speed = 0;

    if (time_elapsed - last_time >= (speed + 1)) {

        /* MELODY */
        m_index = (m_index + 1) % 16;

        if (melody[m_index].tone != 0)
            set_tone(0, melody[m_index].tone);

        /* BASS */
        b_index = (b_index + 1) % 8;
        set_tone(1, bass[b_index].tone);

        /* RHYTHM */
        r_index = (r_index + 1) % 8;

        if (rhythm[r_index].tone == 0) {
            set_volume(2, 0);
        } else {
            set_noise(8);
            set_volume(2, 5);
        }

        last_time = time_elapsed;
    }
}

/* ----- Function: stop_music -----

Purpose: Stops all sound output by disabling audio channels.

Input: None

Output: None
*/
void stop_music() {
    stop_sound();
}