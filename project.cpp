#include<stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#ifdef __WIN64
    #include <windows.h>  //for Sleep() only
    #include<GL/glut.h>
#elif __WIN32
    #include <windows.h>  //for Sleep() only
    #include<GL/glut.h>
#elif __APPLE_CC__
    #include <GLUT/glut.h>
#elif __linux
    #include<GL/glut.h>
#elif __unix
    #include<GL/glut.h>
#endif
#include<limits.h>
#include<unistd.h>
#include<time.h>
#include<math.h>
#include<cstring>
#include<iostream>
#include<vector>


#define MAX_CARS 3

void drawCar();
void drawFootPath();
void drawDivider();
void drawSurroundings();
void stopGame();
void drawOtherCars(int);
void drawOther();
void setCars();
void moveOtherCars();
void detectCollision();
void drawString(std::string);
void drawMainMenu();

int foot_y = 200;
int div_y = 220;
int a = 0;
int speed = 1;
int steerSpeed = 1;

int game_state = 0;

void moveDivider();
void moveRoad();
void moveCar();
void periodicFunction(int);

int lane[MAX_CARS];
int pos[MAX_CARS];
int speeds[MAX_CARS];
int speedsTemp[MAX_CARS];

GLdouble width=1200, height=800;

bool carMoveLeft = false, carMoveRight = false, carMoveFast = false, carStopped = false, gameStopped = false, horn = false;
bool highlightStart = false, highlightExit = false;
//Car variables
int car_x = 0;
int car_y = -100;

void maindisp()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

    switch(game_state)
	{
        case 1 : glClearColor(0.5, 0.5, 0.5, 0.0);
                 drawFootPath();
                 drawSurroundings();
                 drawDivider();
                 drawCar();
                 drawOther();
                 break;

        case 0 : glClearColor(0.0, 0.0, 0.0, 0.0);
                 drawMainMenu();

                 break;
	}

	glFlush();
	glutSwapBuffers();
}

void keyBoardFunc(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT : carMoveLeft = true; carMoveRight = false; break;
		case GLUT_KEY_RIGHT : carMoveRight = true; carMoveLeft = false; break;
		case GLUT_KEY_UP 	: carMoveFast = true; break;
		case GLUT_KEY_DOWN : if(gameStopped) {speed = 2; steerSpeed = 1; gameStopped = false;}; break;
	}
}

void keyboard_up_func(int k, int x, int y)
{
    switch(k)
    {
        case GLUT_KEY_LEFT: carMoveLeft=false;
                            break;
        case GLUT_KEY_RIGHT:carMoveRight=false;
                            break;

		case GLUT_KEY_UP : carMoveFast = false; break;
		case GLUT_KEY_DOWN : carStopped = false; break;
    }
}

void normalKeyBoardFunc(unsigned char key, int x, int y)
{
    switch(key)
    {
        //Horn
        case 'H':
        case 'h': horn = true; break;

    }
}

void mouse_func(int button, int state, int x, int y)
{
    switch(game_state)
    {
        case 0 : if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
                 {
                    if(x >=  630 && x <= 810 && y >= 320 && y <= 405)
                    {
                        //gameStopped = false;
                        setCars();
                        game_state = 1;
                    }

                    else if(x >=  630 && x <= 810 && y >= 490 && y <= 575)
                        game_state = 2;
                 }
                 break;

    }
}

void mouse_hover(int x, int y)
{
        if(x >=  630 && x <= 810 && y >= 320 && y <= 405)
        {
            highlightStart = true;
            highlightExit = false;
        }

        else if(x >=  630 && x <= 810 && y >= 490 && y <= 575)
        {
            highlightStart = false;
            highlightExit = true;
        }

        else
        {
            highlightExit = false;
            highlightStart = false;
        }
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize((int) width, (int) height);
	glutCreateWindow("Galaxian");
	glutFullScreen();


	gluOrtho2D(-240.0, 240.0, -160.0, 160.0);

	glutDisplayFunc(maindisp);
	glutTimerFunc(100, periodicFunction, 0);

    glutSpecialFunc(keyBoardFunc);
    glutSpecialUpFunc(keyboard_up_func);
    glutKeyboardFunc(normalKeyBoardFunc);
    glutMouseFunc(mouse_func);
    glutPassiveMotionFunc(mouse_hover);

	glutMainLoop();
	return 0;
}

