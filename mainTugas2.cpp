// Jonathan Aditya Vandra - 672022006
// Tugas 1 
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

float posX = 25.0f;
float speedX = 1.0f;

float r1 = 1.0f, g1 = 0.5f, b1 = 0.0f;  
float r2 = 0.0f, g2 = 0.5f, b2 = 1.0f;  

float startR1 = r1, startG1 = g1, startB1 = b1;
float startR2 = r2, startG2 = g2, startB2 = b2;

void drawPolygon(int sides, float radius, float centerX, float centerY, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < sides; i++) {
        float angle = 2.0f * 3.1415926f * i / sides;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + centerX, y + centerY);
    }
    glEnd();
}

void init() {
    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 90, 0, 50);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    drawPolygon(6, 5, posX, 40, r1, g1, b1);
    drawPolygon(6, 5, posX, 10, r2, g2, b2); 

    glutSwapBuffers();
}

void timer(int) {
    posX += speedX;

    if (posX > (90 - 5)) {
        posX = 90 - 5;
        speedX = -speedX;

     
        float r = (rand() % 256) / 255.0f;
        float g = (rand() % 256) / 255.0f;
        float b = (rand() % 256) / 255.0f;

        r1 = r2 = r;
        g1 = g2 = g;
        b1 = b2 = b;

    } else if (posX < 5) {
        posX = 5;
        speedX = -speedX;

       
        r1 = startR1; g1 = startG1; b1 = startB1;
        r2 = startR2; g2 = startG2; b2 = startB2;
    }

    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Jonathan Aditya Vandra - 672022006");

    srand(time(NULL));
    glutDisplayFunc(display);
    init();
    glutTimerFunc(0, timer, 0); 
    glutMainLoop();
    return 0;
}
