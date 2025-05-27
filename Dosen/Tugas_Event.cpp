#include <GL/freeglut.h>
#include <vector>
#include <cstdlib>

struct Point {
    float x, y;
    float r, g, b;
};

std::vector<Point> points;
bool useWireframe = false;
bool useWhiteColor = false;

//warna default
float box1Color[3] = {1.0f, 0.0f, 0.0f}; 
float triangleColor[3] = {0.0f, 1.0f, 0.0f}; 
float box2Color[3] = {0.0f, 0.0f, 1.0f};

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

 
    if (useWireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //kotak kiri
    glBegin(GL_QUADS);
        if (useWhiteColor)
            glColor3f(1.0f, 1.0f, 1.0f);
        else
            glColor3fv(box1Color);
            glVertex2f(110.0f, 180.0f);
            glVertex2f(210.0f, 180.0f);
            glVertex2f(210.0f, 280.0f);
            glVertex2f(110.0f, 280.0f);

    glEnd();

    // segitiga
    glBegin(GL_TRIANGLES);
        if (useWhiteColor)
            glColor3f(1.0f, 1.0f, 1.0f);
        else
            glColor3fv(triangleColor);
        glVertex2f(270.0f, 180.0f);
        glVertex2f(370.0f, 180.0f);
        glVertex2f(320.0f, 280.0f);

    glEnd();

    // kotak kanan
    glBegin(GL_QUADS);
        if (useWhiteColor)
            glColor3f(1.0f, 1.0f, 1.0f);
        else
            glColor3fv(box2Color);
            glVertex2f(430.0f, 180.0f);
            glVertex2f(530.0f, 180.0f);
            glVertex2f(530.0f, 280.0f);
            glVertex2f(430.0f, 280.0f);

    glEnd();

   
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    for (const Point& p : points) {
        if (useWhiteColor)
            glColor3f(1.0f, 1.0f, 1.0f);
        else
            glColor3f(p.r, p.g, p.b);
        glVertex2f(p.x, p.y);
    }
    glEnd();

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': case 'A':
            // generate warna random
            box1Color[0] = static_cast<float>(rand()) / RAND_MAX;
            box1Color[1] = static_cast<float>(rand()) / RAND_MAX;
            box1Color[2] = static_cast<float>(rand()) / RAND_MAX;

            triangleColor[0] = static_cast<float>(rand()) / RAND_MAX;
            triangleColor[1] = static_cast<float>(rand()) / RAND_MAX;
            triangleColor[2] = static_cast<float>(rand()) / RAND_MAX;

            box2Color[0] = static_cast<float>(rand()) / RAND_MAX;
            box2Color[1] = static_cast<float>(rand()) / RAND_MAX;
            box2Color[2] = static_cast<float>(rand()) / RAND_MAX;

            for (auto& p : points) {
                p.r = static_cast<float>(rand()) / RAND_MAX;
                p.g = static_cast<float>(rand()) / RAND_MAX;
                p.b = static_cast<float>(rand()) / RAND_MAX;
            }

            useWhiteColor = false;
            break;

        case 's': case 'S':
            useWhiteColor = true;
            break;

        case 'd': case 'D':
            useWireframe = !useWireframe;
            break;
    }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        Point p;
        p.x = static_cast<float>(x);
        p.y = static_cast<float>(480 - y); 
        // warna random
        p.r = static_cast<float>(rand()) / RAND_MAX;
        p.g = static_cast<float>(rand()) / RAND_MAX;
        p.b = static_cast<float>(rand()) / RAND_MAX;
        points.push_back(p);
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Tugas 2 Graf Kom - Jonathan A. Vandra 672022006");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
