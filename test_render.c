/*
File: TEST_RENDER.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: February 23, 2026
File Description: The test driver used to verify renderer.c. Renders multiple
model states and waits for user input between the frames to be able to visually inspect.

*/

#include <osbind.h>
#include <stdio.h>

#include "renderer.h"
#include "model.h"

#define BASE ((UINT8*)Physbase())

/*
Function: wait_key
Purpose: pauses the program execution until user inputs a key
*/
void wait_key()
{
    Cnecin();
}

 /*
Function: print_model
Purpose: prints all the model object values
Input: model pointer: model to the display
*/
void print_model(const Model *m)
{
    printf("Duck: (%u,%u)\n", m->duck.x, m->duck.y);
    printf("Score: %u\n", m->score);

    for (int i=0;i<MAX_BUILDINGS;i++)
        printf("Building %d: (%u,%u)\n", i,
               m->buildings[i].x,
               m->buildings[i].y);
}

/*
Function: test_initial
Purpose: test rendering of the inital model state.
*/
void test_initial()
{
    Model m = model_create_initial();

    print_model(&m);
    render(&m, BASE);
    wait_key();
}

/*
Function: test_move_duck
Purpose: test rendering when the position of the duck moves
*/
void test_move_duck()
{
    Model m = model_create_initial();

    m.duck.x += 50;
    m.duck.y += 20;

    print_model(&m);
    render(&m, BASE);
    wait_key();
}

/*
Function: test_buildings
Purpose: test rendering when the position of the buildings moves
*/
void test_buildings()
{
    Model m = model_create_initial();

    for(int i=0;i<MAX_BUILDINGS;i++)
        m.buildings[i].y += i*10;

    print_model(&m);
    render(&m, BASE);
    wait_key();
}

/*
Function: test_score
Purpose: test rendering of score text
*/
void test_score()
{
    Model m = model_create_initial();

    m.score = 1234;

    print_model(&m);
    render(&m, BASE);
    wait_key();
}

/*
Function: Main
Purpose: Runs all the rendering test in sequence.
*/
int main()
{
    printf("Test Start\n");

    test_initial();
    test_move_duck();
    test_buildings();
    test_score();

    printf("\n tests complete.\n");
    return 0;
}