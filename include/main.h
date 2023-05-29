#ifndef IFmain
#define IFmain

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>
#include <GL/glut.h>
#include "cube.h"
#include "star.h"
#include "bhTree.h"
#include "drawer.h"

// Change this to suit your pc
#define NUMBER_OF_THREADS 8

#define PI 3.14159265359

// This constant shouldnt be changed, its part of the algorithm
#define THETA 0.5

#define G 0.0001

#define STAR_COUNT 10000

// If you wish to draw the barnes hut tree building animations, uncommment this
// #define DRAW_BARNES_HUT_CUBE_ANIMATIONS

void initStars();
void simulation(void);
void calculateOrbitalVelocity(Star* bh, Star* star, int rotation,double angle);
void threadUpdateAndMoveStar(void* args);
double randSpiral(void);
double randfrom(double min, double max);

typedef struct args {
    BHTree* tree;
    int start;
    int end;

} args;

#endif

