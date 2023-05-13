#include "main.h"

BHTree* createBHTree(Cube* cube) {
    BHTree* tree = malloc(sizeof(BHTree));

    tree->cube = cube;
    tree->colectiveMassAndPosition = NULL;
    tree->subTree1 = NULL;
    tree->subTree2 = NULL;
    tree->subTree3 = NULL;
    tree->subTree4 = NULL;
    tree->subTree5 = NULL;
    tree->subTree6 = NULL;
    tree->subTree7 = NULL;
    tree->subTree8 = NULL;
    return tree;
}

bool isExternalNode(BHTree* tree) {
    return (tree->subTree1 == NULL &&
            tree->subTree2 == NULL &&
            tree->subTree3 == NULL &&
            tree->subTree4 == NULL &&
            tree->subTree5 == NULL &&
            tree->subTree6 == NULL &&
            tree->subTree7 == NULL &&
            tree->subTree8 == NULL);
}

void putStar(BHTree* tree, Star* star) {
    if (isIn(tree->subTree1->cube, star)) {
        insertStar(tree->subTree1, star);
    }else if (isIn(tree->subTree2->cube, star)) {
        insertStar(tree->subTree2, star);
    }else if (isIn(tree->subTree3->cube, star)) {
        insertStar(tree->subTree3, star);
    }else if (isIn(tree->subTree4->cube, star)) {
        insertStar(tree->subTree4, star);
    }else if (isIn(tree->subTree5->cube, star)) {
        insertStar(tree->subTree5, star);
    }else if (isIn(tree->subTree6->cube, star)) {
        insertStar(tree->subTree6, star);
    }else if (isIn(tree->subTree7->cube, star)) {
        insertStar(tree->subTree7, star);
    }else if (isIn(tree->subTree8->cube, star)) {
        insertStar(tree->subTree8, star);
    }
    return;
}

void insertStar(BHTree* tree, Star* star) {
    if (tree->colectiveMassAndPosition == NULL) {
        tree->colectiveMassAndPosition = crateStar(star->x, star->y, star->z, star->dx, star->dy, star->dz, star->mass);
    }else if (!(isExternalNode(tree))) {
        calculateMassAndCenterOfMass(tree->colectiveMassAndPosition, star);
        putStar(tree, star);
    }else {
        tree->subTree1 = createBHTree(subCube1(tree->cube));
        tree->subTree2 = createBHTree(subCube2(tree->cube));
        tree->subTree3 = createBHTree(subCube3(tree->cube));
        tree->subTree4 = createBHTree(subCube4(tree->cube));
        tree->subTree5 = createBHTree(subCube5(tree->cube));
        tree->subTree6 = createBHTree(subCube6(tree->cube));
        tree->subTree7 = createBHTree(subCube7(tree->cube));
        tree->subTree8 = createBHTree(subCube8(tree->cube));
        putStar(tree, tree->colectiveMassAndPosition);
        putStar(tree, star);

        calculateMassAndCenterOfMass(tree->colectiveMassAndPosition, star);        
    }
    return;
}

void updateForces(BHTree* tree, Star* star) {
    if (((tree->colectiveMassAndPosition) == NULL) || equals(tree->colectiveMassAndPosition, star)) return;

    if (isExternalNode(tree)) {
        addForces(star, tree->colectiveMassAndPosition);
    }else {
        double s = getSize(tree->cube);

        double d = distanceBetween(tree->colectiveMassAndPosition, star);

        if ((s / d) < THETA) {
            addForces(star, tree->colectiveMassAndPosition);
        }else {
            updateForces(tree->subTree1, star);
            updateForces(tree->subTree2, star);
            updateForces(tree->subTree3, star);
            updateForces(tree->subTree4, star);
            updateForces(tree->subTree5, star);
            updateForces(tree->subTree6, star);
            updateForces(tree->subTree7, star);
            updateForces(tree->subTree8, star);
        }
    }
    return;
}

void freeTree(BHTree* tree) {
    if (tree == NULL) return;

    if (tree->cube != NULL) free(tree->cube); 
    if (tree->colectiveMassAndPosition != NULL) free(tree->colectiveMassAndPosition);
    if (tree->subTree1 != NULL) freeTree(tree->subTree1);
    if (tree->subTree2 != NULL) freeTree(tree->subTree2);
    if (tree->subTree3 != NULL) freeTree(tree->subTree3);
    if (tree->subTree4 != NULL) freeTree(tree->subTree4);
    if (tree->subTree5 != NULL) freeTree(tree->subTree5);
    if (tree->subTree6 != NULL) freeTree(tree->subTree6);
    if (tree->subTree7 != NULL) freeTree(tree->subTree7);
    if (tree->subTree8 != NULL) freeTree(tree->subTree8);
    free(tree);
    return;
}