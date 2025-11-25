#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include "FirstScene.h"
using namespace std; 

// first scene variables
const int hillPoints = 400;
const float screenWidth = 800.0f;
const float screenHeight = 600.0f;

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

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        cerr << "Error initializing GLEW: " << glewGetErrorString(err) << endl;
        return -1;
    }

    glutMainLoop();

    return 0;
}
