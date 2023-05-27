#include "main.h"

Star* stars[STAR_COUNT];

args argList[NUMBER_OF_THREADS];
pthread_t threadList[NUMBER_OF_THREADS];

int main(int argc, char** argv) {
    // Prepare the stars
    initStars();
    // Prepare the window
    initScreen(&argc, argv);
    // Start the simulation
    glutMainLoop();
    return 0;
}

void simulation() {
    Cube* cube = createCube(0, 0, 0, 1.5*20.0);
    BHTree* tree = createBHTree(cube);

    for (int i = 0; i < STAR_COUNT; i++)
    {
        if (isIn(cube, stars[i])) {
            insertStar(tree, stars[i]);
        }
    }
    
    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        argList[i].tree = tree;
        argList[i].start = STAR_COUNT/NUMBER_OF_THREADS*i;
        argList[i].end = STAR_COUNT/NUMBER_OF_THREADS*(i + 1);
        pthread_create(&threadList[i], NULL, threadUpdateAndMoveStar, &argList[i]);

    }
    for (int i = 0; i < NUMBER_OF_THREADS; i++)
    {
        pthread_join(threadList[i], NULL);
    }
    
    freeTree(tree);
}

void threadUpdateAndMoveStar(void* args) {
    for (int i = ((struct args*) args)->start; i < ((struct args*) args)->end; i++)
    {
        resetForces(stars[i]);
        updateForces(( (struct args*) args)->tree, stars[i]);
        moveStar(stars[i], 0.005);
    }
    return;
}

void initStars() {
     // TEST MALA OKOL VELIKE
    /*
    double galaxyR1 = 1.0;
    double galaxyR2 = 0.5;
    int m1 = 100000;
    int m2 = 50000;
    generateGalaxy(-1.0, -1.0, 0.0, 0.0, 0, 4*STAR_COUNT/5, 0.0, 0.0, 0.0, galaxyR1, m1, 1);
    generateGalaxy(0.0, 0.0, 0.0, PI/4, 4*STAR_COUNT/5 ,STAR_COUNT, 0.0, 0.0, 0.0, galaxyR2, m2, 1);
    calculateOrbitalVelocity(stars[0], stars[4*STAR_COUNT/5], 1, 0.0);
    */
    //TEST DVE ENAKI
    double galaxyR1 = 1.0;
    double galaxyR2 = 1.0;
    int m1 = 100000;
    generateGalaxy(-1.0, -1.0, 0.0, PI/4, 0, STAR_COUNT/2, 0.0, 0.0, 0.0, galaxyR1, m1, 1);
    generateGalaxy(1.0, 1.0, 0.0, 0.0, STAR_COUNT/2, STAR_COUNT, 0.0, 0.0, 0.0, galaxyR2, m1, -1);
    return;
}


void calculateOrbitalVelocity(Star* bh, Star* star, int rotation,double angle) {
    double distance = distanceBetween(bh, star);
    double v = sqrt((bh->mass)*G/distance);
    double r[3];
    r[0] = bh->x-star->x;
    r[1] = bh->y-star->y;
    r[2] = bh->z-star->z;

    star->dx = (rotation*(cos(angle)*r[1]+sin(angle)*r[2]) / distance) * v;
    star->dy = (-rotation*(r[0]*cos(angle)) / distance) * v;
    star->dz = (-rotation*(r[0]*sin(angle)) / distance) * v;
    return;
}

double randSpiral() {
    return ((double)rand() / (double)RAND_MAX)*2*PI ;
}

double randfrom(double min, double max) {
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

void generateGalaxy(double x, double y, double z, double angle, int start, int end, double dx,double dy, double dz, double r, int m, int rotation) {
    // Create the center
    stars[start] = crateStar(x, y, z, dx, dy, dz, m);
    stars[start]->g = 1.0;
    // Generate spiral galaxy stars
    for (int i = start+1; i < end; i++) {
        double fi = randSpiral();

	//calculating random coordinates
        double ix = randfrom(0, r)*sin(fi);
        double iy = randfrom(0, r)*cos(fi);
        double iz = randfrom(0, r / 10.0);
        //rotating coordinates
        double tx = ix+x;
        double ty = iy*cos(angle)-iz*sin(angle)+y;
        double tz = iz*cos(angle)+iy*sin(angle)+z;
        stars[i] = crateStar(tx, ty, tz, 0, 0, 0, randfrom(0.01, 0.1));
        stars[i]->g = 0.5;
        calculateOrbitalVelocity(stars[start], stars[i], rotation, angle);
    }
    return;
}


