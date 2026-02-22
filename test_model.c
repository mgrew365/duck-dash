#include <stdio.h>

#include "model.h"
#include "asynch.h"
#include "synch.h"
#include "cond.h"

/* Atari ST clock */
#define TICKS_PER_SECOND 70

/* Helper function to print model state */
void print_model(const Model *model)
{
    unsigned int i;

    printf("MODEL STATE\n");
    printf("Duck: x=%u y=%u dy=%d\n",
           model->duck.x,
           model->duck.y,
           model->duck.delta_y);

    for (i = 0; i < MAX_BUILDINGS; i++) {
        printf("Building %u: x=%u y=%u dx=%d w=%u h=%u\n",
               i,
               model->buildings[i].x,
               model->buildings[i].y,
               model->buildings[i].delta_x,
               model->buildings[i].width,
               model->buildings[i].height);
    }

    printf("Score: %u\n", model->score);
    printf("---------------------\n\n");
}

int main(void)
{
    unsigned int tick;

    /* Create local copy of test snapshot */
    Model model = testDuckDashSnapshot;

    printf("INITIAL STATE\n");
    print_model(&model);

    /* ASYNCHRONOUS EVENT TEST */
    printf("ASYNC EVENT: Duck Jump\n");
    duck_jump(&model);
    print_model(&model);

    /* SYNCHRONOUS EVENT TEST */
    printf("SYNC EVENTS: Clock ticks & movement\n");

    for (tick = 0; tick <= 150; tick++) {
        /* Move buildings */
        move_buildings(model.buildings, MAX_BUILDINGS);

        /* Synchronous events */
        update_score(&model, tick);
        speed_increase(&model, tick);

        /* Print every second */
        if (tick % TICKS_PER_SECOND == 0) {
            printf("Tick %u (Time = %u sec)\n",
                   tick, tick / TICKS_PER_SECOND);
            print_model(&model);
        }
    }

    /* CONDITIONAL EVENT TEST */
    printf("CONDITIONAL EVENT TESTS\n");

    /* Force duck into building */
    model.duck.x = model.buildings[0].x;
    model.duck.y = model.buildings[0].y;

    if (duck_building_collision(&model)) {
        printf("Duck-Building collision detected\n");
    } else {
        printf("Duck-Building collision NOT detected\n");
    }

    /* Force duck to ground */
    model.duck.y = 360;

    if (duck_ground_collision(&model.duck)) {
        printf("Duck-Ground collision detected\n");
    } else {
        printf("Duck-Ground collision NOT detected\n");
    }

    /* Force duck to max height */
    model.duck.y = 50;

    if (duck_max_height(&model.duck)) {
        printf("Duck max height detected\n");
    } else {
        printf("Duck max height NOT detected\n");
    }

    /* Force building off screen */
    model.buildings[0].x = 0;

    if (building_left_border(&model.buildings[0])) {
        printf("Building left screen detected\n");
    } else {
        printf("Building left screen NOT detected\n");
    }

    return 0;
}