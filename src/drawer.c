#include "main.h"

/* YOU CAN MOVE THE ANGLE OF VIEWING THE CENTER OF THE UNIVERSE BY USING THE
ARROW KEYS ON YOUR KEYBOARD AND YOU CAN MOVE THE CAMERA FORWARDS OR BAKCWARDS*
BY USING THE MOUSEWHEEL */

extern Star* stars[];

// Needed for FPS
int frame = 0, relativeTime = 0, timebase = 0, fps = 0;
int angleX = 0;
int angleY = 0;

// Needed for movement along camera axis
static float x = 0.0f, y = 0.0f, z = 5.0f;
static float lx = 0.0f, ly = 0.0f, lz = -1.0f;
float ratio = 0;


void drawStars() {
    glBegin(GL_POINTS);
    for (int i = 0; i < STAR_COUNT; i++)
    {
        glColor3f(stars[i]->r, stars[i]->g, stars[i]->b);
        glVertex3f(stars[i]->x, stars[i]->y, stars[i]->z);
    }
    glEnd();
    return;
}

void initScreen(int* argc, char** argv) {
    glutInit(argc, argv);
    glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
    glutInitWindowSize(WINDOW_START_WIDTH, WINDOW_START_HEIGHT);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Simulating a galaxy!");
    glutDisplayFunc(renderScreen);
    // Changes perspective if window size changes
    glutReshapeFunc(changeSize);
    // Check keyboard for rotation
    glutSpecialFunc(keyboardRotationFunction);
    // Mouse function
    glutMouseFunc(processMouse);
    // Check for exit
    glutKeyboardFunc(exitFunction);
    // Here is the setting of the idle function
    glutIdleFunc(renderScreen);
    // Enable depth testing
	glEnable(GL_DEPTH_TEST);
    return;
}

void renderScreen(void) {
    calculateFPS();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleY, 0.0, 1.0, 0.0);
    // Draw after this
    printFPS();

    simulation();
    drawStars();

    // Finish drawing
    glPopMatrix();
    glutSwapBuffers();
	glFlush();
}

void changeSize(int w, int h) {
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0) h = 1;

	ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 
		      x + lx, y + ly, z + lz,
			  0.0f, 1.0f, 0.0f);
			  
	//moveMeAlongCamera(-10);
    return;
}

void processMouse(int button, int state, int x, int y) {
    if (button == 3) {
        moveMeAlongCamera(1);
    }else if (button == 4) {
        moveMeAlongCamera(-1);
    }
    return;
}

void keyboardRotationFunction(unsigned char key, int x, int y) {
    switch(key)
    {
        case GLUT_KEY_UP:
            angleX += 5;
        break;
        case GLUT_KEY_DOWN:
            angleX -= 5;
        break;
        case GLUT_KEY_LEFT:
            angleY += 5;
        break;
        case GLUT_KEY_RIGHT:
            angleY -= 5;
        break;
    }

    return;
}

void moveMeAlongCamera(int direction) {
	x = x + direction*(lx)*0.1;
	z = z + direction*(lz)*0.1;
	glLoadIdentity();
	gluLookAt(x, y, z, 
		      x + lx,y + ly,z + lz,
			  0.0f, 1.0f, 0.0f);
}

void renderBitmapString(int x, int y, void *font, char *string) {  
    char *c;
    glWindowPos2i(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
    return;
}

void calculateFPS() {
    frame++;
	relativeTime = glutGet(GLUT_ELAPSED_TIME);
	if (relativeTime - timebase > 1000) {
		fps = frame*1000.0/(relativeTime - timebase);
		timebase = relativeTime;		
		frame = 0;
	}
    return;
}

void printFPS() {
    char fpsMsg[128];
    sprintf(fpsMsg, "FPS: %d", fps);
    glColor3f(1.0, 1.0, 1.0);
    renderBitmapString(getWidth() - 60, getHeight(), GLUT_BITMAP_8_BY_13, fpsMsg);
    return;
}


void exitFunction (unsigned char key, int x, int y) {
    if (key == 27) 
            exit(0);
    return;
}

int getWidth() {
    return glutGet(GLUT_WINDOW_WIDTH);
}

int getHeight() {
    return glutGet(GLUT_WINDOW_HEIGHT) - 15;
}
