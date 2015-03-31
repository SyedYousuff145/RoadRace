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
   glRectf(2.0, 10.0, -2.0, -10.0);
   glRectf(-8.0, 12.0, 8.0, 13.0);
   glRectf(-10.0, 9.0, -8.0, 15.0);
   glRectf(8.0, 9.0, 10.0, 15.0);
   glBegin(GL_LINES);
	glVertex2f(8.0,11.0);
	glVertex2f(6.0,7.0);
	glVertex2f(6.0,7.0);
	glVertex2f(6.0,-7.0);
	glVertex2f(6.0,-7.0);
	glVertex2f(10.0,-12.0);
	glVertex2f(-8.0,11.0);
	glVertex2f(-6.0,7.0);
	glVertex2f(-6.0,7.0);
	glVertex2f(-6.0,-7.0);
	glVertex2f(-6.0,-7.0);
	glVertex2f(-10.0,-12.0);
	glVertex2f(10.0,-12.0);
	glVertex2f(-10.0,-12.0);
   glEnd();
    glRectf(-11.0, -16.0, -9.0, -8.0);
    glRectf(9.0, -16.0, 11.0, -8.0);
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
   glutInitWindowSize (250, 250); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 

   glutMainLoop();
   return 0;
}
