#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include "FirstScene.h"
#include "SecondScene.h"
#include "Room.h"
#include "Objects.h"

const int hillPoints = 400;
const float screenWidth = 800.0f;
const float screenHeight = 600.0f;

// camera variables
float camX = -80.0f, camY = 180.0f;
float camZoom = 2.5f;

// fade variables
float fade = 0.0f;
bool fading = false;
bool switchingScene = false;
float fadeSpeed = 0.02f;

// animation variables
bool zoomOut = false;
bool zoomIn = false;

bool panLeft = false;
bool panRight = false;

bool waitFlag = false;
float waitTime = 0.0f;

bool titleFlag = false;
float titleX = 140.0f; // Moves to 740.0f
float textSpeed = 1.0f;

// title card variables
float cardTop = screenHeight * (2.0f / 3.5f);
float cardBottom = screenHeight / 2.5f;
float cardCenterX = screenWidth * 0.5f;
float cardCenterY = (cardTop + cardBottom) * 0.5f;

void drawDoor() {
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(0, 130);
    glVertex2f(70, 130);
    glVertex2f(70, 0);
    glEnd();
    glColor3f(0.459, 0.459, 0.459);
    glColor3f(0.89f, 0.694f, 0.024f);
    glBegin(GL_QUADS);
    glVertex2f(60, 60);
    glVertex2f(60, 70);
    glVertex2f(65, 70);
    glVertex2f(65, 60);
    glEnd();
}

void drawBalcony() {
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(0, 20);
    glVertex2f(100, 20);
    glVertex2f(100, 0);
    glEnd();

    glColor3f(0.459, 0.459, 0.459);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(0, 20);
    glVertex2f(100 - 80, 20);
    glVertex2f(100 - 80, 0);
    glEnd();

    glColor3f(0, 0, 0);
    for (int i = 0; i <= 4; i++) {
        glBegin(GL_LINES);
        glVertex2f(i * 20 + 10, 20);
        glVertex2f(i * 20 + 10, 50);
        glEnd();
    }

    // Balcony railing horizontal bar
    glBegin(GL_LINES);
    glVertex2f(0, 50);
    glVertex2f(100, 50);
    glEnd();
}

void drawWindow() {
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(0, 100);
    glVertex2f(70, 100);
    glVertex2f(70, 0);
    glEnd();

    glColor3f(0.616, 0.651, 0.671);
    glBegin(GL_QUADS);
    glVertex2f(-10, -20);
    glVertex2f(-10, 0);
    glVertex2f(80, 0);
    glVertex2f(80, -20);
    glEnd();

    //shadow
    glColor3f(0.459, 0.459, 0.459);
    glBegin(GL_QUADS);
    glVertex2f(-10, -20);
    glVertex2f(-10, 0);
    glVertex2f(5, 0);
    glVertex2f(5, -20);
    glEnd();

    //glass panes
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(5, 5);
    glVertex2f(30, 5);
    glVertex2f(30, 45);
    glVertex2f(5, 45);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(5, 55);
    glVertex2f(30, 55);
    glVertex2f(30, 95);
    glVertex2f(5, 95);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(40, 5);
    glVertex2f(65, 5);
    glVertex2f(65, 45);
    glVertex2f(40, 45);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(40, 55);
    glVertex2f(65, 55);
    glVertex2f(65, 95);
    glVertex2f(40, 95);
    glEnd();
}

