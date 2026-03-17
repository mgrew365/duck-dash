/*
File: RENDERER.H
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: March 15, 2026
File Description: Defines headers and interface for the renderer
                  module. It is part of drawing the game objects from the game model
                  to the screen using rasters.
*/

#ifndef RENDERER_H
#define RENDERER_H

#include "model.h"
#include "raster.h"
#include "types.h"


/* ----- Function: get_video_base -----
Purpose: Retrieves the base address of the physical video memory so that
         graphics can be drawn directly to the screen.

Input: None

Output: Pointer to the base address of video memory
*/
extern void* get_video_base(void);


/* ----- Function: int_to_string -----

Purpose: Converts an unsigned integer into a null-terminated string.
         
Input: num (unsigned int): the number to convert
       str (char *): character array where the resulting string will be stored

Output: None (the result is stored in the provided character array)
*/
void int_to_string(unsigned int num, char *str);

/* ----- Function: render -----

Purpose: draws the complete frame by cearing the screen and rendering all objects.

Input: Model pointer: current state of the game play.
       base(UINT32*): start address of the frame buffer.

Output: None
*/
void render(const Model *model, UINT32 *base);

/* ----- Function: render_duck -----

Purpose: Draws the duck object to the screen. Based on its current position.

Input: Duck Pointer: the object to render
       base(UINT32*): pointer to start of FB
       
Output: None
*/
void render_duck(const Duck *duck, UINT32 *base);


/* ----- Function: render_building -----

Purpose: Plots the building bitmap at the model coordinates.

Input: Building pointer: building object
       base(UINT32*): start address of the frame buffer.

Output: None
*/
void render_building(const Building *building, UINT32 *base);


#endif