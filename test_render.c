/*
File: TEST_RENDER.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: February 21, 2026
File Description: 

*/

#include <osbind.h>
#include <stdio.h>

#include "renderer.h"
#include "model.h"

#define BASE ((UINT8*)Physbase())

void wait_key()
{
    Cnecin();
}


void print_model(const Model *m)
{
    printf("Duck: (%u,%u)\n", m->duck.x, m->duck.y);
    printf("Score: %u\n", m->score);

    for (int i=0;i<MAX_BUILDINGS;i++)
        printf("Building %d: (%u,%u)\n", i,
               m->buildings[i].x,
               m->buildings[i].y);
}


void test_initial()
{
    Model m = model_create_initial();

    print_model(&m);
    render(&m, BASE);
    wait_key();
}


void test_move_duck()
{
    Model m = model_create_initial();

    m.duck.x += 50;
    m.duck.y += 20;

    print_model(&m);
    render(&m, BASE);
    wait_key();
}


void test_buildings()
{
    Model m = model_create_initial();

    for(int i=0;i<MAX_BUILDINGS;i++)
        m.buildings[i].y += i*10;

    print_model(&m);
    render(&m, BASE);
    wait_key();
}


void test_score()
{
    Model m = model_create_initial();

    m.score = 1234;

    print_model(&m);
    render(&m, BASE);
    wait_key();
}


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