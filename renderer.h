/*
File: RENDERER.H
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: February 23, 2026
File Description: Defines headers and interface for the renderer
module. It is part of drawing the game objects from the game model
to the screen using rasters.

*/

#ifndef RENDERER_H
#define RENDERER_H

#include "model.h"
#include "raster.h"
#include "types.h"

/*
Function: Render
Purpose: Renders the full frame of the game state at the current state
of the model.
Input: Model Pointer: the current game state to be rendered.
       Address(UINT8*): pointer to the start fo the memory of the frame buffer
Output: None/No direct value
*/
void render(const Model *model, UINT32 *base);

/*
Function: Render_Duck
Purpose: Draws the duck object to the screen. Based on its current position.
Input: Duck Pointer: the object to render
       Address(UINT8*): pointer to start of FB
Output: None/No direct value
*/
void render_duck(const Duck *duck, UINT32 *base);

/*
Function: Render_Building
Purpose: Draws the building object to the screen at its current psoition.
Input: Building Pointer: the object to render
       Address(UINT8*): pointer to start of FB
Output: None/No direct value
*/
void render_building(const Building *building, UINT32 *base);


#endif