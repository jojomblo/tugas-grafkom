// Jonathan Aditya Vandra 672022006
#include <GL/freeglut.h>
#include "texture/loadImageBmp.cpp"
#include "texture/loadImageJpg.cpp"  
#include "texture/loadImagePng.cpp" 
#include "texture/loadImageWebp.cpp" 
#include "texture/loadImageTga.cpp"
#include "texture/loadImageDds.cpp"
#include <string.h> 

float rotX = 20.0f;
float rotY = 30.0f;
bool autoRotate = false;

GLuint textureSideID;
GLuint textureFrontID;
GLuint textureBackID;
GLuint textureLeftID;
GLuint textureTopID;
GLuint textureBottomID;  

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    textureFrontID = loadBMP_custom("img/852.bmp");
    textureBackID  = loadJPG_custom("img/662.jpg");
    textureSideID = loadPNG_custom("img/346.png");
    textureLeftID = loadWebP_custom("img/784.webp");
    textureTopID = loadTGA_custom("img/691.tga");
    textureBottomID = loadDDS_custom("img/289.dds");

    glBindTexture(GL_TEXTURE_2D, textureBottomID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glBindTexture(GL_TEXTURE_2D, textureTopID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glBindTexture(GL_TEXTURE_2D, textureLeftID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, textureSideID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glBindTexture(GL_TEXTURE_2D, textureFrontID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, textureBackID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(3.0, 3.0, 7.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glRotatef(rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);

    // DEPAN (BMP)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureFrontID);
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glTexCoord2f(0, 0); glVertex3f(-1, -1, 1);
    glTexCoord2f(1.25, 0); glVertex3f(1, -1, 1);
    glTexCoord2f(1.25, 1); glVertex3f(1, 1, 1);
    glTexCoord2f(0, 1); glVertex3f(-1, 1, 1);
    glEnd();

    // BELAKANG (JPG)
    glBindTexture(GL_TEXTURE_2D, textureBackID);
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glTexCoord2f(1, 0); glVertex3f(-1, -1, -1);
    glTexCoord2f(1, 1); glVertex3f(-1, 1, -1);
    glTexCoord2f(0, 1); glVertex3f(1, 1, -1);
    glTexCoord2f(0, 0); glVertex3f(1, -1, -1);
    glEnd();

    // KANAN (PNG)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureSideID);
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(1, -1, -1);
    glTexCoord2f(0, 1); glVertex3f(1, 1, -1);
    glTexCoord2f(1, 1); glVertex3f(1, 1, 1);
    glTexCoord2f(1, 0); glVertex3f(1, -1, 1);
    glEnd();

    // KIRI (WEBP)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureLeftID);
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-1, -1, -1);
    glTexCoord2f(1, 0); glVertex3f(-1, -1, 1);
    glTexCoord2f(1, 1); glVertex3f(-1, 1, 1);
    glTexCoord2f(0, 1); glVertex3f(-1, 1, -1);
    glEnd();

    // ATAS (TGA)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureTopID);
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-1, 1, -1);
    glTexCoord2f(1, 0); glVertex3f(-1, 1, 1);
    glTexCoord2f(1, 1); glVertex3f(1, 1, 1);
    glTexCoord2f(0, 1); glVertex3f(1, 1, -1);
    glEnd();

    // BAWAH (DDS)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureBottomID);
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-1, -1, -1);
    glTexCoord2f(1, 0); glVertex3f(1, -1, -1);
    glTexCoord2f(1, 1); glVertex3f(1, -1, 1);
    glTexCoord2f(0, 1); glVertex3f(-1, -1, 1);
    glEnd();
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
    if (autoRotate) {
        rotX += 0.3f;
        rotY += 0.5f;
        if (rotX > 360) rotX -= 360;
        if (rotY > 360) rotY -= 360;
        glutPostRedisplay();
    }
    glutTimerFunc(16, timer, 0);
}

void specialKeys(int key, int, int) {
    if (!autoRotate) {
        switch (key) {
        case GLUT_KEY_UP:    rotX -= 5.0f; break;
        case GLUT_KEY_DOWN:  rotX += 5.0f; break;
        case GLUT_KEY_LEFT:  rotY -= 5.0f; break;
        case GLUT_KEY_RIGHT: rotY += 5.0f; break;
        }
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int, int) {
    if (key == 32) {
        autoRotate = !autoRotate;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Kubus BerTexture");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    return 0;
}
