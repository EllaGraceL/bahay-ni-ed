#define _USE_MATH_DEFINES
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include "FirstScene.h"
#include "SecondScene.h"
#include "../source/repos/TEST/TEST.h"
using namespace std;

// camera related variables
float cameraX_pos = 0.0f, cameraY_pos = 5.0f, cameraZ_pos = 20.0f;
float angle = 0.0f;

// earthquake variables
float quakeAmplitude;
float quakeOffset = 0.0f;

// mouse related variables
bool mouseDragging = false;
int lastMouseX, lastMouseY;

float yaw = 0.0f;
float pitch = 0.0f;

void drawBackWallWindow()
{
    float wallZ = -6.0f;

    float epsilon = 1.0f; // small offset to avoid clipping
    float winZ = wallZ + epsilon;

    // Window size
    float winWidth = 3.0f;
    float winHeight = 3.0f;

    // Window position (centered)
    float cx = 0.0f;
    float cy = 0.0f;

    // Window frame thickness
    float frame = 0.2f;

    // Draw window frame - grey
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    // Left frame
    glVertex3f(cx - winWidth / 2 - frame, cy - winHeight / 2 - frame, wallZ);
    glVertex3f(cx - winWidth / 2, cy - winHeight / 2 - frame, wallZ);
    glVertex3f(cx - winWidth / 2, cy + winHeight / 2 + frame, wallZ);
    glVertex3f(cx - winWidth / 2 - frame, cy + winHeight / 2 + frame, wallZ);

    // Right frame
    glVertex3f(cx + winWidth / 2, cy - winHeight / 2 - frame, wallZ);
    glVertex3f(cx + winWidth / 2 + frame, cy - winHeight / 2 - frame, wallZ);
    glVertex3f(cx + winWidth / 2 + frame, cy + winHeight / 2 + frame, wallZ);
    glVertex3f(cx + winWidth / 2, cy + winHeight / 2 + frame, wallZ);

    // Top frame
    glVertex3f(cx - winWidth / 2 - frame, cy + winHeight / 2, wallZ);
    glVertex3f(cx + winWidth / 2 + frame, cy + winHeight / 2, wallZ);
    glVertex3f(cx + winWidth / 2 + frame, cy + winHeight / 2 + frame, wallZ);
    glVertex3f(cx - winWidth / 2 - frame, cy + winHeight / 2 + frame, wallZ);

    // Bottom frame
    glVertex3f(cx - winWidth / 2 - frame, cy - winHeight / 2 - frame, wallZ);
    glVertex3f(cx + winWidth / 2 + frame, cy - winHeight / 2 - frame, wallZ);
    glVertex3f(cx + winWidth / 2 + frame, cy - winHeight / 2, wallZ);
    glVertex3f(cx - winWidth / 2 - frame, cy - winHeight / 2, wallZ);
    glEnd();

    // Draw window glass - light blue
    glColor3f(0.6f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(cx - winWidth / 2, cy - winHeight / 2, wallZ);
    glVertex3f(cx + winWidth / 2, cy - winHeight / 2, wallZ);
    glVertex3f(cx + winWidth / 2, cy + winHeight / 2, wallZ);
    glVertex3f(cx - winWidth / 2, cy + winHeight / 2, wallZ);
    glEnd();
}

void drawRightWallWindow()
{
    // Right wall is at x = +6, width = 6 (z: -6 → +6), height = 6 (y: -3 → +3)
    float wallX = 6.0f;
    float epsilon = 0.05f; // offset to avoid clipping
    float winX = wallX - epsilon; // slightly inside the room (toward center)

    // Window size
    float winWidth = 3.0f;
    float winHeight = 3.0f;

    // Window position (centered vertically, along z-axis)
    float cz = 0.0f;
    float cy = 0.0f;

    // Window frame thickness
    float frame = 0.2f;

    // Draw window frame - grey
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    // Left frame (toward inside)
    glVertex3f(winX, cy - winHeight / 2 - frame, cz - winWidth / 2 - frame);
    glVertex3f(winX, cy - winHeight / 2 - frame, cz - winWidth / 2);
    glVertex3f(winX, cy + winHeight / 2 + frame, cz - winWidth / 2);
    glVertex3f(winX, cy + winHeight / 2 + frame, cz - winWidth / 2 - frame);

    // Right frame
    glVertex3f(winX, cy - winHeight / 2 - frame, cz + winWidth / 2);
    glVertex3f(winX, cy - winHeight / 2 - frame, cz + winWidth / 2 + frame);
    glVertex3f(winX, cy + winHeight / 2 + frame, cz + winWidth / 2 + frame);
    glVertex3f(winX, cy + winHeight / 2 + frame, cz + winWidth / 2);

    // Top frame
    glVertex3f(winX, cy + winHeight / 2, cz - winWidth / 2 - frame);
    glVertex3f(winX, cy + winHeight / 2, cz + winWidth / 2 + frame);
    glVertex3f(winX, cy + winHeight / 2 + frame, cz + winWidth / 2 + frame);
    glVertex3f(winX, cy + winHeight / 2 + frame, cz - winWidth / 2 - frame);

    // Bottom frame
    glVertex3f(winX, cy - winHeight / 2 - frame, cz - winWidth / 2 - frame);
    glVertex3f(winX, cy - winHeight / 2 - frame, cz + winWidth / 2 + frame);
    glVertex3f(winX, cy - winHeight / 2, cz + winWidth / 2 + frame);
    glVertex3f(winX, cy - winHeight / 2, cz - winWidth / 2 - frame);
    glEnd();

    // Draw window glass - light blue
    glColor3f(0.6f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(winX, cy - winHeight / 2, cz - winWidth / 2);
    glVertex3f(winX, cy - winHeight / 2, cz + winWidth / 2);
    glVertex3f(winX, cy + winHeight / 2, cz + winWidth / 2);
    glVertex3f(winX, cy + winHeight / 2, cz - winWidth / 2);
    glEnd();
}


void renderSceneSecond(void) {
    const float size = 50.0f;
    const float step = 1.0f;



    // Draw the ground and grid
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


    glPushMatrix();
    glTranslatef(0.0f, 5.0f, 15.0f);
    renderRoomVBO();               

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(-1.0f, -1.0f);
    drawBackWallWindow();         
    drawRightWallWindow();         
    glDisable(GL_POLYGON_OFFSET_FILL);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 5.0f, 15.0f);
    setupLights();
    glPopMatrix();
}

void displaySecond() {
    glClearColor(0.529f, 0.808f, 0.922f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    float radYaw = yaw * M_PI / 180.0f;
    float radPitch = pitch * M_PI / 180.0f;

    float lookX = cameraX_pos + cos(radPitch) * sin(radYaw);
    float lookY = cameraY_pos - sin(radPitch) + quakeAmplitude;
    float lookZ = cameraZ_pos - cos(radPitch) * cos(radYaw);

    gluLookAt(cameraX_pos, cameraY_pos, cameraZ_pos,
        lookX, lookY, lookZ,
        0.0f, 1.0f, 0.0f);

    GLfloat lightPos[] = { 10, 10, 10, 1 };
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

    case 'w':
    {
        float radYaw = yaw * M_PI / 180.0f;
        cameraX_pos += sin(radYaw) * speed;
        cameraZ_pos -= cos(radYaw) * speed;
        break;
    }
    case 's':
    {
        float radYaw = yaw * M_PI / 180.0f;
        cameraX_pos -= sin(radYaw) * speed;
        cameraZ_pos += cos(radYaw) * speed;
        break;
    }
    case 'a':
    {
        float radYaw = yaw * M_PI / 180.0f;
        cameraX_pos -= cos(radYaw) * speed;
        cameraZ_pos -= sin(radYaw) * speed;
        break;
    }
    case 'd':
    {
        float radYaw = yaw * M_PI / 180.0f;
        cameraX_pos += cos(radYaw) * speed;
        cameraZ_pos += sin(radYaw) * speed;
        break;
    }
    case 32: quakeAmplitude = 0.3f; glutTimerFunc(0, earthquake, 0); break;
    case 27: exit(0);
    }
    glutPostRedisplay();
}

void mouseButtonHandler(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            mouseDragging = true;
            lastMouseX = x;
            lastMouseY = y;
        }
        else if (state == GLUT_UP) {
            mouseDragging = false;
        }
    }
}

void mouseMotionHandler(int x, int y) {
    if (!mouseDragging) return;

    float sensitivity = 0.15f;

    int dx = x - lastMouseX;
    int dy = y - lastMouseY;

    yaw += dx * sensitivity;
    pitch += dy * sensitivity;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    float radYaw = yaw * M_PI / 180.0f;
    float radPitch = pitch * M_PI / 180.0f;


    lastMouseX = x;
    lastMouseY = y;

    glutPostRedisplay();
}

void earthquake(int) {
    quakeOffset += quakeAmplitude;
    quakeAmplitude *= -0.98f;

    if (fabs(quakeAmplitude) <= 0.0005f) {
        quakeOffset = 0;
        quakeAmplitude = 0;
        return;
    }

    glutPostRedisplay();
    glutTimerFunc(32, earthquake, 0);
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
