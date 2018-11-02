#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include<iostream>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define PI 3.14159265

double rotate_y=0;
double rotate_x=0;
static unsigned int table, bottomMachine, topMachine, cokeCan, keyboard, monitor, monitorScreen, monitorBase;
static unsigned int topMonitor;

using namespace std;

void displayText(){
    string strScore = "SHALL WE PLAY A GAME? Love to. How about Global Thermonuclear War? WOULDN’T YOU PREFER A NICE GAME OF MARBLES?";
    int n = strScore.length();
    char text[n+1];
    strcpy(text, strScore.c_str());
    
    glColor3f(255, 255, 255);
    glRasterPos3f(-.8, .8, -1);
    
    for(int i = 0; text[i] != '\0'; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text[i]);
    }
}

void display() {
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    // Reset transformations
    glLoadIdentity();
    
    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    
    // Other Transformations
    // glScalef( 2.0, 2.0, 0.0 );          // Not included
    
//    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); //To turn off wireframe
    
    glCallList(table);
    glCallList(bottomMachine);
    glCallList(topMachine);
    glCallList(keyboard);
    glCallList(monitor);
    glCallList(monitorScreen);
    glCallList(monitorBase);
    glCallList(topMonitor);
    displayText();


    

    //Move to position & draw coke can
    glColor3f(0.95, 0.16, 0.16);
    glPushMatrix();
    glRotatef(270, 1, 0, 0);
    glTranslatef(-0.35, 0.45, 0.025);
    glScalef(0.1, 0.1, 0.1);
    glCallList(cokeCan);
    glPopMatrix();
    
    //Draw table legs
    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glTranslatef(0.45, 0.45, 0.025);
    glScalef(0.1, 0.1, 0.8);
    glCallList(cokeCan);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glTranslatef(-0.45, -0.45, 0.025);
    glScalef(0.1, 0.1, 0.8);
    glCallList(cokeCan);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glTranslatef(0.45, -0.45, 0.025);
    glScalef(0.1, 0.1, 0.8);
    glCallList(cokeCan);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glTranslatef(-0.45, 0.45, 0.025);
    glScalef(0.1, 0.1, 0.8);
    glCallList(cokeCan);
    glPopMatrix();
    //END Table legs
    
    //Draw marbles
    glColor3f(0.59, 0.95, 0.99);
    glPushMatrix();
    glTranslatef(-0.40, 0.035, -0.45);
    glutSolidSphere(0.01, 15, 15);
    glTranslatef(-0.04, 0, -0.02);
    glutSolidSphere(0.01, 15, 15);
    glTranslatef(-0.01, 0, 0.03);
    glutSolidSphere(0.01, 15, 15);
    glPopMatrix();
    
 
    glFlush();
    glutSwapBuffers();
    
}

void setup() {
    
    GLUquadricObj *qobj;
    cokeCan = glGenLists(1);
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_FLAT);
    glNewList(cokeCan, GL_COMPILE);
    gluCylinder(qobj, 0.3, 0.3, 1.0, 15, 5);
    glTranslatef(0, 0, 1);
    gluCylinder(qobj, 0.3, 0.25, 0.1, 15, 5);
    glTranslatef(0, 0, 0.1);
    
    //Coke can cap
    float i = 0.0f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, 0);
    for(i = 0.0f; i <= 360; i++)
        glVertex3f(0.25*cos(PI * i / 180.0), 0.25*sin(PI * i / 180.0), 0);
    glEnd();
    glEndList();
    //END Coke can
    
    //Draw table
