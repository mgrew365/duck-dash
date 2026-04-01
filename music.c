#include "psg.h"
#include "music.h"

typedef struct {
    int tone;
    int duration;
} Note;

/* 🎵 MELODY (Channel A) — fast + catchy */
Note melody[] = {
    {600,2},{700,2},{800,2},{700,2},
    {750,2},{700,2},{600,3},{0,1},

    {800,2},{900,2},{1000,2},{900,2},
    {800,2},{700,2},{600,3},{0,1}
};

/* 🔊 BASS (Channel B) — constant motion */
Note bass[] = {
    {1000,4},{900,4},{800,4},{900,4},
    {1000,4},{900,4},{800,4},{900,4}
};

/* 🥁 RHYTHM (Channel C) — fast ticks */
Note rhythm[] = {
    {1,1},{0,1},{1,1},{0,1},
    {1,1},{0,1},{1,1},{0,1}
};

int m_index = 0;
int b_index = 0;
int r_index = 0;

UINT32 last_time = 0;

/* START MUSIC */
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

/* UPDATE MUSIC */
void update_music(UINT32 time_elapsed) {

    int speed = 1;

    /* 🔥 dynamic speed (feels like runner accelerating) */
    if (time_elapsed > 200) speed = 1;
    if (time_elapsed > 400) speed = 0;

    if (time_elapsed - last_time >= (speed + 1)) {

        /* 🎵 MELODY */
        m_index = (m_index + 1) % 16;

        if (melody[m_index].tone != 0)
            set_tone(0, melody[m_index].tone);

        /* 🔊 BASS */
        b_index = (b_index + 1) % 8;
        set_tone(1, bass[b_index].tone);

        /* 🥁 RHYTHM */
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