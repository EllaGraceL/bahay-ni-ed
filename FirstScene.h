#pragma once

void drawDoor();
void drawBalcony();
void drawWindow();
void drawHouse();
void drawHill(float baseY, float amplitude, float frequency, float r, float g, float b);

void updateZoom(int value);
void animation(unsigned char key, int x, int y);
void drawFade();
void updateFade(int value);

void keyboardFirst(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);

float hillHeightAt(float x, float baseY, float amplitude, float frequency);

void displayFirst();
void initFirst();