//    glColor3f(1, 0, 0);
    table = glGenLists(1);
    glNewList(table, GL_COMPILE);
    glPushMatrix();
    glColor3f(0.4, 0.4, 0.4);
    
    glBegin(GL_POLYGON); //front
    glVertex3f(  0.5, -0.025, -0.5 );
    glVertex3f(  0.5,  0.025, -0.5 );
    glVertex3f( -0.5,  0.025, -0.5 );
    glVertex3f( -0.5, -0.025, -0.5 );
    glEnd();
    
    glBegin(GL_POLYGON); //back
    glVertex3f(  0.5, -0.025, 0.5 );
    glVertex3f(  0.5,  0.025, 0.5 );
    glVertex3f( -0.5,  0.025, 0.5 );
    glVertex3f( -0.5, -0.025, 0.5 );
    glEnd();
    
    glBegin(GL_POLYGON); //right
    glVertex3f( 0.5, -0.025, -0.5 );
    glVertex3f( 0.5,  0.025, -0.5 );
    glVertex3f( 0.5,  0.025,  0.5 );
    glVertex3f( 0.5, -0.025,  0.5 );
    glEnd();
    
    glBegin(GL_POLYGON); //left
    glVertex3f( -0.5, -0.025,  0.5 );
    glVertex3f( -0.5,  0.025,  0.5 );
    glVertex3f( -0.5,  0.025, -0.5 );
    glVertex3f( -0.5, -0.025, -0.5 );
    glEnd();
    
    glBegin(GL_POLYGON); //top
    glVertex3f(  0.5,  0.025,  0.5 );
    glVertex3f(  0.5,  0.025, -0.5 );
    glVertex3f( -0.5,  0.025, -0.5 );
    glVertex3f( -0.5,  0.025,  0.5 );
    glEnd();
    
    glBegin(GL_POLYGON); //bottom
    glVertex3f(  0.5, -0.025, -0.5 );
    glVertex3f(  0.5, -0.025,  0.5 );
    glVertex3f( -0.5, -0.025,  0.5 );
    glVertex3f( -0.5, -0.025, -0.5 );
    glEnd();
    
    glPopMatrix();
    glEndList();
    //END Table
    
    
    bottomMachine = glGenLists(1);
    glNewList(bottomMachine, GL_COMPILE);
    glPushMatrix();
    glTranslatef(-.27,.075,.075);

    glBegin(GL_POLYGON); //front
    glColor3f(0.73, 0.73, 0.73);
    
    glVertex3f(  0.2, -.05, -.4 );
    glVertex3f(  .2,  .05, -.4 );
    glVertex3f( -.2,  .05, -.4 );
    glVertex3f( -.2, -.05, -.4 );
    glEnd();
    
    glBegin(GL_POLYGON); //back
    glColor3f(.19, .6, .8);

    glVertex3f(  .2, -.05, .4 );
    glVertex3f(  .2,  .05, .4 );
    glVertex3f( -.2,  .05, .4 );
    glVertex3f( -.2, -.05, .4 );
    glEnd();
    
    glBegin(GL_POLYGON); //right
    glVertex3f( .2, -.05, -.4 );
    glVertex3f( .2,  .05, -.4 );
    glVertex3f( .2,  .05,  .4 );
    glVertex3f( .2, -.05,  .4 );
    glEnd();
    
    glBegin(GL_POLYGON); //left
    glVertex3f( -.2, -.05,  .4 );
    glVertex3f( -.2,  .05,  .4 );
    glVertex3f( -.2,  .05, -.4 );
    glVertex3f( -.2, -.05, -.4 );
    glEnd();
    
    glBegin(GL_POLYGON); //top
    glVertex3f(  .2,  .05,  .4 );
    glVertex3f(  .2,  .05, -.4 );
    glVertex3f( -.2,  .05, -.4 );
    glVertex3f( -.2,  .05,  .4 );
    glEnd();
    
    glBegin(GL_POLYGON); //bottom
    glVertex3f(  .2, -.05, -.4 );
    glVertex3f(  .2, -.05,  .4 );
    glVertex3f( -.2, -.05,  .4 );
    glVertex3f( -.2, -.05, -.4 );
    glEnd();
    
    glPopMatrix();
    glEndList();
    //END Bottom machine
    
    
    topMachine = glGenLists(1);
    glNewList(topMachine, GL_COMPILE);
    glPushMatrix();
    glTranslatef(-.27,.17,.075);
    
    glBegin(GL_POLYGON); //front
    glColor3f(0.5, 0.54, 0.53);
    
    glVertex3f(  0.2, -.05, -.4 );
    glVertex3f(  .2,  .05, -.4 );
    glVertex3f( -.2,  .05, -.4 );
    glVertex3f( -.2, -.05, -.4 );
    glEnd();
    
    glBegin(GL_POLYGON); //back
    glColor3f(0.9, 0.91, 0.84);

    glVertex3f(  .2, -.05, .4 );
    glVertex3f(  .2,  .05, .4 );
    glVertex3f( -.2,  .05, .4 );
    glVertex3f( -.2, -.05, .4 );
    glEnd();
    
    glBegin(GL_POLYGON); //right
    glVertex3f( .2, -.05, -.4 );
    glVertex3f( .2,  .05, -.4 );
    glVertex3f( .2,  .05,  .4 );
    glVertex3f( .2, -.05,  .4 );
    glEnd();
    
    glBegin(GL_POLYGON); //left
    glVertex3f( -.2, -.05,  .4 );
    glVertex3f( -.2,  .05,  .4 );
    glVertex3f( -.2,  .05, -.4 );
    glVertex3f( -.2, -.05, -.4 );
    glEnd();
    
    glBegin(GL_POLYGON); //top
    glVertex3f(  .2,  .05,  .4 );
    glVertex3f(  .2,  .05, -.4 );
    glVertex3f( -.2,  .05, -.4 );
    glVertex3f( -.2,  .05,  .4 );
    glEnd();
    
    glBegin(GL_POLYGON); //bottom
    glVertex3f(  .2, -.05, -.4 );
    glVertex3f(  .2, -.05,  .4 );
    glVertex3f( -.2, -.05,  .4 );
    glVertex3f( -.2, -.05, -.4 );
    glEnd();
    
    glPopMatrix();
    glEndList();
    //END top machine
    
    
    keyboard = glGenLists(1);
    glNewList(keyboard, GL_COMPILE);
    glPushMatrix();
    glTranslatef(.2,.04, -.38);
    glColor3f(0.32, 0.32, 0.32);
    
    glBegin(GL_POLYGON); //front
    glVertex3f(  0.2, -.02, -.1 );
    glVertex3f(  .2,  .02, -.1);
    glVertex3f( -.2,  .02, -.1 );
    glVertex3f( -.2, -.02, -.1 );
    glEnd();
    
    glBegin(GL_POLYGON); //back
    glVertex3f(  .2, -.05, .1 );
    glVertex3f(  .2,  .05, .1 );
    glVertex3f( -.2,  .05, .1 );
    glVertex3f( -.2, -.05, .1 );
    glEnd();
    
    glBegin(GL_POLYGON); //right
    glVertex3f( .2, -.02, -.1 );
    glVertex3f( .2,  .02, -.1 );
    glVertex3f( .2,  .05,  .1 );
    glVertex3f( .2, -.05,  .1 );
    glEnd();
    
    glBegin(GL_POLYGON); //left
    glVertex3f( -.2, -.05,  .1 );
    glVertex3f( -.2,  .05,  .1 );
    glVertex3f( -.2,  .02, -.1 );
    glVertex3f( -.2, -.02, -.1 );
    glEnd();
    
    glBegin(GL_POLYGON); //top
    glColor3f(0.16, 0.16, 0.16);
    glVertex3f(  .2,  .05,  .1 );
    glVertex3f(  .2,  .02, -.1 );
    glVertex3f( -.2,  .02, -.1 );
    glVertex3f( -.2,  .05,  .1 );
    glEnd();
    
    glBegin(GL_POLYGON); //bottom
    glVertex3f(  .2, -.02, -.1 );
    glVertex3f(  .2, -.02,  .1 );
    glVertex3f( -.2, -.02,  .1 );
    glVertex3f( -.2, -.02, -.1 );
    glEnd();
    
    glPopMatrix();
    glEndList();
    //END keyboard
    
    
    monitor = glGenLists(1);
    glNewList(monitor, GL_COMPILE);
    glPushMatrix();
    glTranslatef(.2, .3, -.05);
    
    glBegin(GL_POLYGON); //front
    glColor3f(0.08, 0.08, 0.08);
    
    glVertex3f(  0.2, -.2, -.2 );
    glVertex3f(  .2,  .2, -.2);
    glVertex3f( -.2,  .2, -.2 );
    glVertex3f( -.2, -.2, -.2 );
    glEnd();
    
    glBegin(GL_POLYGON); //back
    glColor3f(0.93, 0.9, 0.75);

    glVertex3f(  .2, -.2, .2 );
    glVertex3f(  .2,  .2, .2 );
    glVertex3f( -.2,  .2, .2 );
    glVertex3f( -.2, -.2, .2 );
    glEnd();
    
    glBegin(GL_POLYGON); //right
    glVertex3f( .2, -.2, -.2 );
    glVertex3f( .2,  .2, -.2 );
    glVertex3f( .2,  .2,  .2 );
    glVertex3f( .2, -.2,  .2 );
    glEnd();
    
    glBegin(GL_POLYGON); //left
    glVertex3f( -.2, -.2,  .2 );
    glVertex3f( -.2,  .2,  .2 );
    glVertex3f( -.2,  .2, -.2 );
    glVertex3f( -.2, -.2, -.2 );
    glEnd();
    
    glBegin(GL_POLYGON); //top
    glVertex3f(  .2,  .2,  .2 );
    glVertex3f(  .2,  .2, -.2 );
    glVertex3f( -.2,  .2, -.2 );
    glVertex3f( -.2,  .2,  .2 );
    glEnd();
    
    glBegin(GL_POLYGON); //bottom
    glVertex3f(  .2, -.2, -.2 );
    glVertex3f(  .2, -.2,  .2 );
    glVertex3f( -.2, -.2,  .2 );
    glVertex3f( -.2, -.2, -.2 );
    glEnd();
    
    glPopMatrix();
    glEndList();
    //END monitor
    
    
    monitorScreen = glGenLists(1);
    glNewList(monitorScreen, GL_COMPILE);
    glPushMatrix();
    glTranslatef(.2, .3, -.26);
    glColor3f(0.86, 0.85, 0.83);
    
    glBegin(GL_POLYGON); //front
    glVertex3f(  .16, -.16, 0 );
    glVertex3f(  .16,  .16, 0 );
    glVertex3f( -.16,  .16, 0 );
    glVertex3f( -.16, -.16, 0 );
    glEnd();
    
    glBegin(GL_POLYGON); //back
    glVertex3f(  .16, -.16, 0 );
    glVertex3f(  .16,  .16, 0 );
    glVertex3f( -.16,  .16, 0 );
    glVertex3f( -.16, -.16, 0 );
    glEnd();
    
    glBegin(GL_POLYGON); //right
    glVertex3f( .16, -.16, 0 );
    glVertex3f( .16,  .16, 0 );
    glVertex3f( .16,  .16, 0 );
    glVertex3f( .16, -.16, 0 );
    glEnd();
    
    glBegin(GL_POLYGON); //left
    glVertex3f( -.16, -.16, 0 );
    glVertex3f( -.16,  .16, 0 );
    glVertex3f( -.16,  .16, 0 );
    glVertex3f( -.16, -.16, 0 );
    glEnd();
    
    glBegin(GL_POLYGON); //top
    glVertex3f(  .16,  .16, 0 );
    glVertex3f(  .16,  .16, 0 );
    glVertex3f( -.16,  .16, 0 );
    glVertex3f( -.16,  .16, 0 );
    glEnd();
    
    glBegin(GL_POLYGON); //bottom
    glVertex3f(  .16, -.16, 0 );
    glVertex3f(  .16, -.16, 0 );
    glVertex3f( -.16, -.16, 0 );
    glVertex3f( -.16, -.16, 0 );
    glEnd();
    
    glPopMatrix();
    glEndList();
    //END monitorScreen
    
    
    monitorBase = glGenLists(1);
    glNewList(monitorBase, GL_COMPILE);
    glPushMatrix();
    glTranslatef(.2, 0.05, -.05);
    glColor3f(0.93, 0.9, 0.75);

    glBegin(GL_POLYGON); //front
    glVertex3f(  .1, -.05, -.1 );
    glVertex3f(  .1,  .05, -.1);
    glVertex3f( -.1,  .05, -.1 );
    glVertex3f( -.1, -.05, -.1 );
    glEnd();
    
    glBegin(GL_POLYGON); //back
    glVertex3f(  .1, -.05, .1 );
    glVertex3f(  .1,  .05, .1 );
    glVertex3f( -.1,  .05, .1 );
    glVertex3f( -.1, -.05, .1 );
    glEnd();
    
    glBegin(GL_POLYGON); //right
    glVertex3f( .1, -.05, -.1 );
    glVertex3f( .1,  .05, -.1 );
    glVertex3f( .1,  .05,  .1 );
    glVertex3f( .1, -.05,  .1 );
    glEnd();
    
    glBegin(GL_POLYGON); //left
    glVertex3f( -.1, -.05,  .1 );
    glVertex3f( -.1,  .05,  .1 );
    glVertex3f( -.1,  .05, -.1 );
    glVertex3f( -.1, -.05, -.1 );
    glEnd();
    
    glBegin(GL_POLYGON); //top
    glVertex3f(  .1,  .05,  .1 );
    glVertex3f(  .1,  .05, -.1 );
    glVertex3f( -.1,  .05, -.1 );
    glVertex3f( -.1,  .05,  .1 );
    glEnd();
    
    glBegin(GL_POLYGON); //bottom
    glVertex3f(  .1, -.05, -.1 );
    glVertex3f(  .1, -.05,  .1 );
    glVertex3f( -.1, -.05,  .1 );
    glVertex3f( -.1, -.05, -.1 );
    glEnd();
    
    glPopMatrix();
    glEndList();
    //END monitorBase
    
    
    topMonitor = glGenLists(1);
    glNewList(topMonitor, GL_COMPILE);
    glPushMatrix();
    glTranslatef(.2, 0.6, -.12);
    glColor3f(0.68, 0.68, 0.68);
    
    glBegin(GL_POLYGON); //front
    glVertex3f(  .1, -.1, -.075 );
    glVertex3f(  .1,  .1, -.075 );
    glVertex3f( -.1,  .1, -.075 );
    glVertex3f( -.1, -.1, -.075 );
    glEnd();
    
    glBegin(GL_POLYGON); //back
    glVertex3f(  .1, -.1, .075 );
    glVertex3f(  .1,  .1, .075 );
    glVertex3f( -.1,  .1, .075 );
    glVertex3f( -.1, -.1, .075 );
    glEnd();
    
    glBegin(GL_POLYGON); //right
    glVertex3f( .1, -.1, -.075 );
    glVertex3f( .1,  .1, -.075 );
    glVertex3f( .1,  .1,  .075 );
    glVertex3f( .1, -.1,  .075 );
    glEnd();
    
    glBegin(GL_POLYGON); //left
    glVertex3f( -.1, -.1,  .075 );
    glVertex3f( -.1,  .1,  .075 );
    glVertex3f( -.1,  .1, -.075 );
    glVertex3f( -.1, -.1, -.075 );
    glEnd();
    
    glBegin(GL_POLYGON); //top
    glVertex3f(  .1,  .1,  .075 );
    glVertex3f(  .1,  .1, -.075 );
    glVertex3f( -.1,  .1, -.075 );
    glVertex3f( -.1,  .1,  .075 );
    glEnd();
    
    glBegin(GL_POLYGON); //bottom
    glVertex3f(  .1, -.1, -.075 );
    glVertex3f(  .1, -.1,  .075 );
    glVertex3f( -.1, -.1,  .075 );
    glVertex3f( -.1, -.1, -.075 );
    glEnd();
    
    glPopMatrix();
    glEndList();
    //END monitorBase
    
}

void specialKeys( int key, int x, int y ) {
    
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 5;
    
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 5;
    
    else if (key == GLUT_KEY_UP)
        rotate_x += 5;
    
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;
    
    glutPostRedisplay();
    
}

void resize(int w, int h) {
    glViewport (0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-10.0, 10.0, -10.0, 10.0, 5.0, 250.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[]) {
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Assignment 6");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutSpecialFunc(specialKeys);
    
    setup();
    glutMainLoop();
    
    return 0;
    
}
