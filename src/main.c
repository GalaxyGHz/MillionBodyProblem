#include "main.h"

Star* stars[STAR_COUNT];

args argList[NUMBER_OF_THREADS];
pthread_t threadList[NUMBER_OF_THREADS];

int main(int argc, char** argv) {
    double galaxyR1 = 1.5;
    double galaxyR2 = 0.25;
    int m1 = 100000;
    int m2 = 20000;
    //initStars();
    generateGalaxy(0.0,0.0,0.0,0.0,0,STAR_COUNT,1.0,0.0,0.0,galaxyR1,m1);
    //generateGalaxy(1.0,1.0,0.0,0.0,2*STAR_COUNT/3,STAR_COUNT,-0.5,galaxyR2,m2);
    // Prepare the window
    initScreen(&argc, argv);
    // Start the simulation
    glutMainLoop();
    return 0;
}

void simulation() {
    Cube* cube = createCube(0, 0, 0, 1.5*8.0);
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
        moveStar(stars[i], 0.0005);
    }
    return;
}

void initStars() {
    stars[0] = crateStar(0, 0, 0, 
                         0, 0, 0, 
                         100000);

    for (int i = 1; i < STAR_COUNT; i++)
    {
        double fi = randSpiral();
        double x = randfrom(0, GALAXY1_RADIUS) * sin(fi);
        double y = randfrom(0, GALAXY1_RADIUS) * cos(fi);
        double z = randfrom(0, GALAXY1_RADIUS/10.0);

        stars[i] = crateStar(x, y, z, 
                            0, 0, 0, 
                            randfrom(0.001, 0.02));
        calculateOrbitalVelocity(stars[0], stars[i]);
    }
    return;
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

double randSpiral() {
    return ((double)rand() / (double)RAND_MAX)*2*PI ;
}

double randfrom(double min, double max) {
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}


void generateGalaxy(double x, double y, double z, double angle, int start, int end, double dx,double dy, double dz, double r, int m ) {
    // Reset the stars array
    for (int i = start; i < end; i++) {
        free(stars[i]);
        stars[i] = NULL;
    }

    // Create the central star
    stars[start] = crateStar(x, y, z, dx, dy, dz, m);
    stars[start]->g = 1.0;
    // Generate spiral galaxy stars
    for (int i = start+1; i < end; i++) {
        double fi = angle + i*0.1;


        double ix = x + randfrom(0, r)*sin(fi);
        double iy = y + randfrom(0, r)*cos(fi);
        double iz = z + randfrom(0, r / 10.0);
        stars[i] = crateStar(ix, iy, iz, 0, 0, 0, randfrom(0.001, 0.02));
        stars[i]->g = 0.5;
        calculateOrbitalVelocity(stars[start], stars[i]);
    }
}


