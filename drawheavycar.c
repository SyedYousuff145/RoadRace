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

   glRectf(0.0, 0.0, 6.0, 4.0);
   glBegin(GL_POLYGON);
	glVertex2f(0.0, 0.0);
	glVertex2f(6.0, 0.0);
	glVertex2f(5.0, -1.0);
	glVertex2f(1.0, -1.0);
   glEnd();
   glRectf(1.0, -4.0, 5.0, -1.0);
   glBegin(GL_POLYGON);
	glVertex2f(1.0, -4.0);
	glVertex2f(5.0, -4.0);
	glVertex2f(5.5, -5.0);
	glVertex2f(0.5, -5.0);
   glEnd();
   glRectf(0.5, -6.0, 5.5, -5);
   
   glBegin(GL_LINES);
	glVertex2f(0.0, -5.5);
	glVertex2f(0.5, -5.5);
	glVertex2f(5.5, -5.5);
	glVertex2f(6.0, -5.5);
	glVertex2f(-1.0, 2.0);
	glVertex2f(0.0, 2.0);
	glVertex2f(6.0, 2.0);
	glVertex2f(7.0, 2.0);
   glEnd();
   
   
   glRectf(-0.5, -6.0, 0.0, -5.0);
   glRectf(6.0, -6.0, 6.5, -5.0);

/*   glBegin(GL_LINES);
	glVertex2f(0.0,0.0);
	glVertex2f(0.0, 2.0);
	
	glVertex2f(0.0, 2.0);
	glVertex2f(2.0, 2.0);

	glVertex2f(2.0, 2.0);
	glVertex2f(2.0, 0.0);
   glEnd();
*/
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
