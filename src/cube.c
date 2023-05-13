#include "main.h"

Cube* createCube(double x, double y, double z, double size) {
    Cube* cube = malloc(sizeof(Cube));

    cube->x = x;
    cube->y = y;
    cube->z = z;
    cube->size = size;
    return cube;
}

double getSize(Cube* cube) {
    return cube->size;
}

bool isInsideSpace(Cube* cube, double x, double y, double z) {
    double sizeDiv2 = (cube->size)/2.0;
    double cx = cube->x;
    double cy = cube->y;
    double cz = cube->z;
    bool xCordinate = (x <= (cx + sizeDiv2)) && (x > cx - sizeDiv2);
    bool yCordinate = (y <= (cy + sizeDiv2)) && (y > cy - sizeDiv2);
    bool zCordinate = (z <= (cz + sizeDiv2)) && (z > cz - sizeDiv2);
    return xCordinate && yCordinate && zCordinate;
}

Cube* subCube1(Cube* cube) {
    double newX = (cube->x) + (cube->size)/4.0;
    double newY = (cube->y) + (cube->size)/4.0;
    double newZ = (cube->z) + (cube->size)/4.0;
    double newSize = (cube->size)/2.0;
    return createCube(newX, newY, newZ, newSize);
}
Cube* subCube2(Cube* cube) {
    double newX = (cube->x) + (cube->size)/4.0;
    double newY = (cube->y) + (cube->size)/4.0;
    double newZ = (cube->z) - (cube->size)/4.0;
    double newSize = (cube->size)/2.0;
    return createCube(newX, newY, newZ, newSize);
}
Cube* subCube3(Cube* cube) {
    double newX = (cube->x) + (cube->size)/4.0;
    double newY = (cube->y) - (cube->size)/4.0;
    double newZ = (cube->z) + (cube->size)/4.0;
    double newSize = (cube->size)/2.0;
    return createCube(newX, newY, newZ, newSize);
}
Cube* subCube4(Cube* cube) {
    double newX = (cube->x) + (cube->size)/4.0;
    double newY = (cube->y) - (cube->size)/4.0;
    double newZ = (cube->z) - (cube->size)/4.0;
    double newSize = (cube->size)/2.0;
    return createCube(newX, newY, newZ, newSize);
}
Cube* subCube5(Cube* cube) {
    double newX = (cube->x) - (cube->size)/4.0;
    double newY = (cube->y) + (cube->size)/4.0;
    double newZ = (cube->z) + (cube->size)/4.0;
    double newSize = (cube->size)/2.0;
    return createCube(newX, newY, newZ, newSize);
}
Cube* subCube6(Cube* cube) {
    double newX = (cube->x) - (cube->size)/4.0;
    double newY = (cube->y) + (cube->size)/4.0;
    double newZ = (cube->z) - (cube->size)/4.0;
    double newSize = (cube->size)/2.0;
    return createCube(newX, newY, newZ, newSize);
}
Cube* subCube7(Cube* cube) {
    double newX = (cube->x) - (cube->size)/4.0;
    double newY = (cube->y) - (cube->size)/4.0;
    double newZ = (cube->z) + (cube->size)/4.0;
    double newSize = (cube->size)/2.0;
    return createCube(newX, newY, newZ, newSize);
}
Cube* subCube8(Cube* cube) {
    double newX = (cube->x) - (cube->size)/4.0;
    double newY = (cube->y) - (cube->size)/4.0;
    double newZ = (cube->z) - (cube->size)/4.0;
    double newSize = (cube->size)/2.0;
    return createCube(newX, newY, newZ, newSize);
}