#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

static GLfloat spin = 0.0;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glPushMatrix();
   
   glColor3f(0.34, 1.0, 1.0);
   glRectf(-4.0, 6.0, 4.0, 6.5);
   glRectf(-5.0, 4.5, -4.0, 7.5);
   glRectf(4.0, 4.5, 5.0, 7.5);
   glColor3f(0.34, 0.0, 1.0);
   glBegin(GL_POLYGON);
	glVertex2f(-3.0,3.5);
	glVertex2f(-4.0, 6.0);
	glVertex2f(4.0, 6.0);
        glVertex2f(3.0,3.5);
   glEnd();

  glBegin(GL_POLYGON);
	glVertex2f(-4.5, -6.0);
	glVertex2f(-3.0,-3.5);
	glVertex2f(3.0,-3.5);
	glVertex2f(4.5, -6.0);
   glEnd();
  glBegin(GL_POLYGON);
	glVertex2f(-3.0,-3.5);
	glVertex2f(-3.0,3.5);
	glVertex2f(3.0,3.5);
	glVertex2f(3.0,-3.5);
  glEnd();

   
    
    glColor3f(0.34, 1.0, 1.0);
    glRectf(1.0, 5.0, -1.0, -5.0);
    glRectf(-5.5, -8.0, -4.5, -4.0);
    glRectf(4.5, -8.0, 5.5, -4.0);
    glRectf(-3.5, -7.0, -2.5, -6.0);
    glRectf(2.5, -7.0, 3.5, -6.0);
   glBegin(GL_POINTS);
        glVertex2f(-3.5,-7.5);
        glVertex2f(-3.5,-7.5);
        glVertex2f(-4,-8);
        glVertex2f(-2,-8);
        glVertex2f(-3,-8);
        glVertex2f(-3,-8.5);
   glEnd(); 
   glPopMatrix();
   glutSwapBuffers();
}


void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}



/* 
 *  Request double buffer display mode.
 *  Register mouse input callback functions
 */
 int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (300, 300); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 

   glutMainLoop();
   return 0;
}
