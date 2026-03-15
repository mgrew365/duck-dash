/*
File: RENDERER.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: March 15, 2026
File Description: Contains the implementation of rendering functions for all the game
                  play objects. Each of the functions draws a specfic object using the raster graphics.

*/

#include <osbind.h>
#include "renderer.h"
#include "raster.h"

#define DUCK_HEIGHT 32
#define BUILDING_HEIGHT 32

/* ----- Function: get_video_base -----
Purpose: Retrieves the base address of the physical video memory so that
         graphics can be drawn directly to the screen.

Input: None

Output: Pointer to the base address of video memory
*/
void* get_video_base(void) {
    return Physbase();
}

/* ----- Function: render -----

Purpose: draws the complete frame by cearing the screen and rendering all objects.

Input: Model pointer: current state of the game play.
       base(UINT32*): start address of the frame buffer.

Output: None
*/
void render(const Model *model, UINT32 *base) {
    int i;
    
    /* Clear the screen  */
    clear_screen(base);

    /*Render the Duck */
    render_duck(&model->duck, base);

    /* Render all Buildings*/
    for (i = 0; i < MAX_BUILDINGS; i++) {
        render_building(&model->buildings[i], base);
    }

    /* Render Score  */
    plot_string((UINT8 *)base, 10, 10, "SCORE: 0"); 
}



/* ----- Function: render_duck -----

Purpose: Draws the duck object to the screen. Based on its current position.

Input: Duck Pointer: the object to render
       base(UINT32*): pointer to start of FB
       
Output: None
*/
void render_duck(const Duck *duck, UINT32 *base) {
    /* Duck bitmap is 16-bit   */
    plot_32bit_bitmap((UINT32 *)base, duck->y, duck->x, duck_bitmap, DUCK_HEIGHT);
}


/* ----- Function: render_building -----

Purpose: Plots the building bitmap at the model coordinates.

Input: Building pointer: building object
       base(UINT32*): start address of the frame buffer.

Output: None
*/
void render_building(const Building *building, UINT32 *base) {
    /* Building width is 32 in model.c */
    plot_32bit_bitmap(base, building->y, building->x, building_bitmap, building->height);
}