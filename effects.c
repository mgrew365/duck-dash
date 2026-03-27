#include "psg.h"
#include "effects.h"
#include "types.h"

void play_game_start() {
    enable_channel(2, 1, 0);
    set_tone(2, 800);

    set_envelope(0x0A, 2000);
    set_volume(2, 16);   
}

void play_jump() {
    enable_channel(2, 1, 0);
    set_tone(2, 600);

    set_envelope(0x09, 1000);
    set_volume(2, 16);
}

void play_collision() {
    enable_channel(2, 1, 1);
    set_noise(20);
    set_tone(2, 200);

    set_envelope(0x0E, 4000);
    set_volume(2, 16);
}