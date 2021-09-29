
#include <iostream>
#include <GL/glut.h>

using namespace std;

// cloud1 and cloud2 coords
GLfloat cloudX1 = 0, cloudY1 = 0, cloudX2 = 0, cloudY2 = 0;
// boat coords
GLfloat boatX = 0, boatY = 0;
// translation status (enabled/disabled)
GLint cloudStatus = 1, boatStatus = 1;


// function to draw a circle given center(x, y) and r
void drawCircle(GLfloat cx, GLfloat cy, GLfloat r, GLint segs) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segs; i++) {
        GLfloat theta = 2.0 * 3.14 * (GLfloat)i / (GLfloat)segs;
        GLfloat x = r * cos(theta), y = r * sin(theta);

        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawTree() {
    glPushMatrix();
    // trunk
    glBegin(GL_POLYGON);
    glColor3f(0.43, 0.0, 0.0);
    glVertex2i(338, 385);
    glVertex2i(338, 510);
    glVertex2i(358, 510);
    glVertex2i(358, 380);
    glEnd();

    // upper part
    glColor3f(0.0, 0.8, 0.1);
    drawCircle(328, 505, 20, 1000);
    drawCircle(348, 505, 20, 1000);
    drawCircle(368, 505, 20, 1000);
    drawCircle(318, 525, 20, 1000);
    drawCircle(338, 525, 20, 1000);
    drawCircle(358, 525, 20, 1000);
    drawCircle(378, 525, 20, 1000);
    drawCircle(328, 545, 20, 1000);
    drawCircle(346, 545, 20, 1000);
    drawCircle(368, 545, 20, 1000);
    drawCircle(348, 560, 20, 1000);

    glPopMatrix();
}

void drawHouse(void) {
    glPushMatrix();
    // lower part
    glBegin(GL_POLYGON);
    glColor3f(0.7, 0.3, 0.1);
    glVertex2i(350, 380);
    glVertex2i(350, 460);
    glVertex2i(430, 460);
    glVertex2i(430, 380);
    glEnd();
    // upper part
    glBegin(GL_POLYGON);
    glColor3f(0.9, 0.0, 0.0);
    glVertex2i(340, 460);
    glVertex2i(390, 515);
    glVertex2i(440, 460);
    glEnd();
    // door
    glBegin(GL_POLYGON);
    glColor3f(0.4, 0.0, 0.0);
    glVertex2i(370, 380);
    glVertex2i(370, 430);
    glVertex2i(410, 430);
    glVertex2i(410, 380);
    glEnd();

    glPopMatrix();
}

void drawSun(void) {
    glPushMatrix();

    glColor3f(1.0, 1.0, 0.5);
    drawCircle(900, 700, 40, 1000);

    glPopMatrix();
}

void drawCloud1(void) {
    glPushMatrix();
    // cloud 1
    glColor3f(0.8, 0.8, 0.8);
    drawCircle(200, 690, 25, 1000);
    drawCircle(230, 700, 25, 1000);
    drawCircle(180, 700, 25, 1000);
    drawCircle(210, 720, 25, 1000);

    glPopMatrix();
}

void drawCloud2(void) {
    glPushMatrix();
    // cloud 2
    drawCircle(600, 590, 25, 1000);
    drawCircle(630, 600, 26, 1000);
    drawCircle(580, 600, 25, 1000);
    drawCircle(610, 620, 25, 1000);

    glPopMatrix();
}

void drawBoat(void) {
    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0.9, 0.8, 0.1);
    glVertex2i(270, 155);
    glVertex2i(375, 165);
    glVertex2i(480, 155);
    glVertex2i(480, 20);
    glVertex2i(270, 20);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.35, 0.0, 0.0);
    glVertex2i(250, 20);
    glVertex2i(180, 100);
    glVertex2i(380, 80);
    glVertex2i(600, 100);
    glVertex2i(500, 20);
    glEnd();

    glPopMatrix();
}

void scene() {
    glPushMatrix();
    // sky
    glBegin(GL_POLYGON);
    glColor3f(0.4, 0.5, 1.0);
    glVertex2i(0, 800);
    glVertex2i(1200, 800);
    // change color to create a gradient effect
    glColor3f(0.7, 0.7, 1.0);
    glVertex2i(1200, 0);
    glVertex2i(0, 0);
    glEnd();

    // ground
    glBegin(GL_POLYGON);
    // light green
    glColor3f(0.0, 0.5, 0.0);
    glVertex2i(0, 200);
    glVertex2i(200, 350);
    glVertex2i(400, 400);
    glVertex2i(600, 350);
    glVertex2i(800, 320);
    glVertex2i(1000, 300);
    // change to dark green
    // thus creating a gradient effect from light to dark green
    glColor3f(0.1, 0.9, 0.1);
    glVertex2i(1200, 200);
    glVertex2i(1200, 100);
    glVertex2i(0, 100);
    glEnd();

    // river
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.3, 1.0);
    glVertex2i(0, 100);
    glVertex2i(200, 120);
    glVertex2i(400, 140);
    glVertex2i(600, 150);
    glVertex2i(1000, 120);
    glVertex2i(1200, 100);
    glVertex2i(1200, 0);
    glVertex2i(0, 0);
    glEnd();

    // tree
    drawTree();

    // house
    drawHouse();

    // sun
    drawSun();

    glPopMatrix();
}

// boat translation
void boat(void) {
    if (boatStatus == 1) {
        boatX += 0.5;
    }
    if (boatX > 1000) {
        boatX = -600;
    }

    // translate the boat to its new position
    glPushMatrix();
    glTranslatef(boatX, boatY, 0);
    drawBoat();
    glPopMatrix();
}

// cloud1 translation
void cloud1(void) {
    if (cloudStatus == 1) {
        cloudX1 += 0.2;
    }
    if (cloudX1 > 1100) {
        cloudX1 = -650;
    }

    glPushMatrix();
    glTranslatef(cloudX1, cloudY1, 0.0);
    drawCloud1();
    glPopMatrix();
}

// cloud2 translation
void cloud2(void) {
    if (cloudStatus == 1) {
        cloudX2 += 0.2;
    }
    if (cloudX2 > 600) {
        cloudX2 = -1150;
    }

    glPushMatrix();
    glTranslatef(cloudX2, cloudY2, 0.0);
    drawCloud2();
    glPopMatrix();
}

void init(void) {
    glClearColor(0.0, 0.0, 1.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 1200.0, 0.0, 800.0);
}

// keyboard callback
void keyboard(unsigned char key, int x, int y) {

    switch (key) {
        // s resumes the tranlation
    case 's':
        boatStatus = 1;
        cloudStatus = 1;
        break;
        // p pauses the translation
    case 'p':
        boatStatus = 0;
        cloudStatus = 0;
        break;
    default:
        break;
    }
}

// display callback
void display(void) {
    // draw the scene
    scene();
    // responsible of drawing and translation of the boat and clouds
    boat();
    cloud1();
    cloud2();

    glFlush();

    // set a flag to call "display" callback on each iteration of the mainloop
    glutPostRedisplay();
    // since double buffering is used, render the next frame and swap the buffers
    glutSwapBuffers();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1350, 700);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("I3333");
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);

    init();
    glutMainLoop();
}
