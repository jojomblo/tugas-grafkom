// Jonathan Aditya Vandra - 672022006
// Tugas 3
#include <GL/freeglut.h>
#include <cmath>

float dotX = 240.0f, dotY = 320.0f;
float velX = 3.0f, velY = 2.0f;
const float radius = 8.0f;
const int winW = 640, winH = 480;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 1, 1);
    glPointSize(radius * 0.8f);
    glBegin(GL_POINTS);
    glVertex2f(dotX, dotY);
    glEnd();

    glFlush();
}

void timer(int) {
    const float slowZone = 40.0f;
    const float defaultVelX = 3.0f;
    const float defaultVelY = 2.0f;

    // pelanin kalau deket kiri kanan
    if ((dotX - radius < slowZone && velX < 0) || (dotX + radius > winW - slowZone && velX > 0)) {
        velX *= 0.955f;
    }

    // pelanin kalau deket atas bawah
    if ((dotY - radius < slowZone && velY < 0) || (dotY + radius > winH - slowZone && velY > 0)) {
        velY *= 0.955f;
    }

    // set kecepatan setelah mantul
    if (dotX - radius <= 0) {
        dotX = radius;
        velX = defaultVelX;  
    }
    if (dotX + radius >= winW) {
        dotX = winW - radius;
        velX = -defaultVelX;
    }
    if (dotY - radius <= 0) {
        dotY = radius;
        velY = defaultVelY;
    }
    if (dotY + radius >= winH) {
        dotY = winH - radius;
        velY = -defaultVelY;
    }

    dotX += velX;
    dotY += velY;

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void init() {
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, winW, 0, winH);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Jonathan Aditya Vandra - 672022006");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
