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
} Model;


/* STRUCTURES*/
/* BITMAPS*/
extern const UINT16 duck[];
extern const UINT16 building[];
extern Model testDuckDashSnapshot;

/* Ducks movement (jump/fall)*/
void move_duck(Duck *duck);

/* Move buildings left towards the duck*/
void move_buildings(Building buildings[], unsigned int count);

#endif
