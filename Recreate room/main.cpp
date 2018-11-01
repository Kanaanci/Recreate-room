#include <cstdlib>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include<vector>

#ifdef __APPLE__
//#  include <GL/glew.h>
#  include <GLUT/GLUT.h>
#  include <OpenGL/glext.h>
#else
//#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
//#pragma comment(lib, "glew32.lib")
#endif

#define PI 3.14159265

double rotate_y=0;
double rotate_x=0;
static unsigned int table;
static unsigned int bottomMachine;


void display() {
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    // Reset transformations
    glLoadIdentity();
    
    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    
    // Other Transformations
    // glScalef( 2.0, 2.0, 0.0 );          // Not included
    
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
//    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); //To turn off wireframe
    
    glCallList(table);
    glCallList(bottomMachine);

    
    glFlush();
    glutSwapBuffers();
    
}

void setup() {
    table = glGenLists(1);
    glNewList(table, GL_COMPILE);
    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    
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
    
    bottomMachine = glGenLists(1);
    glNewList(bottomMachine, GL_COMPILE);
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(-.38,.075,.38);
    
    glBegin(GL_POLYGON); //front
    glVertex3f(  0.1, -.05, -.1 );
    glVertex3f(  .1,  .05, -.1 );
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

    glEnd();
    
    glPopMatrix();
    glEndList();
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
