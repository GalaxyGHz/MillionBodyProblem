#ifndef IFstar
#define IFstar
#include "main.h"

typedef struct Star {
    double x, y, z;  //Position
    double dx, dy, dz;  //Speed
    double fx, fy, fz;  //Force
    double mass;  //Mass
    double r, g, b;

} Star;

Star* crateStar(double x, double y, double z, double dx, double dy, double dz, double mass);
void moveStar(Star* star, double dt);
double distanceBetween(Star* StarA, Star* StarB);
void addForces(Star* starA, Star* starB);
void calculateMassAndCenterOfMass(Star* starA, Star* starB);
bool isIn(Cube* cube, Star* star);
bool equals(Star* starA, Star* starB);

#endif