//This function draws a car at (car_x, car_y)
void drawCar(void)
{
    glPushMatrix();

    glTranslated(car_x, car_y, 0.0);

    glColor3f(0.34, 1.0, 1.0);

    glRectd(2, 10, -2, -10);
    glRectf(-8, 12, 8, 13);
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
    glRectf(-7.0, -14.0, -5.0, -12.0);
    glRectf(5.0, -14.0, 7.0, -12.0);

    glBegin(GL_POINTS);
        glVertex2f(-7,-15);
        glVertex2f(-5,-15);
        glVertex2f(-8,-16);
        glVertex2f(-4,-16);
        glVertex2f(-6,-16);
        glVertex2f(-6,-17);
    glEnd();

	glPopMatrix();
}

void drawOtherCars(int i)
{
    glPushMatrix();

    glTranslated((lane[i] - 1)*37, pos[i], 0.0);

    switch(speeds[i])
    {
        case 2 : glColor3f(0.0, 1.0, 0.0); break;
        case 3 : glColor3f(0.0, 0.0, 1.0); break;
        case 4 :
        case 5 :
        case 6:
        case 7 : glColor3f(1.0, 0.0, 0.0); break;
        case 0 : glColor3f(0.0, 0.0, 0.0); break;
    }

    glRectd(2, 10, -2, -10);
    glRectf(-8, 12, 8, 13);
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
    glRectf(-7.0, -14.0, -5.0, -12.0);
    glRectf(5.0, -14.0, 7.0, -12.0);

    glBegin(GL_POINTS);
        glVertex2f(-7,-15);
        glVertex2f(-5,-15);
        glVertex2f(-8,-16);
        glVertex2f(-4,-16);
        glVertex2f(-6,-16);
        glVertex2f(-6,-17);
    glEnd();

	glPopMatrix();
}

void drawFootPath()
{
	int i, y;
	glPushMatrix();

	//Draw right side foot path
	glTranslated(60, 0, 0);
	y = foot_y + 20;

	for(i = 0; i < 20; i++)
	{
		if(a == 0)
		{
			if(i % 2 == 0)
				glColor3f(1.0, 1.0, 1.0);
			else
				glColor3f(0.0, 0.0, 0.0);
		}

		else
		{
			if(i % 2 == 1)
				glColor3f(1.0, 1.0, 1.0);
			else
				glColor3f(0.0, 0.0, 0.0);
		}


		y -= 20;
		glRectd(5, y, -5, y - 20);
	}
	glPopMatrix();

	//Draw left side foot path
	glPushMatrix();
	glTranslated(-60, 0, 0);

	y = foot_y + 20;
	for(i = 0; i < 20; i++)
	{

		if(a == 0)
		{
			if(i % 2 == 0)
				glColor3f(1.0, 1.0, 1.0);
			else
				glColor3f(0.0, 0.0, 0.0);
		}

		else
		{
			if(i % 2 == 1)
				glColor3f(1.0, 1.0, 1.0);
			else
				glColor3f(0.0, 0.0, 0.0);
		}

		y -= 20;
		glRectd(5, y, -5, y - 20);
	}
	glPopMatrix();

}

void drawDivider()
{
	int i;
	int y = div_y + 80;
	glColor3f(1.0, 1.0, 1.0);

	//Draw left divider

	for(i = 0 ; i < 8; i++)
	{
		y-=80;
		glRectd(22, y, 18, y-40);
		glRectd(-18, y, -22, y-40);
	}

}

void drawSurroundings()
{
	glColor3f(0.0, 1.0, 0.0);
	glRectd(240, 160, 65, -160);
	glRectd(-240, 160, -65, -160);
}

void stopGame()
{
	speed = 0;
	steerSpeed = 0;
}

