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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    glutDisplayFunc(displaySecond);
    glutKeyboardFunc(keyboardSecond);
    glutSpecialFunc(specialKeyboardSecond);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, earthquake, 0);

	glEnable(GL_DEPTH_TEST);

    printf("Hit 'SpaceBar' to Play Animation");

	glutMainLoop();

    return 0;
}