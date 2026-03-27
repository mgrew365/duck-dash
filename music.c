#include "psg.h"
#include "music.h"

typedef struct {
    int tone;
    int duration;
} Note;

/* Simple 4-note loop */
Note song[] = {
    {500, 20},
    {600, 20},
    {700, 20},
    {600, 20}
};

int current_note = 0;
UINT32 last_time = 0;

void start_music() {
    current_note = 0;
    last_time = 0;

    enable_channel(0, 1, 0);  
    set_volume(0, 10);
    set_tone(0, song[0].tone);
}

void update_music(UINT32 time_elapsed) {
    if (time_elapsed - last_time >= song[current_note].duration) {

        current_note = (current_note + 1) % 4;

        set_tone(0, song[current_note].tone);
        set_volume(0, 10);

        last_time = time_elapsed;
    }
}