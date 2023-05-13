#ifndef IFcube
#define IFcube
#include "main.h"

typedef struct Cube {
    double x;
    double y;
    double z;
    double size;
} Cube;

Cube* createCube(double x, double y, double z, double size);
double getSize(Cube* cube);
bool isInsideSpace(Cube* cube, double x, double y, double z);
Cube* subCube1(Cube* cube);
Cube* subCube2(Cube* cube);
Cube* subCube3(Cube* cube);
Cube* subCube4(Cube* cube);
Cube* subCube5(Cube* cube);
Cube* subCube6(Cube* cube);
Cube* subCube7(Cube* cube);
Cube* subCube8(Cube* cube);

#endif
