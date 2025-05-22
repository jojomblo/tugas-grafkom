#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Gambar lingkaran
void drawCircle(float cx, float cy, float r)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 100; ++i)
    {
        float angle = 2.0f * 3.14159f * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();
}

// Gambar awan
void drawCloud(float x, float y, float scale)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (int i = 0; i < 5; i++)
    {
        float alpha = 0.6f - (i * 0.1f);
        float sizeFactor = 1.0f - (i * 0.05f);

        glColor4f(0.97f, 0.98f, 0.99f, alpha);
        drawCircle(x, y, 40 * scale * sizeFactor);
        drawCircle(x + 35 * scale, y + 10 * scale, 38 * scale * sizeFactor);
        drawCircle(x + 70 * scale, y, 42 * scale * sizeFactor);
        drawCircle(x + 20 * scale, y - 15 * scale, 30 * scale * sizeFactor);
        drawCircle(x + 55 * scale, y - 12 * scale, 32 * scale * sizeFactor);
    }

    glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
    drawCircle(x + 15 * scale, y + 5 * scale, 35 * scale);
    drawCircle(x + 45 * scale, y + 8 * scale, 32 * scale);

    for (int i = 0; i < 3; i++)
    {
        float shadowAlpha = 0.4f - (i * 0.1f);
        glColor4f(0.85f, 0.87f, 0.89f, shadowAlpha);
        drawCircle(x + 25 * scale, y - 18 * scale, 25 * scale - (i * 5));
        drawCircle(x + 55 * scale, y - 15 * scale, 22 * scale - (i * 5));
    }

    glColor4f(1.0f, 1.0f, 1.0f, 0.9f);
    drawCircle(x + 10 * scale, y + 20 * scale, 18 * scale);
    drawCircle(x + 60 * scale, y + 18 * scale, 15 * scale);

    glColor4f(1.0f, 1.0f, 1.0f, 0.3f);
    drawCircle(x - 10 * scale, y + 5 * scale, 15 * scale);
    drawCircle(x + 75 * scale, y - 5 * scale, 12 * scale);
    drawCircle(x + 30 * scale, y + 25 * scale, 10 * scale);

    glDisable(GL_BLEND);
}

// Gambar pohon
void drawTree(float x, float y, float scale )
{
    // Batang
    glColor3f(0.54f, 0.27f, 0.07f);
    glBegin(GL_QUADS);
    glVertex2f(x - 20 * scale, y);
    glVertex2f(x + 20 * scale, y);
    glVertex2f(x + 15 * scale, y + 80 * scale);
    glVertex2f(x - 15 * scale, y + 80 * scale);
    glEnd();

    // Cabang
    glColor3f(0.54f, 0.27f, 0.07f);
    glBegin(GL_QUADS);
    glVertex2f(x + 10 * scale, y + 80 * scale);
    glVertex2f(x + 30 * scale, y + 80 * scale);
    glVertex2f(x + 50 * scale, y + 120 * scale);
    glVertex2f(x + 30 * scale, y + 120 * scale);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(x - 10 * scale, y + 80 * scale);
    glVertex2f(x - 30 * scale, y + 80 * scale);
    glVertex2f(x - 50 * scale, y + 120 * scale);
    glVertex2f(x - 30 * scale, y + 120 * scale);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(x - 10 * scale, y + 50 * scale);
    glVertex2f(x + 10 * scale, y + 50 * scale);
    glVertex2f(x + 30 * scale, y + 70 * scale);
    glVertex2f(x + 10 * scale, y + 70 * scale);
    glEnd();

    // Daun
    glColor3f(0.1f, 0.8f, 0.1f);
    drawCircle(x, y + 150 * scale, 80 * scale);
    glColor3f(0.2f, 0.9f, 0.2f);
    drawCircle(x + 50 * scale, y + 130 * scale, 70 * scale);
    drawCircle(x - 50 * scale, y + 130 * scale, 70 * scale);
    glColor3f(0.0f, 0.6f, 0.0f);
    drawCircle(x, y + 180 * scale, 60 * scale);
    drawCircle(x + 30 * scale, y + 170 * scale, 50 * scale);
    drawCircle(x - 30 * scale, y + 170 * scale, 50 * scale);
}

