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
     //TEST 1 VELIKA
     /*
     double r = 2.0;
     int m = 1000000;
     generateGalaxy(0.0, 0.0, 0.0, 0.0, 0, STAR_COUNT, 0.0, 0.0, 0.0, r, m, 1, 'b');
     */
     //TEST DVE POD KOTOM
     /*
     double galaxyR1 = 1.0;
     double galaxyR2 = 1.0;
     int m = 100000;
     generateGalaxy(-1.5, 0.0, 0.0, PI/4, 0, STAR_COUNT/2, 0.0, 0.0, 0.0, galaxyR1, m, 1, 'g');
     generateGalaxy(1.5, 0.0, 0.0, -PI/4, STAR_COUNT/2, STAR_COUNT, 0.0, 0.0, 0.0, galaxyR2, m, -1, 'r');
    */
     //TEST DVE ENAKI KI SE VERTITA V RAZLIČNE SMERI  
     /*
     double galaxyR1 = 1.0;
     double galaxyR2 = 1.0;
     int m1 = 100000;
     generateGalaxy(-1.0, -1.0, 0.0, 0.0, 0, STAR_COUNT/2, 0.0, 0.0, 0.0, galaxyR1, m1, 1, 'b');
     generateGalaxy(1.0, 1.0, 0.0, 0.0, STAR_COUNT/2, STAR_COUNT, 0.0, 0.0, 0.0, galaxyR2, m1, -1, 'r');
     */
     // TEST MALA PADE V VELIKO
     /*
    double galaxyR1 = 1.5;
    double galaxyR2 = 0.5;
    int m1 = 100000;
    int m2 = 3000;
    generateGalaxy(0.0, 0.0, 0.0, -PI/4, 0, 4*STAR_COUNT/5, 0.0, 0.0, 0.0, galaxyR1, m1, 1,'b');
    generateGalaxy(1.5, 1.5, 0.0, 0.0, 4*STAR_COUNT/5 ,STAR_COUNT, 0.0, 0.0, 0.0, galaxyR2, m2, 1, 'r');
    */
     // TEST MALA OKOLI VELIKE
     
    double galaxyR1 = 1.0;
    double galaxyR2 = 0.5;
    int m1 = 100000;
    int m2 = 3000;
    Star* bh1 = crateStar(-1.0, -1.0, 0.0, 0.0, 0.0, 0.0, m1);
    Star* bh2 = crateStar(1.0, 1.0, 0.0, 0.0, 0.0, 0.0, m2);
    calculateOrbitalVelocity(bh1, bh2, 1, 0.0);
    bh2->dx *= 0.6;
    bh2->dy *= 0.6;
    bh2->dz *= 0.6;
    generateGalaxy(-1.0, -1.0, 0.0, 0.0, 0, 4*STAR_COUNT/5, 0.0, 0.0, 0.0, galaxyR1, m1, 1,'r');
    generateGalaxy(1.0, 1.0, 0.0, PI/4, 4*STAR_COUNT/5 ,STAR_COUNT, bh2->dx, bh2->dy, bh2->dz, galaxyR2, m2, 1, 'g');
    
    
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

void generateGalaxy(double x, double y, double z, double angle, int start, int end, double dx,double dy, double dz, double r, int m, int rotation, char color) {
    // Create the center
    stars[start] = crateStar(x, y, z, dx, dy, dz, m);
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
        stars[i] = crateStar(tx, ty, tz, 0.0, 0.0, 0.0, randfrom(0.01, 0.1));
        calculateOrbitalVelocity(stars[start], stars[i], rotation, angle);
        double distance = distanceBetween(stars[start], stars[i]);
        if(color=='r'){
            stars[i]->r=1.0;
            stars[i]->b=(distance/r)-0.25;
            stars[i]->g=(distance/r)-0.25;
        }
        if(color=='g'){
            stars[i]->r=(distance/r)-0.25;
            stars[i]->g=1.0;
            stars[i]->b=(distance/r)-0.25;
        }
        if(color=='b'){
            stars[i]->r=(distance/r)-0.25;
            stars[i]->g=(distance/r)-0.25;
            stars[i]->b=1.0;
        }
        stars[i]->dx += stars[start]->dx;
        stars[i]->dy += stars[start]->dy;
        stars[i]->dz += stars[start]->dz;
    }
    return;
}


