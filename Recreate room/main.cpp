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
static unsigned int table, bottomMachine, topMachine, cokeCan, keyboard, monitor;

using namespace std;

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
    

    //Move to position & draw coke can
    glPushMatrix();
    glRotatef(270, 1, 0, 0);
    glTranslatef(-0.35, 0.45, 0.025);
    glScalef(0.1, 0.1, 0.1);
    glCallList(cokeCan);
    glPopMatrix();
    
    //Draw table legs
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
    table = glGenLists(1);
    glNewList(table, GL_COMPILE);
    glPushMatrix();
    glColor3f(1, 0, 0);

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
    glColor3f(0, 1, 0);

    glBegin(GL_POLYGON); //front
    glVertex3f(  0.2, -.05, -.4 );
    glVertex3f(  .2,  .05, -.4 );
    glVertex3f( -.2,  .05, -.4 );
    glVertex3f( -.2, -.05, -.4 );
    glEnd();
    
    glBegin(GL_POLYGON); //back
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
    glColor3f(1, 0, 0);

    glBegin(GL_POLYGON); //front
    glVertex3f(  0.2, -.05, -.4 );
    glVertex3f(  .2,  .05, -.4 );
    glVertex3f( -.2,  .05, -.4 );
    glVertex3f( -.2, -.05, -.4 );
    glEnd();
    
    glBegin(GL_POLYGON); //back
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
    glColor3f(0, 0, 10);
    
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
    glColor3f(1, 1, 1); //so you can see the tilt

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
