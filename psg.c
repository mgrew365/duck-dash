#include <osbind.h>
#include "psg.h"
#include "types.h"

#define PSG_REG_SELECT 0xFF8800
#define PSG_REG_WRITE  0xFF8802

static volatile UINT8 *const psg_reg = (UINT8 *)0xFF8800;
static volatile UINT8 *const psg_val = (UINT8 *)0xFF8802;

void write_psg(int reg, UINT8 val) {
    long old_ssp;

    if (reg < 0 || reg > 15) return;

    old_ssp = Super(0);

    *psg_reg = (UINT8)reg;
    *psg_val = val;

    Super(old_ssp);
}

/* FIXED */
UINT8 read_psg(int reg) {
    long old_ssp;
    UINT8 value;

    if (reg < 0 || reg > 15) return 0;

    old_ssp = Super(0);

    *psg_reg = (UINT8)reg;
    value = *psg_val;

    Super(old_ssp);

    return value;
}

/* Tone */
void set_tone(int channel, int tuning) {
    int fine = channel * 2;
    int coarse = fine + 1;

    write_psg(fine, tuning & 0xFF);
    write_psg(coarse, (tuning >> 8) & 0x0F);
}

void set_volume(int channel, int volume) {
    if (channel < 0 || channel > 2) return;

    /* volume 16+ = envelope mode */
    if (volume >= 16) {
        write_psg(8 + channel, 16);  
    } else {
        write_psg(8 + channel, volume & 0x0F);
    }
}

/* Mixer */
void enable_channel(int channel, int tone_on, int noise_on) {
    UINT8 mixer = 0xFF;

    if (channel == 0) {
        if (tone_on) mixer &= ~1;
        if (noise_on) mixer &= ~(1 << 3);
    } else if (channel == 1) {
        if (tone_on) mixer &= ~(1 << 1);
        if (noise_on) mixer &= ~(1 << 4);
    } else if (channel == 2) {
        if (tone_on) mixer &= ~(1 << 2);
        if (noise_on) mixer &= ~(1 << 5);
    }

    write_psg(7, mixer);
}

void stop_sound() {
    set_volume(0, 0);
    set_volume(1, 0);
    set_volume(2, 0);
}

void set_noise(int tuning) {
    if (tuning < 0 || tuning > 31) return;
    write_psg(6, tuning);
}

void set_envelope(int shape, unsigned int sustain) {
    write_psg(11, sustain & 0xFF);
    write_psg(12, (sustain >> 8) & 0xFF);
    write_psg(13, shape);
}