/*
File: MODEL.H
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: March 1, 2026
File Description: This file defines the main data structures and function prototypes for the Duck
                  Dash game model. It includes definitions for Duck and Building objects, the main Model
                  structure containing the duck, buildings and score, and prototypes for functions that
                  change the game model. These prototypes incldue move_duck, move_buildings, and 
                  model_create_initial. This header declares buidling graphics and a test snapshot for the
                  initial game state. The functions in this file are implemented in model.c
*/
#ifndef MODEL_H
#define MODEL_H

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 400
#define MAX_BUILDINGS  4

#include "types.h"

/* PROTOTYPES*/

/* Duck Object*/
typedef struct {
    unsigned int x, y;
    int delta_y;        /* Vertical displacement*/
} Duck;

/* Building Object */
typedef struct {
    unsigned int x, y;
    int delta_x;        /* Horizontal displacement*/
    unsigned int width;
    unsigned int height;
} Building;

/* Main Game Model */
typedef struct {
    Duck duck;
    Building buildings[MAX_BUILDINGS];
    unsigned int score;
    bool quit;
} Model;

/* BITMAPS*/
/* 16-bit duck sprite */
extern const UINT32 duck_bitmap[];

/* 32-bit building sprite */
extern const UINT32 building_bitmap[];

/* Test snapshot of initial state */
extern Model testDuckDashSnapshot;


/* ----- Function: move_duck -----

Purpose: Updates the vertical position of the duck.

Input: Duck *duck: a pointer to duck object

Output: None
*/
void move_duck(Duck *duck);


/* ----- Function: move_buildings -----

Purpose: Updates the horizontal position of the buildings and moves them left towards
         the duck.

Input: buildings[]: an array of building objects
       count: number of buildings in the array

Output: None
*/
void move_buildings(Building buildings[], unsigned int count);

/* ----- Function: model_create_initial -----

Purpose: This function returns a copy of the initial game model for testing or restarting the game. 

Input: None

Output: Model object which contains initial duck, building position, and score
*/
Model model_create_initial();


Building model_create_building(void);
#endif
