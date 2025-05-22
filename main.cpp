#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Fungsi menggambar lingkaran
void drawCircle(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 100; ++i) {
        float angle = 2.0f * 3.14159f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();
}

// Fungsi menggambar awan sederhana
void drawCloud(float x, float y) {
    glColor3f(1.0, 1.0, 1.0);
    drawCircle(x, y, 40);
    drawCircle(x + 30, y + 10, 35);
    drawCircle(x + 60, y, 40);
}

// Fungsi menggambar pohon
void drawTree(float x, float y) {
    // Batang
    glColor3f(0.55f, 0.27f, 0.07f);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + 15, y);
        glVertex2f(x + 15, y + 80);
        glVertex2f(x, y + 80);
    glEnd();

    // Daun
    glColor3f(0.0f, 0.5f, 0.0f);
    drawCircle(x + 7, y + 100, 30);
    drawCircle(x - 10, y + 90, 25);
    drawCircle(x + 25, y + 90, 25);
}

// Fungsi menggambar rumah
void drawHouse(float x, float y, float scale = 1.0f) {
    // Dinding
    glColor3f(1.0f, 0.95f, 0.8f);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + 150 * scale, y);
        glVertex2f(x + 150 * scale, y + 120 * scale);
        glVertex2f(x, y + 120 * scale);
    glEnd();

    // Atap
    glColor3f(0.6f, 0.1f, 0.1f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x - 10, y + 120 * scale);
        glVertex2f(x + 75 * scale, y + 180 * scale);
        glVertex2f(x + 160 * scale, y + 120 * scale);
    glEnd();

    // Pintu
    glColor3f(0.4f, 0.1f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(x + 20 * scale, y);
        glVertex2f(x + 50 * scale, y);
        glVertex2f(x + 50 * scale, y + 60 * scale);
        glVertex2f(x + 20 * scale, y + 60 * scale);
    glEnd();

    // Jendela
    glColor3f(0.2f, 0.6f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(x + 90 * scale, y + 40 * scale);
        glVertex2f(x + 130 * scale, y + 40 * scale);
        glVertex2f(x + 130 * scale, y + 80 * scale);
        glVertex2f(x + 90 * scale, y + 80 * scale);
    glEnd();

    // Jendela bulat atas
    glColor3f(0.2f, 0.6f, 0.9f);
    drawCircle(x + 75 * scale, y + 140 * scale, 20 * scale);
}

// Fungsi menggambar garasi
void drawGarage(float x, float y) {
    // Bangunan utama
    glColor3f(0.7f, 0.85f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + 150, y);
        glVertex2f(x + 150, y + 120);
        glVertex2f(x, y + 120);
    glEnd();

    // Atap segitiga
    glColor3f(0.6f, 0.2f, 0.2f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x, y + 120);
        glVertex2f(x + 75, y + 180);
        glVertex2f(x + 150, y + 120);
    glEnd();

    // Pintu garasi
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(x + 20, y);
        glVertex2f(x + 130, y);
        glVertex2f(x + 130, y + 80);
        glVertex2f(x + 20, y + 80);
    glEnd();

    // Jendela atas bulat
    glColor3f(0.2f, 0.6f, 0.9f);
    drawCircle(x + 75, y + 140, 20);
}

// Fungsi menggambar mobil
void drawCar(float x, float y, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);  // Body
        glVertex2f(x, y);
        glVertex2f(x + 100, y);
        glVertex2f(x + 100, y + 30);
        glVertex2f(x + 80, y + 50);
        glVertex2f(x + 20, y + 50);
        glVertex2f(x, y + 30);
    glEnd();

    // Jendela
    glColor3f(0.8, 1.0, 1.0);
    glBegin(GL_QUADS);
        glVertex2f(x + 25, y + 30);
        glVertex2f(x + 45, y + 30);
        glVertex2f(x + 45, y + 45);
        glVertex2f(x + 25, y + 45);
    glEnd();

    // Roda
    glColor3f(0.1, 0.1, 0.1);
    drawCircle(x + 20, y, 10);
    drawCircle(x + 80, y, 10);
}

// Fungsi display utama
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Langit
    glColor3f(0.53f, 0.81f, 0.98f);
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(1280, 0);
        glVertex2f(1280, 800);
        glVertex2f(0, 800);
    glEnd();

    // Tanah
    glColor3f(0.5f, 1.0f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(1280, 0);
        glVertex2f(1280, 300);
        glVertex2f(0, 300);
    glEnd();

    // Jalan
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
        glVertex2f(0, 100);
        glVertex2f(1280, 100);
        glVertex2f(1280, 0);
        glVertex2f(0, 0);
    glEnd();

    // Gambar objek
    drawCloud(200, 700);
    drawCloud(700, 730);
    drawCloud(1050, 680);

    drawTree(400, 300);
    drawTree(900, 300);

    drawHouse(100, 300);
    drawGarage(700, 300);

    drawCar(250, 120, 1.0, 0.0, 0.0);  // Mobil merah
    drawCar(850, 120, 0.4, 0.8, 0.6);  // Mobil hijau

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 1280.0, 0.0, 800.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1280, 800);
    glutCreateWindow("Kota OpenGL");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
