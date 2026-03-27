#include <osbind.h>
#include "psg.h"
#include "music.h"
#include "effects.h"


/* Simple delay loop (not precise, but fine for testing) */
void delay(long time) {
    long i;
    for (i = 0; i < time * 1000; i++);
}

/* =========================
   PSG TEST
========================= */
void test_psg() {
    Cconws("Testing PSG...\r\n");

    enable_channel(0, 1, 0);
    set_volume(0, 10);
    set_tone(0, 500);

    delay(2000);

    set_tone(0, 800);
    delay(2000);

    stop_sound();

    Cconws("PSG test done.\r\n\n");
}
/* =========================
   EFFECTS TEST
========================= */
void test_effects() {
    Cconws("Testing Effects...\r\n");

    Cconws("Game Start Sound\r\n");
    play_game_start();
    delay(2000);

    Cconws("Jump Sound\r\n");
    play_jump();
    delay(2000);

    Cconws("Collision Sound\r\n");
    play_collision();
    delay(3000);

    stop_sound();

    Cconws("Effects test done.\r\n\n");
}

/* =========================
   MUSIC TEST
========================= */
void test_music() {
    UINT32 time;
    int i;

    time = 0;

    Cconws("Testing Music (loop for ~10 seconds)...\r\n");

    start_music();

    for (i = 0; i < 700; i++) {  
        update_music(time);
        time++;
        delay(20);
    }

    stop_sound();

    Cconws("Music test done.\r\n\n");
}

/* =========================
   MAIN TEST DRIVER
========================= */
int main() {

    Cconws("=== SOUND TEST DRIVER ===\r\n\n");

    test_psg();
    test_effects();
    test_music();

    Cconws("All tests complete.\r\n");

    return 0;
}