void drawHouse() {
    glColor3f(0.922, 0.91, 0.824);
    glBegin(GL_QUADS);
    glVertex2f(-500, -200);
    glVertex2f(-500, 120);
    glVertex2f(200, 120);
    glVertex2f(200, -200);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-100, 100);
    glVertex2f(-100, 200);
    glVertex2f(200, 200);
    glVertex2f(200, 100);
    glEnd();

    //shadow
    glColor3f(0.78, 0.773, 0.718);
    glBegin(GL_QUADS);
    glVertex2f(-100 - 10, 120);
    glVertex2f(-100 - 10, 200);
    glVertex2f(-80, 200);
    glVertex2f(-80, 120);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-500 - 10, -200);
    glVertex2f(-500 - 10, 120);
    glVertex2f(-480, 120);
    glVertex2f(-480, -200);
    glEnd();


    // Roof
    glColor3f(0.31, 0.365, 0.412);
    glBegin(GL_TRIANGLES);
    glVertex2f(-130, 200);
    glVertex2f(50, 300);
    glVertex2f(230, 200);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-530, 120);
    glVertex2f(-290, 200);
    glVertex2f(-50, 120);
    glEnd();

    //shadow
    glColor3f(0.231, 0.286, 0.329);
    glBegin(GL_TRIANGLES);
    glVertex2f(-130, 200);
    glVertex2f(50, 300);
    glVertex2f(-130 + 50, 200);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(-530, 120);
    glVertex2f(-290, 200);
    glVertex2f(-530 + 70, 120);
    glEnd();

    // Door
    glColor3f(0.58, 0.157, 0.122);
    glPushMatrix();
    glTranslatef(21, -180, 0);
    drawDoor();
    glPopMatrix();

    glColor3f(0.58, 0.157, 0.122);
    glPushMatrix();
    glTranslatef(21, 30, 0);
    drawDoor();
    glPopMatrix();

    // Window
    int a = -420;
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glColor3f(0.58, 0.157, 0.122);
        glTranslatef(a, -150, 0);
        drawWindow();
        glPopMatrix();
        a += 120;
    }

    int b = -420;
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glColor3f(0.58, 0.157, 0.122);
        glTranslatef(b, -10, 0);
        drawWindow();
        glPopMatrix();
        b += 120;
    }

    //balcony
    glColor3f(0.616, 0.651, 0.671);
    glPushMatrix();
    glTranslatef(6, 30, 0);
    drawBalcony();
    glPopMatrix();

    //steps
    glColor3f(0.616, 0.651, 0.671);
    glBegin(GL_QUADS);
    glVertex2f(21, -190); glVertex2f(101, -190);
    glVertex2f(101, -180); glVertex2f(21, -180);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(21, -200); glVertex2f(111, -200);
    glVertex2f(111, -190); glVertex2f(21, -190);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(21, -210); glVertex2f(121, -210);
    glVertex2f(121, -200); glVertex2f(21, -200);
    glEnd();

    int shadow = 70;
    //steps shadow
    glColor3f(0.459, 0.459, 0.459);
    glBegin(GL_QUADS);
    glVertex2f(21, -190); glVertex2f(101 - shadow, -190);
    glVertex2f(101 - shadow, -180); glVertex2f(21, -180);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(21, -200); glVertex2f(111 - shadow, -200);
    glVertex2f(111 - shadow, -190); glVertex2f(21, -190);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(21, -210); glVertex2f(121 - shadow, -210);
    glVertex2f(121 - shadow, -200); glVertex2f(21, -200);
    glEnd();
}

void drawHill(float baseY, float amplitude, float frequency, float r, float g, float b) {
    glColor3f(r, g, b);

    int extendedPoints = hillPoints * 3;
    float startX = -screenWidth;
    float endX = 2 * screenWidth;

    glBegin(GL_POLYGON);
    glVertex2f(startX, 0.0f);
    for (int i = 0; i <= extendedPoints; ++i) {
        float t = (float)i / extendedPoints;
        float x = startX + t * (endX - startX);
        float y = amplitude * sinf(x * frequency);
        glVertex2f(x, y + baseY);
    }
    glVertex2f(endX, 0.0f);
    glEnd();
}

void renderStrokeString(float x, float y, float scale, void* font, const char* string) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(scale, scale, 1.0f);
    while (*string) {
        glutStrokeCharacter(font, *string);
        string++;
    }
    glPopMatrix();
}

void drawTitleCard() {
    

    glColor4f(1.0f, 0.6f, 0.2f, 0.60f);

    glBegin(GL_QUADS);
    glVertex2f(0.0f, cardBottom);
    glVertex2f(screenWidth, cardBottom);
    glVertex2f(screenWidth, cardTop);
    glVertex2f(0.0f, cardTop);
    glEnd();
}


void updateZoom(int value) {
    if (titleFlag) {
        titleX += 3.0f;
        textSpeed += 0.005f;
        if (titleX >= 740.0f) {
            titleFlag = false;
            zoomOut = true;
        }
    }

    if (zoomOut) {
        camZoom -= 0.007f;
        if (camZoom <= 1.0f) {
            zoomOut = false;
            panLeft = true;
        }
    }

    if (panLeft) {
        camX -= 1.5f;
        if (camX <= -320.0f) {
            panLeft = false;
            waitFlag = true;
        }
    }

    if (waitFlag) {
        waitTime += 16.0f;
        if (waitTime >= 1500.0f) {
            waitFlag = false;
            waitTime = 0.0f;
            panRight = true;
            zoomIn = true;
        }
    }

    if (zoomIn) {
        camZoom += 0.05f;  // zoom as long as zoomIn is true
        camX += 3.0f;      // pan at the same time if needed

        if (camZoom >= 4.5f) {
            zoomIn = false;
            if (!fading) {
                fading = true;
                switchingScene = true;
                fade = 0.0f;
                fadeSpeed = fabs(fadeSpeed);
                glutTimerFunc(0, updateFade, 0);
            }
        }

        if (camX >= -100.0f) {
            panRight = false; // stop panning, but keep zooming
        }
    }

    glutPostRedisplay();

    if (titleFlag || zoomOut || zoomIn || panLeft || panRight || waitFlag)
        glutTimerFunc(16, updateZoom, 0);
}


