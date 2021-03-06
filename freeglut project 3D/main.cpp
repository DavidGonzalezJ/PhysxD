#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <GL/freeglut.h>
#include <windows.h>
#include <vector>
#include <iostream>
#include "particulas.h"
#include "Test0.h"
#include "Test1.h"
#include "Test2.h"
#include "Test3.h"
#include "Test4.h"
#include "Test5.h"
#include "Test7.h"

//#include <GL/glut.h>
using namespace std;

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
int WIDTH= 1000, HEIGHT= 1000;

GLfloat dameRandom(GLfloat max, GLfloat min);

bool pausa = false;
// Viewing frustum parameters
GLdouble xRight=10, xLeft=-xRight, yTop=250, yBot=-30, N=1, F=2000;

// Camera parameters
GLdouble eyeX=200, eyeY=100, eyeZ=200;
GLdouble lookX=0.0, lookY=0.0, lookZ=0.0;
GLdouble upX=0, upY=1, upZ=0;

// Scene variables
GLfloat angX, angY, angZ; 
std::vector<particulas> esferas;
GLfloat frecuencia= 10;
GLfloat lastUpdate = 0;

Test0 escena0;
Test1 escena1;
Test2 escena2;
//Test3 escena3;
Test4 escena4;
Test7 escena6;
Test5* escena5;


int numEscenas = 1;
int CONT = 0;

void buildSceneObjects() {	 
    angX=0.0f;
    angY=0.0f;
    angZ=0.0f;	
	//creaParticulas(1000);
	//escena.creaParticulas(1000);
	//escena2.creaParticulas(1000);
	escena5 = new Test5();


}

void initGL() {	 		 
	glClearColor(0,0.2,0.4,1.0);
      
	glEnable(GL_COLOR_MATERIAL);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.9f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	buildSceneObjects();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Light0
	glEnable(GL_LIGHTING);  
    glEnable(GL_LIGHT0);
    GLfloat d[]={0.7f,0.5f,0.5f,1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
    GLfloat a[]={0.3f,0.3f,0.3f,1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, a);
	GLfloat s[]={1.0f,1.0f,1.0f,1.0f};
    glLightfv(GL_LIGHT0, GL_SPECULAR, s);
	GLfloat p[]={25.0f, 25.0f, 25.0f, 1.0f};	 
	glLightfv(GL_LIGHT0, GL_POSITION, p);

	// Camera set up
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ);

	// Frustum set up
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
	glFrustum(xLeft, xRight, yBot, yTop, N, F);
	//glOrtho(xLeft, xRight, yBot, yTop, N, F);

	// Viewport set up
    glViewport(0, 0, WIDTH, HEIGHT);  	
 }

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
	 
	glMatrixMode(GL_MODELVIEW);	 
	glPushMatrix();	 
		// Rotating the scene
		glRotatef(angX, 1.0f, 0.0f, 0.0f);
        glRotatef(angY, 0.0f, 1.0f, 0.0f);
        glRotatef(angZ, 0.0f, 0.0f, 1.0f);
		
		glLineWidth(1.5f);
		// Drawing axes
		glBegin( GL_LINES );			
			glColor3f(1.0,0.0,0.0); 
			glVertex3f(0, 0, 0);
			glVertex3f(200, 0, 0);	     
	 
			glColor3f(0.0,1.0,0.0); 
			glVertex3f(0, 0, 0);
			glVertex3f(0, 200, 0);	 
	 
			glColor3f(0.0,0.0,1.0); 
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 200);	     
		glEnd();
		 		
		// Drawing the scene	 		 
		glColor3f(1.0, 1.0, 1.0);

		switch (CONT)
		{
		case 0: escena6.dibuja(); break;
		case 1: escena1.dibuja(); break;
		case 2: escena2.dibuja(); break;
		case 3: escena2.dibuja(); break;
		case 4: escena4.dibuja(); break;
		case 5: escena5->dibuja(); break;


		default:
			break;
		}
		//dibujaParticulas();
		angY += 0.05f;

		
		//escena2.dibuja();
//		glutSolidSphere(6, 50, 60); //Sphere: radius=6, meridians=50, parallels=60
	glPopMatrix();
 
	glFlush();
	glutSwapBuffers();
//	Sleep(10);
	if (!pausa) glutPostRedisplay();
}


void resize(int newWidth, int newHeight) {
	WIDTH= newWidth;
	HEIGHT= newHeight;
	GLdouble RatioViewPort= (float)WIDTH/(float)HEIGHT;
	glViewport (0, 0, WIDTH, HEIGHT) ;
   
	GLdouble SVAWidth= xRight-xLeft;
	GLdouble SVAHeight= yTop-yBot;
	GLdouble SVARatio= SVAWidth/SVAHeight;
	if (SVARatio >= RatioViewPort) {		 
		GLdouble newHeight= SVAWidth/RatioViewPort;
		GLdouble yMiddle= ( yBot+yTop )/2.0;
		yTop= yMiddle + newHeight/2.0;
		yBot= yMiddle - newHeight/2.0;
    }
	else {      
		GLdouble newWidth= SVAHeight*RatioViewPort;
		GLdouble xMiddle= ( xLeft+xRight )/2.0;
		xRight= xMiddle + newWidth/2.0;
		xLeft=  xMiddle - newWidth/2.0;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();   
	glOrtho(xLeft, xRight, yBot, yTop, N, F);
}

void key(unsigned char key, int x, int y){
	bool need_redisplay = true;
	switch (key) {
		case 27:  /* Escape key */
			//continue_in_main_loop = false; // (**)
			//Freeglut's sentence for stopping glut's main loop (*)
			glutLeaveMainLoop (); 
			break;		 
		case 'a': angX=angX+5; break;
		case 'z': angX=angX-5; break; 
		case 's': angY=angY+5; break;
		case 'x': angY=angY-5; break;
		case 'd': angZ=angZ+5; break;
		case 'c': angZ=angZ-5; break; 
		case 9: CONT++; CONT%=numEscenas; break;
		case 'p': pausa = !pausa; break; //parar el movimiento
		case ' ': escena6.lanzaProyectil(); break;
		case 'l': escena6.apagaFuego(); break;
			
	}

	if (need_redisplay)
		glutPostRedisplay();
}
void creaVentana(int argc, char *argv[]){
	srand(static_cast <unsigned> (time(0)));
	int my_window; // my window's identifier

	// Initialization
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	//glutInitWindowPosition (140, 140);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	// Window construction
	my_window = glutCreateWindow("Freeglut 3D-project");

	// Callback registration
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutDisplayFunc(display);

	// OpenGL basic setting
	initGL();

	// Freeglut's main loop can be stopped executing (**)
	// while (continue_in_main_loop) glutMainLoopEvent();

	// Classic glut's main loop can be stopped after X-closing the window,
	// using the following freeglut's setting (*)
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	// Classic glut's main loop can be stopped in freeglut using (*)
	glutMainLoop();
}
int main(int argc, char *argv[]){
	
	do{
		creaVentana(argc, argv);
		CONT++;

	} while (CONT < numEscenas);

	// We would never reach this point using classic glut

	
	return 0;
}

GLfloat dameRandom(GLfloat max, GLfloat min) {
	return min + static_cast <GLfloat> (rand()) / (static_cast <GLfloat> (RAND_MAX / (max - min)));
}
