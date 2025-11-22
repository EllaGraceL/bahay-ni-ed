#define _USE_MATH_DEFINES
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <cmath>
#include "FirstScene.h"
#include "SecondScene.h"
using namespace std;

float cameraX_pos = 0.0f, cameraY_pos = 5.0f, cameraZ_pos = 20.0f;
float cameraX_look = 0.0f, cameraY_look = 0.0f, cameraZ_look = 0.0f;
float angle = 0.0f;

float quakeAmplitude;

void renderSceneSecond(void) {
    const float size = 50.0f;
    const float step = 1.0f;  

    glColor3f(0.3f, 0.8f, 0.3f);

    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-size, 0.0f, -size);
    glVertex3f(-size, 0.0f, size);
    glVertex3f(size, 0.0f, size);
    glVertex3f(size, 0.0f, -size);
    glEnd();

    glColor3f(0.2f, 0.2f, 0.2f);
    

    glBegin(GL_LINES);
    for (float i = -size; i <= size; i += step) {
        glVertex3f(i, 0, -size);
        glVertex3f(i, 0, size);
        glVertex3f(-size, 0, i);
        glVertex3f(size, 0, i);
    }
    glEnd();
}

void displaySecond() {
    glClearColor(0.529f, 0.808f, 0.922f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(cameraX_pos, cameraY_pos, cameraZ_pos,  // camera position
        cameraX_look, cameraY_look, cameraZ_look,  // look at origin
        0.0f, 1.0f, 0.0f); // up vector

    GLfloat lightPos[] = { 10.0f, 10.0f, 10.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	renderSceneSecond();

	glutSwapBuffers();
}

void keyboardSecond(unsigned char key, int x, int y) {
    const float speed = 1.0f;
    switch (key) {
    case '1': // for scene switching
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);

        initFirst();

        glutDisplayFunc(displayFirst);
        glutKeyboardFunc(keyboardFirst);
        glutSpecialFunc(specialKeys);
        printf("Switched to First Scene. Use WASD to move, Arrow Keys to look around, +/- to zoom.\n");
		break;

    case 'w': cameraZ_pos -= speed; cameraZ_look -= speed; break;
    case 's': cameraZ_pos += speed; cameraZ_look += speed; break;
    case 'a': cameraX_pos -= speed; cameraX_look -= speed; break;
    case 'd': cameraX_pos += speed; cameraX_look += speed; break;
    // for earthquake purposes (change to animation and make smoother)
    case 'o': cameraY_look += 0.5f; break;
	case 'p': cameraY_look -= 0.5f; break;
    case 32: quakeAmplitude = 7.5f; glutTimerFunc(0, earthquake, 0); break;
    case 27: exit(0);
    }
    glutPostRedisplay();
}

void specialKeyboardSecond(int key, int x, int y) {
    const float angleStep = 5.0f;
    switch (key) {
    case GLUT_KEY_UP:
        cameraY_look += 1.0f;
        break;
    case GLUT_KEY_DOWN:
        cameraY_look -= 1.0f;
        break;
    case GLUT_KEY_LEFT:
        angle -= angleStep;
        cameraX_look = cameraX_pos + 20.0f * sin(angle * M_PI / 180.0f);
        cameraZ_look = cameraZ_pos - 20.0f * cos(angle * M_PI / 180.0f);
        break;
    case GLUT_KEY_RIGHT:
        angle += angleStep;
        cameraX_look = cameraX_pos + 20.0f * sin(angle * M_PI / 180.0f);
        cameraZ_look = cameraZ_pos - 20.0f * cos(angle * M_PI / 180.0f);
        break;
    }
    glutPostRedisplay();
}

void earthquake(int) {
    cameraY_look += quakeAmplitude;
	quakeAmplitude = -quakeAmplitude * 0.95f;
    
	glutPostRedisplay();

    if (abs(quakeAmplitude) <= 0.05f) {
        quakeAmplitude = 0.00f;
        return;
    }

	glutTimerFunc(100, earthquake, 0);
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, aspect, 1.0f, 200.0f);

    glMatrixMode(GL_MODELVIEW);
}