void resumeGame()
{
    speed = 2;
    steerSpeed = 1;
}

void drawOther()
{
	int i;
	for(i = 0; i < MAX_CARS; i++)
	{
		drawOtherCars(i);
	}
}

void setCars()
{
	int i;
	for(i = 0; i < MAX_CARS; i++)
	{
		lane[i] = i;
		pos[i] = 110 + rand()%100;
        speeds[i] = 1 + i + rand()%4;
	}
}

void moveDivider()
{
	div_y -= speed;
	if(div_y < 120)
		div_y = 200;
}

void moveCar()
{
	if(carMoveLeft)
		car_x -= steerSpeed;


	else if(carMoveRight)
		car_x += steerSpeed;

	if(car_x > 45 || car_x < -45)
		gameStopped = true;
}

void moveRoad()
{
	foot_y -= speed;
	if(foot_y < 160)
	{
		foot_y = 180;
		if(a == 0)
			a = 1;
		else
			a = 0;
	}
}

void periodicFunction(int v)
{
    if(gameStopped)
        stopGame();

    else
        resumeGame();

	if(speed != 0)
	{
		if(carMoveFast)
			speed = 6;

		else
			speed = 2;
	}

	moveRoad();
	moveDivider();
	moveCar();
    moveOtherCars();
    detectCollision();
	glutPostRedisplay();
	glutTimerFunc(10, periodicFunction, v);
}

void moveOtherCars()
{
    int i;
    for(i = 0; i < MAX_CARS; i++)
    {
        pos[i] += -speed + speeds[i];

        if(pos[i] < -200 || pos[i] > 200)
        {
            pos[i] = 200 + rand()%100;
            speeds[i] = 2 + rand()%4;
        }
        //if((speeds[0] == speeds[1]) && (speeds[1] == speeds[2]))
          //  speeds[1]--;

    }

    if(horn)
    {
        speeds[(car_x + 60)/40]++;
        if(speeds[(car_x + 60)/40] > 7)
            speeds[(car_x + 60)/40] = 7;
        horn = false;
    }
}

void detectCollision()
{
    if(game_state != 1)
        return;

    int i, limit;
    for(i = 0; i < MAX_CARS; i++)
    {
        if(pos[i] < -70 && pos[i] > -130)
        {
            limit = (i - 1)*40;
            if(car_x < limit + 22 && car_x > limit - 22)
            {
                speeds[i] = 0;
                gameStopped = true;
            }
        }
    }

}

void draw_string(std::string str)
{
    for(unsigned int i=0;i<str.length();i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *(str.begin()+i));
    }
}

void drawMainMenu()
{
    //Draw start button
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    drawFootPath();
    drawSurroundings();
    drawDivider();
    drawCar();

    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(0, 30, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(30, 15);
        glVertex2f(30, -15);
        glVertex2f(-30, -15);
        glVertex2d(-30, 15);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-20, 30, 0);
    glScalef(0.1, 0.1, 0.1);
    glColor3f(1.0, 1.0, 1.0);
    draw_string("START");

    glPopMatrix();

    //Draw exit button
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    glTranslated(0, -30, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(30, 15);
        glVertex2f(30, -15);
        glVertex2f(-30, -15);
        glVertex2d(-30, 15);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-15, -30, 0);
    glScalef(0.1, 0.1, 0.1);
    draw_string("EXIT");

    glPopMatrix();

    if(highlightStart)
    {
        glColor3f(1.0, 0.0, 0.0);

        glPushMatrix();
        glTranslated(0, 30, 0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(35, 20);
            glVertex2f(35, -20);
            glVertex2f(-35, -20);
            glVertex2d(-35, 20);
        glEnd();
        glPopMatrix();

    }

    if(highlightExit)
    {
        glColor3f(1.0, 0.0, 0.0);

        glPushMatrix();
        glTranslated(0, -30, 0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(35, 20);
            glVertex2f(35, -20);
            glVertex2f(-35, -20);
            glVertex2d(-35, 20);
        glEnd();
        glPopMatrix();

    }




}
