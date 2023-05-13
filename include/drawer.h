#ifndef IFdrawer
#define IFdrawer

#include "main.h"

#define WINDOW_POSITION_X 2220
#define WINDOW_POSITION_Y 200

#define WINDOW_START_WIDTH 900
#define WINDOW_START_HEIGHT 900


void drawStars(void);

void initScreen(int*, char**);
void renderScreen(void);
void changeSize(int, int);

void processMouse(int button, int state, int x, int y);
void moveMeAlongCamera(int direction);
void keyboardRotationFunction(unsigned char, int, int);
void exitFunction(unsigned char, int, int);

void printFPS(void);
void calculateFPS(void);

void renderBitmapString(int, int, void*, char*);
int getWidth(void);
int getHeight(void);

#endif