#ifndef IFmain
#define IFmain

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <GL/glut.h>
#include "cube.h"
#include "star.h"
#include "bhTree.h"
#include "drawer.h"

#define numOfThreads 16

#define PI 3.14159265359

#define THETA 0.5
#define GAMA 0.0001
//double G = 6.67e-11;
#define G 0.0001

#define STAR_COUNT 10000     
#define galaxyRadius 0.9

void simulation(void);

typedef struct args {
    BHTree* tree;
    int start;
    int end;

} args;

#endif

