/*
 * game.h
 *
 *  Created on: May 2, 2018
 *      Author: Sibt ul Hussain & parkerqueen
 */

#ifndef AsteroidS_CPP_
#define AsteroidS_CPP_

#include "Board.h"

using namespace std;

// seed the random numbers generator by current time (see the documentation of
// srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right
 * coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1,
            1);  // set the screen size to given width and height.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*
 * Main Canvas drawing function.
 * */

Board* b;
void GameDisplay() /**/ {
    // set the background color using function glClearColor.
    // to change the background play with the red, green and blue values below.
    // Note that r, g and b values must be in the range [0,1] where 0 means dim
    // rid and 1 means pure red and so on.

    glClearColor(
        0 /*Red Component*/, 0,  // 148.0/255/*Green Component*/,
        0.0 /*Blue Component*/,
        0 /*Alpha component*/);    // Red==Green==Blue==1 --> White Colour
    glClear(GL_COLOR_BUFFER_BIT);  // Update the colors
    Mix_VolumeMusic(75);
    if (Mix_PlayingMusic() == 0) Mix_PlayMusic(music, -1);
    b->collider();
    b->run();
    glutSwapBuffers();  // do not modify this line..
}

/*This function is called (automatically) whenever any non-printable key (such
 * as up-arrow, down-arraw) is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed
 * or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key
 * pressed, while x and y tells the program coordinates of mouse pointer when
 * key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT)
        b->rotate(SPINL);
    else if (key == GLUT_KEY_RIGHT)
        b->rotate(SPINR);
    else if (key == GLUT_KEY_UP)
        b->fuelShip(true);
}

void KeyUp(int key, int x, int y) {
    if (key == GLUT_KEY_UP) b->fuelShip(false);
    if (key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT) b->rotate(SPNULL);
}

/*This function is called (automatically) whenever any printable key (such as
 * x,b, enter, etc.) is pressed from the keyboard This function has three
 * argument variable key contains the ASCII of the key pressed, while x and y
 * tells the program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
    if (key == 32)
        b->shoot();
    else if (key == 13)
        b->start();
    else if (key == 'b')
        b->hyperdrive();
    else if (key == 27) {
        closemedia();
        delete b;
        exit(1);
    }
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {
    // implement your functionality here
    b->timer(25);
    glutPostRedisplay();
    // once again we tell the library to call our Timer function after next
    // 1000/FPS
    glutTimerFunc(25.0, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside
 * the game window
 *
 * You will have to add the necessary code here for finding the direction of
 * shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current
 * position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {}

void MouseMoved(int x, int y) {}

/*This function is called (automatically) whenever your mouse button is clicked
 * witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state
 * (button is pressed or released), x & y that tells the coordinate of current
 * position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {}

/*
 * our gateway main function
 * */
int main(int argc, char* argv[]) {
    loadmedia();                     // Load the sound assets
    InitRandomizer();                // seed the random number generator...
    b = new Board(BWIDTH, BHEIGHT);  // create a new board object to use in the
                                     // Display Function ...
    glutInit(&argc, argv);           // initialize the graphics library...
    glutInitDisplayMode(GLUT_DOUBLE |
                        GLUT_RGBA);  // we will be using color display mode
    glutInitWindowPosition(50, 50);  // set the initial position of our window
    glutInitWindowSize(BWIDTH, BHEIGHT);  // set the size of our window
    glutCreateWindow("Asteroids");        // set the title of our game window
    SetCanvasSize(BWIDTH, BHEIGHT);       // set the number of pixels...

    // Register your functions to the library,
    // you are telling the library names of function to call for different
    // tasks.
    // glutDisplayFunc(display); // tell library which function to call for
    // drawing Canvas.

    glutDisplayFunc(GameDisplay);  // tell library which function to call for
                                   // drawing Canvas.
    glutSpecialFunc(NonPrintableKeys);  // tell library which function to call
                                        // for non-printable ASCII characters
    glutSpecialUpFunc(KeyUp);
    glutKeyboardFunc(PrintableKeys);  // tell library which function to call for
                                      // printable ASCII characters
    // This function tells the library to call our Timer function after
    // 1000.0/FPS milliseconds...
    glutTimerFunc(25.0, Timer, 0);

    glutMouseFunc(MouseClicked);
    glutPassiveMotionFunc(MouseMoved);     // Mouse
    glutMotionFunc(MousePressedAndMoved);  // Mouse

    // now handle the control to library and it will call our registered
    // functions when it deems necessary...
    glutMainLoop();
    return 1;
}
#endif /* AsteroidS_CPP_ */
