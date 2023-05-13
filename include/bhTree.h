#ifndef IFbhtree
#define IFbhtree
#include "main.h"

typedef struct BHTree {
    
    Star* colectiveMassAndPosition;
    Cube* cube;
    struct BHTree* subTree1;
    struct BHTree* subTree2;
    struct BHTree* subTree3;
    struct BHTree* subTree4;
    struct BHTree* subTree5;
    struct BHTree* subTree6;
    struct BHTree* subTree7;
    struct BHTree* subTree8;

} BHTree;

BHTree* createBHTree(Cube* cube);
bool isExternalNode(BHTree* tree);
void putStar(BHTree* tree, Star* star);
void insertStar(BHTree* tree, Star* star);
void updateForces(BHTree* tree, Star* star);
void freeTree(BHTree* tree);


#endif