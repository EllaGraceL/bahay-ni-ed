#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>
#include <vector>

// Camera
float camAngleX = 0.0f;
float camAngleY = 0.0f;
float camDistance = 0.1f;
float camPanX = 0.0f;
float camPanY = 0.0f;


GLuint roomVAO = 0;
GLuint roomVBO = 0;
int roomVertexCount = 0;


void setMaterialColor(float r, float g, float b, float shininess) {
    GLfloat ambient[] = { r * 0.25f, g * 0.25f, b * 0.25f, 1.0f };
    GLfloat diffuse[] = { r, g, b, 1.0f };
    GLfloat specular[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}


void addQuad(std::vector<float>& data,
    float x1, float y1, float z1,
    float x2, float y2, float z2,
    float x3, float y3, float z3,
    float x4, float y4, float z4)
{
    float ux = x2 - x1, uy = y2 - y1, uz = z2 - z1;
    float vx = x3 - x2, vy = y3 - y2, vz = z3 - z2;
    float nx = uy * vz - uz * vy;
    float ny = uz * vx - ux * vz;
    float nz = ux * vy - uy * vx;
    float len = sqrtf(nx * nx + ny * ny + nz * nz);
    if (len > 0.0001f) { nx /= len; ny /= len; nz /= len; }

    auto push = [&](float x, float y, float z) {
        data.push_back(x);
        data.push_back(y);
        data.push_back(z);
        data.push_back(nx);
        data.push_back(ny);
        data.push_back(nz);
        };

    // Tri 1
    push(x1, y1, z1); push(x2, y2, z2); push(x3, y3, z3);
    // Tri 2
    push(x1, y1, z1); push(x3, y3, z3); push(x4, y4, z4);
}


void initRoomVBO()
{
    const float halfW = 6.0f;
    const float halfH = 3.0f;
    const float halfD = 6.0f;

    std::vector<float> verts;

    // FLOOR
    addQuad(verts,
        -halfW, -halfH, -halfD, halfW, -halfH, -halfD,
        halfW, -halfH, halfD, -halfW, -halfH, halfD
    );

    // CEILING
    addQuad(verts,
        -halfW, halfH, -halfD, halfW, halfH, -halfD,
        halfW, halfH, halfD, -halfW, halfH, halfD
    );

    // BACK WALL
    addQuad(verts,
        -halfW, -halfH, -halfD, -halfW, halfH, -halfD,
        halfW, halfH, -halfD, halfW, -halfH, -halfD
    );

    // FRONT WALL
    addQuad(verts,
        -halfW, -halfH, halfD, halfW, -halfH, halfD,
        halfW, halfH, halfD, -halfW, halfH, halfD
    );

    // LEFT WALL
    addQuad(verts,
        -halfW, -halfH, halfD, -halfW, -halfH, -halfD,
        -halfW, halfH, -halfD, -halfW, halfH, halfD
    );

    // RIGHT WALL
    addQuad(verts,
        halfW, -halfH, -halfD, halfW, -halfH, halfD,
        halfW, halfH, halfD, halfW, halfH, -halfD
    );

    roomVertexCount = verts.size() / 6;

    glGenVertexArrays(1, &roomVAO);
    glGenBuffers(1, &roomVBO);

    glBindVertexArray(roomVAO);
    glBindBuffer(GL_ARRAY_BUFFER, roomVBO);

    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}


void renderRoomVBO()
{
    glBindVertexArray(roomVAO);

    int faceVertexCount = 6;

    // FLOOR - pink
    glColor3f(1.0f, 0.75f, 0.8f);
    glDrawArrays(GL_TRIANGLES, 0, faceVertexCount);

    // CEILING - orange
    glColor3f(1.0f, 0.6f, 0.2f);
    glDrawArrays(GL_TRIANGLES, faceVertexCount, faceVertexCount);

    // BACK WALL - grey
    glColor3f(0.6f, 0.6f, 0.6f);
    glDrawArrays(GL_TRIANGLES, faceVertexCount * 2, faceVertexCount);

    // FRONT WALL - grey
    glColor3f(0.6f, 0.6f, 0.6f);
    glDrawArrays(GL_TRIANGLES, faceVertexCount * 3, faceVertexCount);

    // LEFT WALL - grey
    glColor3f(0.6f, 0.6f, 0.6f);
    glDrawArrays(GL_TRIANGLES, faceVertexCount * 4, faceVertexCount);

    // RIGHT WALL - grey
    glColor3f(0.6f, 0.6f, 0.6f);
    glDrawArrays(GL_TRIANGLES, faceVertexCount * 5, faceVertexCount);

    glBindVertexArray(0);
}


void setupLights() {
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    GLfloat globalAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    GLfloat lightColor[] = { 0.9f, 0.85f, 0.8f, 1.0f };
    GLfloat lightDir[] = { -0.3f, -1.0f, -0.4f, 0.0f };
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightDir);

    GLfloat fillColor[] = { 0.5f, 0.55f, 0.6f, 1.0f };
    GLfloat fillPos[] = { 0.0f, 2.0f, 0.0f, 1.0f };
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, fillColor);
    glLightfv(GL_LIGHT1, GL_SPECULAR, fillColor);
    glLightfv(GL_LIGHT1, GL_POSITION, fillPos);
}


void displayTEST() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float radX = camAngleX * (3.14159265f / 180.0f);
    float radY = camAngleY * (3.14159265f / 180.0f);

    float cx = camDistance * cosf(radX) * cosf(radY);
    float cy = camDistance * sinf(radX);
    float cz = camDistance * cosf(radX) * sinf(radY);

    gluLookAt(
        cx + camPanX, cy + camPanY, cz,
        camPanX, camPanY, 0.0f,
        0.0f, 1.0f, 0.0f
    );

    setupLights();

    setMaterialColor(1.0f, 1.0f, 1.0f, 20.0f);

    renderRoomVBO();

    glutSwapBuffers();
}

void initGLTEST() {
    glewInit();
    glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    setupLights();
    initRoomVBO();
}