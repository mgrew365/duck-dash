/*
File: RENDERER.C
Names: Manroop Grewal, Sarah Fazal
Instructor: Steve Kalmar
Assignment: Checkpoint 2 - COMP 2659 
Date Modified: February 21, 2026
File Description: 

*/

#include "renderer.h"
#include "raster.h"

#define DUCK_HEIGHT 16
#define BUILDING_HEIGHT 32


/* main renderer function */
void render(const Model *model, UINT8 *base)
{
    unsigned int i;

    clear_screen((UINT32*)base);

    render_duck(&model->duck, base);

    for (i = 0; i < MAX_BUILDINGS; i++)
        render_building(&model->buildings[i], base);

    render_score(model->score, base);
}


/* RENDER DUCK */
void render_duck(const Duck *duck, UINT8 *base)
{
    plot_bitmap_16(
        (UINT16*)base,
        duck->y,
        duck->x,
        DUCK_HEIGHT
    );
}


/* RENDER BUILDING */
void render_building(const Building *b, UINT8 *base)
{
    plot_bitmap_32(
        (UINT32*)base,
        b->y,
        b->x,
        BUILDING_HEIGHT
    );
}


/* RENDER SCORE TEXT */
void render_score(unsigned int score, UINT8 *base)
{
    char text[12];
    int i = 0;

    text[i++] = 'S';
    text[i++] = 'c';
    text[i++] = 'o';
    text[i++] = 'r';
    text[i++] = 'e';
    text[i++] = ':';
    text[i++] = ' ';

    if (score == 0)
        text[i++] = '0';
    else {
        unsigned int s = score;
        char temp[6];
        int j = 0;

        while (s > 0) {
            temp[j++] = '0' + (s % 10);
            s /= 10;
        }
        while (j--)
            text[i++] = temp[j];
    }

    text[i] = '\0';

    plot_string(base, 10, 10, text);
}