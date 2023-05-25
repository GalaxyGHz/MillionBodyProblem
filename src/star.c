#include "main.h"

// Create a new point like star with these parameters
Star* crateStar(double x, double y, double z, double dx, double dy, double dz, double mass) {
    Star* star = malloc(sizeof(Star));

    star->x = x;
    star->y = y;
    star->z = z;
    star->dx = dx;
    star->dy = dy;
    star->dz = dz;
    star->mass = mass;

    star->fx = 0;
    star->fy = 0;
    star->fz = 0;
    star->r = 0;
    star->g = 0;
    star->b = 0;


    return star;
}

// Move the star to its next position with respect to the forces acting upon it
void moveStar(Star* star, double dt) {
    star->dx += dt*(star->fx)/(star->mass);
    star->dy += dt*(star->fy)/(star->mass);
    star->dz += dt*(star->fz)/(star->mass);
    star->x += dt*(star->dx);
    star->y += dt*(star->dy);
    star->z += dt*(star->dz);
    
    double speed = sqrt(star->dx * star->dx + star->dy * star->dy + star->dz * star->dz);
    star->r = 0.15*speed;  // Example: Set red component based on speed
    star->b = 1.0-0.15*speed;   // Example: Set blue component to a constant value
    
    return;
}

// Calculate the distance between two stars
double distanceBetween(Star* StarA, Star* StarB) {
    double distanceX = (StarA->x) - (StarB->x);
    double distanceY = (StarA->y) - (StarB->y);
    double distanceZ = (StarA->z) - (StarB->z);
    return sqrt(distanceX*distanceX + distanceY*distanceY + distanceZ*distanceZ);
}

// Reset the forces acting upon a star
void resetForces(Star* star) {
    star->fx = 0;
    star->fy = 0;
    star->fz = 0;
    return;
}

// Add the forces acting on starA due to starB
void addForces(Star* starA, Star* starB) {
    double EPS=0.1;
    double dd = distanceBetween(starA, starB);

    double force = (G*(starA->mass)*(starB->mass))/(dd*dd*dd+EPS*EPS*EPS);

    starA->fx += force*((starB->x) - (starA->x));
    starA->fy += force*((starB->y) - (starA->y));
    starA->fz += force*((starB->z) - (starA->z));
    return;
}

// Save the mass and center of mass of the system into starA. StarA is a pseudostar that represents the sum of masses of all of the 
// stars in that cube of the Bernes-Hut tree
void calculateMassAndCenterOfMass(Star* starA, Star* starB) {
    double massSum = (starA->mass) + (starB->mass);

    starA->x = ((starA->x)*(starA->mass) + (starB->x)*(starB->mass)) / massSum;
    starA->y = ((starA->y)*(starA->mass) + (starB->y)*(starB->mass)) / massSum;
    starA->z = ((starA->z)*(starA->mass) + (starB->z)*(starB->mass)) / massSum;

    starA->mass = massSum;
    return;
}

bool isIn(Cube* cube, Star* star) {
    return isInsideSpace(cube, star->x, star->y, star->z);
}

bool equals(Star* starA, Star* starB) {
    return (((starA->x) == (starB->x)) && 
           ((starA->y) == (starB->y)) && 
           ((starA->z) == (starB->z)) && 
           ((starA->mass) == (starB->mass)) &&
           ((starA->dx) == (starB->dx)) &&
           ((starA->dy) == (starB->dy)) &&
           ((starA->dz) == (starB->dz)));
}
