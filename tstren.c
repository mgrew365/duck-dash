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

void wait_key(void) {
    Cnecin();
}

int main() {
    UINT32 *base = (UINT32 *)Physbase();

    Model myModel = testDuckDashSnapshot;

    /* Render the state to the screen */
    render(&myModel, base);
    
    wait_key();

    /*Clear screen after key press*/
    clear_screen(base);
    
    return 0;
}