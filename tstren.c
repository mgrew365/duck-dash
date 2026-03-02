/*
File: TEST_RENDER.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: March 1, 2026
File Description: Test driver for the renderer. Displays a static frame.
*/

#include <osbind.h>
#include "renderer.h"
#include "model.h"

int main() {
    /* Get the physical base of the Atari ST screen */
    UINT32 *base = (UINT32 *)Physbase();

    /* Use the test snapshot from model.c [cite: 6] */
    Model myModel = testDuckDashSnapshot;

    /* Render the state to the screen */
    render(&myModel, base);

    /* Wait for a keypress before returning to GEM [cite: 8] */
    Cnecin();

    return 0;
}