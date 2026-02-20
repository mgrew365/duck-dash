#ifndef MODEL_H
#define MODEL_H

#include "types.h"

/* PROTOTYPES*/

/* Duck Object*/
typedef struct {
    unsigned int x, y;
    int delta_y;
} Duck;

/* Building Object */
typedef struct {
    unsigned int x, y;
    unsigned int width;
    unsigned int height;
} Building;

/* Main Game Model */
#define MAX_BUILDINGS 3 /* Maximum number of buildings on the screen (change as needed)*/

typedef struct {
    Duck duck;
    Building buildings[MAX_BUILDINGS];
    unisgned int score;
} Model;

/* STRUCTURES*/
/* BITMAPS*/
extern const UINT16 duck[];
extern const UINT16 building[];

/* Ducks movement (jump/fall)*/
void move_duck(Duck *duck);

/* Move buildings left towards the duck*/
void move_buildings(Building buildings[], int count);

/* Initialize the model to default game state */
void init_model(Model *model);

/* Increment score */
void increment_score(Model *model);


#endif