// Gambar outline lingkaran
void drawCircleOutline(float cx, float cy, float r, int num_segments = 100)
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; ++i)
    {
        float theta = 2.0f * 3.14159f * float(i) / float(num_segments);
        glVertex2f(cx + r * cos(theta), cy + r * sin(theta));
    }
    glEnd();
}

// Gambar rumah
void drawHouse(float x, float y, float scale )
{
    float houseWidth = 300 * scale;
    float houseHeight = 120 * scale;

    // Dinding
    glColor3f(1.0f, 0.95f, 0.8f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + houseWidth, y);
    glVertex2f(x + houseWidth, y + houseHeight);
    glVertex2f(x, y + houseHeight);
    glEnd();

    // Atap kiri
    float roofHeight = 60 * scale;
    float roofOverhang = 20 * scale;
    glColor3f(0.6f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(x - roofOverhang, y + houseHeight);
    glVertex2f(x + houseWidth / 2, y + houseHeight + roofHeight);
    glVertex2f(x + houseWidth / 2 + roofOverhang, y + houseHeight + roofHeight);
    glVertex2f(x + roofOverhang, y + houseHeight);
    glEnd();

    // Atap kanan
    glColor3f(0.55f, 0.05f, 0.05f);
    glBegin(GL_QUADS);
    glVertex2f(x + roofOverhang, y + houseHeight);
    glVertex2f(x + houseWidth / 2 + roofOverhang, y + houseHeight + roofHeight);
    glVertex2f(x + houseWidth + roofOverhang, y + houseHeight);
    glVertex2f(x + houseWidth, y + houseHeight);
    glEnd();

    // Cerobong
    glColor3f(0.8f, 0.4f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(x + 200 * scale, y + houseHeight + 30 * scale);
    glVertex2f(x + 210 * scale, y + houseHeight + 30 * scale);
    glVertex2f(x + 210 * scale, y + houseHeight + 60 * scale);
    glVertex2f(x + 200 * scale, y + houseHeight + 60 * scale);
    glEnd();

    // Pintu
    glColor3f(0.4f, 0.1f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x + 40 * scale, y);
    glVertex2f(x + 80 * scale, y);
    glVertex2f(x + 80 * scale, y + 70 * scale);
    glVertex2f(x + 40 * scale, y + 70 * scale);
    glEnd();

    // Jendela kotak
    glColor3f(0.6f, 0.85f, 0.95f);
    glBegin(GL_QUADS);
    glVertex2f(x + 200 * scale, y + 50 * scale);
    glVertex2f(x + 250 * scale, y + 50 * scale);
    glVertex2f(x + 250 * scale, y + 80 * scale);
    glVertex2f(x + 200 * scale, y + 80 * scale);
    glEnd();

    // Frame jendela kotak
    glColor3f(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x + 200 * scale, y + 50 * scale);
    glVertex2f(x + 250 * scale, y + 50 * scale);
    glVertex2f(x + 250 * scale, y + 80 * scale);
    glVertex2f(x + 200 * scale, y + 80 * scale);
    glEnd();
    // Garis tengah jendela kotak
    glBegin(GL_LINES);
    glVertex2f(x + 225 * scale, y + 50 * scale);
    glVertex2f(x + 225 * scale, y + 80 * scale);
    glEnd();

    // Jendela bulat
    float centerX = x + 120 * scale;
    float centerY = y + 145 * scale;
    float radius = 20 * scale;

    glColor3f(0.6f, 0.85f, 0.95f);
    drawCircle(centerX, centerY, radius);

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3);
    drawCircleOutline(centerX, centerY, radius);

    // Garis jendela bulat
    glBegin(GL_LINES);
    glVertex2f(centerX - radius, centerY);
    glVertex2f(centerX + radius, centerY);
    glVertex2f(centerX, centerY - radius);
    glVertex2f(centerX, centerY + radius);
    glEnd();
}

// Gambar garasi
void drawGarage(float x, float y, float scale = 1.5f)
{
    // Bangunan utama
    glColor3f(0.7f, 0.85f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 150 * scale, y);
    glVertex2f(x + 150 * scale, y + 120 * scale);
    glVertex2f(x, y + 120 * scale);
    glEnd();

    // Atap segitiga
    glColor3f(0.6f, 0.2f, 0.2f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y + 120 * scale);
    glVertex2f(x + 75 * scale, y + 180 * scale);
    glVertex2f(x + 150 * scale, y + 120 * scale);
    glEnd();

    // Outline atap
    glColor3f(0.4f, 0.1f, 0.1f);
    glLineWidth(4.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(x, y + 120 * scale);
    glVertex2f(x + 75 * scale, y + 180 * scale);
    glVertex2f(x + 150 * scale, y + 120 * scale);
    glEnd();

    // Pintu garasi
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(x + 20 * scale, y);
    glVertex2f(x + 130 * scale, y);
    glVertex2f(x + 130 * scale, y + 80 * scale);
    glVertex2f(x + 20 * scale, y + 80 * scale);
    glEnd();

    // Garis pintu garasi
    glColor3f(0.4f, 0.4f, 0.4f);
    for (float i = 5 * scale; i < 80 * scale; i += 8 * scale)
    {
        glBegin(GL_QUADS);
        glVertex2f(x + 20 * scale, y + i);
        glVertex2f(x + 130 * scale, y + i);
        glVertex2f(x + 130 * scale, y + i + 4 * scale);
        glVertex2f(x + 20 * scale, y + i + 4 * scale);
        glEnd();
    }

    // Jendela bulat
    glColor3f(0.2f, 0.6f, 0.9f);
    glLineWidth(4.0f);
    drawCircle(x + 75 * scale, y + 140 * scale, 20 * scale);

    // Garis vertikal jendela bulat
    glBegin(GL_LINES);
    glVertex2f(x + 75 * scale, y + 120 * scale);
    glVertex2f(x + 75 * scale, y + 160 * scale);
    glEnd();
}

// Gambar mobil
void drawCar(float x, float y, float scale, float r, float g, float b)
{
    // Bodi
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(x + 0 * scale, y + 0 * scale);
    glVertex2f(x + 0 * scale, y + 30 * scale);
    glVertex2f(x + 30 * scale, y + 55 * scale);
    glVertex2f(x + 80 * scale, y + 65 * scale);
    glVertex2f(x + 120 * scale, y + 65 * scale);
    glVertex2f(x + 150 * scale, y + 55 * scale);
    glVertex2f(x + 180 * scale, y + 30 * scale);
    glVertex2f(x + 180 * scale, y + 0 * scale);
    glEnd();

    // Jendela depan
    glColor3f(0.8f, 0.9f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(x + 35 * scale, y + 32 * scale);
    glVertex2f(x + 45 * scale, y + 55 * scale);
    glVertex2f(x + 85 * scale, y + 60 * scale);
    glVertex2f(x + 85 * scale, y + 32 * scale);
    glEnd();

    // Jendela belakang
    glBegin(GL_POLYGON);
    glVertex2f(x + 95 * scale, y + 32 * scale);
    glVertex2f(x + 95 * scale, y + 60 * scale);
    glVertex2f(x + 145 * scale, y + 55 * scale);
    glVertex2f(x + 155 * scale, y + 32 * scale);
    glEnd();

    // Garis tengah jendela
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
    glVertex2f(x + 90 * scale, y + 32 * scale);
    glVertex2f(x + 90 * scale, y + 62 * scale);
    glEnd();

    // Roda depan
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircle(x + 45 * scale, y + 3 * scale, 20 * scale);
    glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle(x + 45 * scale, y + 3 * scale, 13 * scale);

    // Roda belakang
    glColor3f(0.1f, 0.1f, 0.1f);
    drawCircle(x + 135 * scale, y + 3 * scale, 20 * scale);
    glColor3f(0.7f, 0.7f, 0.7f);
    drawCircle(x + 135 * scale, y + 3 * scale, 13 * scale);
}

// Posisi mobil 1
float carPosX1 = 1280.0f;
float carSpeed1 = 2.0f; 

// Update mobil 1
void updateCar1(int value)
{
    carPosX1 -= carSpeed1;
    if (carPosX1 < -200)  
        carPosX1 = 1280; 
    glutPostRedisplay();
    glutTimerFunc(16, updateCar1, 0);
}

// Posisi mobil 2
float carPosX2 = -200.0f;
float carSpeed2 = 2.0f;

// Update mobil 2
void updateCar2(int value)
{
    carPosX2 += carSpeed2;
    if (carPosX2 > 1280)  
        carPosX2 = -200;  
    glutPostRedisplay();
    glutTimerFunc(16, updateCar2, 0);
}

// Fungsi display utama
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Langit
    glColor3f(0.53f, 0.81f, 0.98f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(1280, 0);
    glVertex2f(1280, 800);
    glVertex2f(0, 800);
    glEnd();

    // Matahari
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Halo matahari
    for (int i = 3; i >= 1; --i) {
        float alpha = 0.15f * i;
        float radius = 90.0f + 25.0f * i;
        glColor4f(1.0f, 0.95f, 0.5f, alpha);
        drawCircle(1200.0f, 720.0f, radius);
    }

    // Matahari utama
    glColor3f(1.0f, 0.95f, 0.4f);
    drawCircle(1200.0f, 720.0f, 80.0f);

    // Sinar matahari
    glLineWidth(6.0f);
    glColor4f(1.0f, 0.95f, 0.5f, 0.5f);
    glBegin(GL_LINES);
    for (int i = 0; i < 12; ++i) {
        float angle = 2.0f * 3.14159f * i / 12;
        float x1 = 1200.0f + cos(angle) * 90.0f;
        float y1 = 720.0f + sin(angle) * 90.0f;
        float x2 = 1200.0f + cos(angle) * 130.0f;
        float y2 = 720.0f + sin(angle) * 130.0f;
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    }
    glEnd();

    glDisable(GL_BLEND);

    // Tanah 
    glColor3f(0.5f, 1.0f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(0, 50);
    glVertex2f(1280, 50);
    glVertex2f(1280, 220); 
    glVertex2f(0, 220);    
    glEnd();

    // Trotoar 
    glColor3f(0.75f, 0.75f, 0.75f); 
    glBegin(GL_QUADS);
    glVertex2f(0, 130);
    glVertex2f(1280, 130);
    glVertex2f(1280, 200);
    glVertex2f(0, 200);
    glEnd();

    // Zebra cross
    float tileWidth = 40.0f;
    float tileHeight = 20.0f;
    float trotoarYStart = 130.0f;

    for (float x = 0; x < 1280; x += tileWidth)
    {
        bool isWhite = (int(x / tileWidth) % 2 == 0);
        if (isWhite)
            glColor3f(1.0f, 1.0f, 1.0f);
        else
            glColor3f(0.0f, 0.0f, 0.0f);

        glBegin(GL_QUADS);
        glVertex2f(x, trotoarYStart);
        glVertex2f(x + tileWidth, trotoarYStart);
        glVertex2f(x + tileWidth, trotoarYStart + tileHeight);
        glVertex2f(x, trotoarYStart + tileHeight);
        glEnd();
    }

    // Jalan 
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(1280, 0);
    glVertex2f(1280, 130);
    glVertex2f(0, 130);
    glEnd();

    // Garis jalan
    glColor3f(1.0f, 1.0f, 1.0f);
    float dashLength = 60.0f;
    float gapLength = 40.0f;
    float yCenter = 50.0f;
    float lineWidth = 8.0f;
    for (float x = 0; x < 1280; x += dashLength + gapLength)
    {
        glBegin(GL_QUADS);
        glVertex2f(x, yCenter - lineWidth / 2);
        glVertex2f(x + dashLength, yCenter - lineWidth / 2);
        glVertex2f(x + dashLength, yCenter + lineWidth / 2);
        glVertex2f(x, yCenter + lineWidth / 2);
        glEnd();
    }

    // Gambar objek
    drawCloud(200, 700, 1.5);
    drawCloud(700, 730, 1.5);
    drawCloud(1050, 680, 1);
    drawCloud(460, 650, 1.2);

    drawTree(620, 200, 1.7);
    drawTree(1000, 200,1.3);
    drawTree(100, 200,1.3);
    drawHouse(100, 200, 1.5);
    drawGarage(700, 200);
    drawGarage(1200, 200);

    drawCar(carPosX1, 120, 1.7, 0.8f, 0.2f, 0.2f); 
    drawCar(carPosX2, 35, 1.7, 0.1f, 0.2f, 0.6f);

    glFlush();
}

// Inisialisasi
void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 1280.0, 0.0, 800.0);
    glutTimerFunc(0, updateCar1, 0);
    glutTimerFunc(0, updateCar2, 0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1280, 800);
    glutCreateWindow("Jonathan Aditya Vandra - 672022006");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
