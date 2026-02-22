/*
File: RENDERER.H
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: February 21, 2026
File Description: 

*/

#ifndef RENDERER_H
#define RENDERER_H

#include "model.h"
#include "types.h"

void render(const Model *model, UINT8 *base);
void render_duck(const Duck *duck, UINT8 *base);
void render_building(const Building *b, UINT8 *base);
void render_score(unsigned int score, UINT8 *base);

#endif