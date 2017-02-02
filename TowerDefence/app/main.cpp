
#include <windows.h>
#include <GL/freeglut.h>  
#include <stdlib.h>
#include <stdio.h>
#include <boost/smart_ptr.hpp>
#include "Input.hpp"
#include "Timer.hpp"
#include "GameManager.hpp"

boost::shared_ptr<GameManager> gm;
double lastframetime;
int window;

bool keyPressed[30];
bool willPlace; 
int mousePosX, mousePosY; 
float moveX, moveY;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	glutFullScreen(); //FULLSCREEN FUNC.
	lastframetime = currentTime();

	gm.reset(new GameManager());
	gm->init();

	for(int i=0; i<30; i++)
		keyPressed[i]=false;
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.3,0.3,1.0,1.0);
	
	double now = currentTime();
	gm->update(now - lastframetime);
	gm->render();
	lastframetime = now;

	if(keyPressed[KEY_ID_W]==true)      gm->getCam()->moveForward();
	if(keyPressed[KEY_ID_A]==true)      gm->getCam()->moveLeft();
	if(keyPressed[KEY_ID_D]==true)      gm->getCam()->moveRight();
	if(keyPressed[KEY_ID_S]==true)      gm->getCam()->moveBackward();
	if(keyPressed[KEY_ID_SPACE]==true)  gm->getCam()->moveUp();
	if(keyPressed[KEY_ID_C]==true)      gm->getCam()->moveDown();

	glutSwapBuffers();
	glutPostRedisplay();

}

void keyDown(unsigned char key, int x, int y)
{
	switch (key) 
	{
	case 'q':
	case 27:
		glutDestroyWindow(window);
		exit(0);
#ifndef _WIN32
		// Must use this with regular glut, since it never returns control to main().
		exit(0);
#endif
		break;

	case 'w':
		keyPressed[KEY_ID_W] = true;
		break;
	case 'a':
		keyPressed[KEY_ID_A] = true;
		break;
	case 's':
		keyPressed[KEY_ID_S] = true;
		break;
	case 'd':
		keyPressed[KEY_ID_D] = true;
		break;
	case ' ':
		keyPressed[KEY_ID_SPACE] = true;
		break;
	case 'c':
		keyPressed[KEY_ID_C] = true;
		break;

	default:
		glutPostRedisplay();
	}
}

void keyUp(unsigned char key, int x, int y)
{
	switch (key) 
	{
	case 'w':
		keyPressed[KEY_ID_W] = false;
		break;
	case 'a':
		keyPressed[KEY_ID_A] = false;
		break;
	case 's':
		keyPressed[KEY_ID_S] = false;
		break;
	case 'd':
		keyPressed[KEY_ID_D] = false;
		break;
	case ' ':
		keyPressed[KEY_ID_SPACE] = false;
		break;
	case 'c':
		keyPressed[KEY_ID_C] = false;
		break;
	case 'b':
		keyPressed[KEY_ID_B] = false;
		if(!willPlace)
		{
			if(gm->AddTower())
			{
				willPlace = true;
				gm->CurrentTower->setDraw(true);
			}

		}
		break;
	case 'u':
		keyPressed[KEY_ID_U] = false;
		if(!willPlace)
		{
			gm->UpGradeSelected();
		}
		break;

	}
}

void mousePressed(int button, int state, int posX, int posY)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		mousePosX = posX;
		mousePosY = posY;
		keyPressed[MOUSE_LEFT_BUTTON_DOWN] = true;
	}  
	if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
	{
		keyPressed[MOUSE_LEFT_BUTTON_DOWN] = false;
		if(willPlace)
		{
			if(gm->CurrentTower->IsBuildAble())
			{
				gm->CurrentTower->setDraw(false);
				gm->AddTowerDone();
				willPlace = false;

			}
		}
		else
			gm->PickObject(posX,posY);

	}

}

//Detectes the mouse Pos in 3D space
void mouseMoved(int x, int y)
{
	if(willPlace)
	{
		gm->CurrentTower->setDraw(true);

		GLint viewport[4];
		GLdouble modelview[16];
		GLdouble projection[16];
		GLfloat winX, winY, winZ;
		GLdouble posX, posY, posZ;
		siut::Vec3f ret; 
		glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
		glGetDoublev( GL_PROJECTION_MATRIX, projection );
		glGetIntegerv( GL_VIEWPORT, viewport );

		winX = (float)x;
		winY = (float)viewport[3] - (float)y;

		// Read all pixels at given screen XY from the Depth Buffer
		glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ ); //Used for dettecting where is the mouse on the 3d modell 
		gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

		ret[0] = (float)posX;
		ret[1] = (float)posY;
		ret[2] = (float)posZ;
		
		static GLdouble x1, y1, z1, x2, y2, z2, rx, ry;
		siut::Vec3f camPos = gm->getCam()->getPosition(); 

		x1 = ret[0] - camPos[0];
		y1 = ret[1] - camPos[1];
		z1 = ret[2] - camPos[2];

		gm->CurrentTower->setPos(siut::Vec3f(x1,y1,z1));
	}

}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, float(w)/float(h) ,1.0f, 3000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10.0, 10.0, 10.0,     10.0, 5.0, 0.0,    0.0, 1.0, 0.0);


}

int main(int argc, char** argv)
{
	MessageBox(GetActiveWindow(),(LPCWSTR)L"Hello and welcome to 3D Tower Defense MADNESS!!!!",(LPCWSTR)L"The game will begin right after a short message.", MB_OK | MB_ICONQUESTION );
	MessageBox(GetActiveWindow(),(LPCWSTR)L"Here are the controls for the Game: \n\n B- Buy Tower!. That would cost u 20 Gold. \n\n U- Upgrade Selected Tower! That would cost 30 \n\n Click to select and diselect Towers \n [W,S,A,D]- Camera Movement \n [C,Space]- Camera Up and Down  \n That is All, \n Now Enjoy \n and GET READY!!! \n The game is not going to wait for you!!!!  \n\n\n Author: Nasser Ukla ", (LPCWSTR)L"3D Tower Defence MADNESS!!!", MB_OK | MB_ICONQUESTION );
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(700, 700); 
	glutInitWindowPosition(10, 10);
	window = glutCreateWindow("Tower Defence 3D by Nasser Ukla");
	init();
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mousePressed);
	//glutMotionFunc(mouseMoved);
	glutPassiveMotionFunc(mouseMoved);
	// Add other callback functions here..
	
	
	glutMainLoop();
	return 0;
}