void animation(unsigned char key, int x, int y) {
    if (!zoomOut && !zoomIn) { // only start if not already animating
        titleFlag = true;
        glutTimerFunc(0, updateZoom, 0);
    }
}

void drawFade() {
    if (fade <= 0.0f) return;

    glClearColor(0.58f, 0.157f, 0.122f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0, 0, 0, fade);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(screenWidth, 0);
    glVertex2f(screenWidth, screenHeight);
    glVertex2f(0, screenHeight);
    glEnd();

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void updateFade(int value) {
    if (!fading) return;

    fade += fadeSpeed;

    if (fade >= 1.0f && switchingScene) {
        switchingScene = false;

        initGLTEST();
        initChairMesh();
        initVaseMesh();
        initDrawerMesh();
        initClockMesh();
        initTVTABLEMesh();
        initTVMesh();
        initDoorMesh();

        glutDisplayFunc(displaySecond);
        glutKeyboardFunc(keyboardSecond);
        glutReshapeFunc(reshape);

        glutMouseFunc(mouseButtonHandler);
        glutMotionFunc(mouseMotionHandler);

        reshape(1920, 1080);

        fadeSpeed = -fadeSpeed;
    }

    if (fade <= 0.0f) {
        fade = 0.0f;
        fading = false;
        fadeSpeed = fabs(fadeSpeed);
        return;
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateFade, 0);
}

void keyboardFirst(unsigned char key, int x, int y) {
    switch (key) {
    case '2':
        initGLTEST();
        initChairMesh();
        initVaseMesh();
        initDrawerMesh();
        initClockMesh();
        initTVTABLEMesh();
        initTVMesh();
        initDoorMesh();

        glutDisplayFunc(displaySecond);
        glutKeyboardFunc(keyboardSecond);
        glutReshapeFunc(reshape);

        glutMouseFunc(mouseButtonHandler);
        glutMotionFunc(mouseMotionHandler);

        reshape(1920, 1080);

        break;
    case 32: animation(key, x, y);
        break;
    case 27: exit(0); break;
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    float moveSpeed = 5.0f;

    switch (key) {
    case GLUT_KEY_UP:    camY += moveSpeed; break;
    case GLUT_KEY_DOWN:  camY -= moveSpeed; break;
    case GLUT_KEY_LEFT:  camX -= moveSpeed; break;
    case GLUT_KEY_RIGHT: camX += moveSpeed; break;
    }

    glutPostRedisplay();
}

float hillHeightAt(float x, float baseY, float amplitude, float frequency) {
    return baseY + amplitude * sinf(x * frequency);
}

void displayFirst() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(screenWidth / 2.0f, 0.0f, 0.0f);
    glScalef(camZoom, camZoom, 1.0f);
    glTranslatef(-camX - screenWidth / 2.0f, -camY, 0.0f);

    // Draw hills
    drawHill(250.0f, 30.0f, 0.01f, 0.4f, 0.7f, 0.4f);
    drawHill(100.0f, 80.0f, 0.005f, 0.2f, 0.6f, 0.2f);

    // Variables for house position
    float houseX = 250.0f;
    float hillY = hillHeightAt(houseX, 250.0f, 30.0f, 0.01f) - 100.0f;

    // Draw house
    glPushMatrix();
    glTranslatef(houseX, hillY + 200.0f, 0.0f);
    drawHouse();
    glPopMatrix();

    // For transition
    drawFade();

    // Intro Title Card
    glPushMatrix();
    glTranslatef(titleX, 0.0f, 0.0f);
    drawTitleCard();
    glPopMatrix();

    glLoadIdentity();
    glTranslatef(titleX * textSpeed, 0.0f, 0.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    renderStrokeString(cardCenterX - 260, cardCenterY + 50, 0.25f, GLUT_STROKE_ROMAN, "BAHAY NI ED");
    renderStrokeString(cardCenterX - 220, cardCenterY + 10, 0.15f, GLUT_STROKE_ROMAN, "TN38 - Group 7");
    renderStrokeString(cardCenterX - 300, cardCenterY - 120, 0.20f, GLUT_STROKE_ROMAN, "Press Spacebar to Begin");

    glutSwapBuffers();
}

void initFirst() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.529f, 0.808f, 0.922f, 1.0f); // sky blue
}

