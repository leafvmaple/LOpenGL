//
//  main.cpp
//  LOpenGL
//
//  Created by LeafMaple on 2018/06/14.
//  Copyright © 2018 LeafMaple. All rights reserved.
//

#ifdef __APPLE__
#include <glut/glut.h>
#else
#include <gl/glut.h>
#endif

#include <GLUT/GLUT.h>
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();
    glFlush();
}
int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("LOpenGL");
    glutDisplayFunc(display);
    glutMainLoop();
}
