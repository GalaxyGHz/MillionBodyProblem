#include "main.h"
#include <pthread.h>


Star* stars[STAR_COUNT];

args argList[numOfThreads];
pthread_t threadList[numOfThreads];

double randSpiral() {
    return ((double)rand() / (double)RAND_MAX)*2*PI ;
}

double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

void calculateOrbitalVelocity(Star* bh, Star* star) {
    double distance = distanceBetween(bh, star);
    double v = sqrt((bh->mass)*GAMA/distance);

    double r[2];
    r[0] = bh->x - star->x;
    r[1] = bh->y - star->y;

    star->dx = (r[1]/distance)*v;
    star->dy = (-1*r[0]/distance)*v;

    return;
}

void initStars() {
    stars[0] = crateStar(0, 0, 0, 
                         0, 0, 0, 
                         100000);

    for (int i = 1; i < STAR_COUNT; i++)
    {
        double fi = randSpiral();
        double x = randfrom(0, galaxyRadius) * sin(fi);
        double y = randfrom(0, galaxyRadius) * cos(fi);
        double z = randfrom(0, galaxyRadius/10.0);

        stars[i] = crateStar(x, y, z, 
                            0, 0, 0, 
                            randfrom(0.001, 0.02));
        calculateOrbitalVelocity(stars[0], stars[i]);
    }
    return;
}

void threadUpdateAndMoveStar(void* args) {
    for (int i = ((struct args*) args)->start; i < ((struct args*) args)->end; i++)
    {
        resetForces(stars[i]);
        updateForces(( (struct args*) args)->tree, stars[i]);
        moveStar(stars[i], 0.0005);
    }
    return;
}

void simulation() {
    Cube* cube = createCube(0, 0, 0, getHeight()*2);
    BHTree* tree = createBHTree(cube);

    for (int i = 0; i < STAR_COUNT; i++)
    {
        if (isIn(cube, stars[i])) {
            insertStar(tree, stars[i]);
        }
    }
    
    for (int i = 0; i < numOfThreads; i++)
    {
        argList[i].tree = tree;
        argList[i].start = STAR_COUNT/numOfThreads*i;
        argList[i].end = STAR_COUNT/numOfThreads*(i + 1);
        pthread_create(&threadList[i], NULL, threadUpdateAndMoveStar, &argList[i]);

    }
    for (int i = 0; i < numOfThreads; i++)
    {
        pthread_join(threadList[i], NULL);
    }
    
    freeTree(tree);
}


int main(int argc, char** argv) {

    initStars();

    // Prepare the window
    initScreen(&argc, argv);
    // Start the simulation
    glutMainLoop();
    return 0;
}

