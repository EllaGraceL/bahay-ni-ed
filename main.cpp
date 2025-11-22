#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include <stdio.h>
#include "FirstScene.h"
#include "SecondScene.h"
using namespace std;

// first scene variables
const int hillPoints = 400;
const float screenWidth = 800.0f;
const float screenHeight = 600.0f;

// second scene variables

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize((int)screenWidth, (int)screenHeight);
    glutCreateWindow("House on The Hill");

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    initFirst();

    glutDisplayFunc(displayFirst);
    glutKeyboardFunc(keyboardFirst);
    glutSpecialFunc(specialKeys);
    printf("Use WASD to move, Arrow Keys to look around, +/- to zoom.\n");

	glutMainLoop();

    return 0;
}