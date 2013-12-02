
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <iostream> //C++ I/O
#include <GL/glut.h> 

using namespace std;

//	Constants

const float PI = 3.14159265358979323;
const int ESC = 27;

const float zoomFactor = pow(2, 0.1);
const float yawIncr = 2.0;
const float pitchIncr = 2.0;

//	Globals

int screenWidth = 640;
int screenHeight = 480;

float camDist = 15.0;
float camYaw = 30.0;
float camPitch = 30.0;

float camCenterX = 0.0;
float camCenterY = 0.0;
float camCenterZ = 0.0;
//	Function prototypes

bool lightOn = true;

void updateMouse(int x, int y);
void display();
void reshape(int, int);
void keyboard(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);
void init();
void printInstructions();
void setView();
void drawAxes();
void drawCube();
void mouseClick(int button, int state, int x, int y);

GLuint texture = NULL;

int main(int argc, char* argv[])
{
	screenHeight = 480;
	screenWidth = 640;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Assignment 2");
	glutPassiveMotionFunc(&updateMouse);
	glutMouseFunc(&mouseClick);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);

	init();


	glutMainLoop();
	return 0;
}

void mouseClick(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN)
	{
		if(button ==  GLUT_LEFT_BUTTON)
				camDist /= zoomFactor;
		else if(button == GLUT_RIGHT_BUTTON)		
				camDist *= zoomFactor;
		
		glutPostRedisplay();	
	}
	return;

};


void updateMouse(int x, int y)
{
	//since calling glutWarpPointer will recall updateMouse into an inf loop, this method will not be used yet
		//So center is at screenWidth/2 ScreenHeight/2, if mouse moves, needs to look up or down depending
	
		//camYaw += (x - screenWidth/2);  //move x by amount mouse moved
		//camPitch +=	(y - screenHeight/2); //move y by amount mouse moved from center
		//glutWarpPointer(screenWidth/2, screenHeight/2);  //reset mouse to center, it recalls update mouse... stupid
		//then need to redraw
	
	cout << sin(camYaw * PI/360.0) << endl << endl;
	//this method will calculate the percentage of the mouses location and translate it to 360 degrees. Example|
	//Example: center of screen will be 0degrees while edges are 180
	camYaw = -(360*(((double)x/screenWidth)-.5));
	camPitch = -(360*(((double)y/screenHeight)-.5));
	//cout << camPitch << endl;
	glutPostRedisplay();
	
	return;

	
};



void drawLights()
{
	
    
	//Add point source light
	GLfloat light_Pos[4] = {5.0, 5.0, -10.0, 1.0};   // Positioned at (5.0, 5.0, -10.0)
	GLfloat light_Ka[4] = {0.5, 0.5, 0.5, 1.0};    // ambient light parameters
	//GLfloat light_Kd[4] = {0.8, 0.8, 0.8, 1.0}; // diffuse light parameters
	//GLfloat light_Ks[4] = {0.9, 0.2, 0.9, 1.0};    //specular light parameters
		glLightfv(GL_LIGHT0, GL_POSITION, light_Pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);
}

/*
void loadTexture(GLuint texture_obj, string tFileName) {
SDL_Surface *g_image_surface = NULL; 
const char *fileName = tFileName.c_str();
g_image_surface = IMG_Load(fileName);
glBindTexture(GL_TEXTURE_2D,texture_obj);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
glTexImage2D(GL_TEXTURE_2D, 0, g_image_surface->format->BytesPerPixel,g_image_surface->w, g_image_surface->h,0,GL_RGB,GL_UNSIGNED_BYTE,g_image_surface->pixels);
SDL_FreeSurface(g_image_surface);
}
*/


void init()
{
	glClearColor(0.8, 0.8, 0.8, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL); //allow material to be effected by lighting
	glClearDepth(1.0);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_FOG);
	GLfloat fogColor[4] = {.9, 0.9, 0.9, 1.0};
	glFogi(GL_FOG_MODE, GL_LINEAR );
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_START, 10.0 );
	glFogf(GL_FOG_END, 15.0 );

	glEnable(GL_TEXTURE_2D);
	//loadTexture(texture,"Texture.jpg");
	

	printInstructions();
	return;
}

void printInstructions()
{
	cout << "Lecture 10 Demo 3: Controlling the Camera" << endl << endl;
	
	cout << "Press + to zoom in." << endl;
	cout << "Press - to zoom out." << endl << endl;
	
	cout << "Use the arrow keys to rotate camera left, right, up, and down." << endl << endl;
		
	cout << "To quit, press ESC, then hit any key." << endl;
	
	return;
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	setView();
	drawLights();
	//drawCube();


	

	//to draw array of cubes
	for (int i = 0; i < 5; i++)
	{
		glPushMatrix();
		glTranslatef(-6.5, 0.0, -2.0*i); 
		for (int j = 0; j < 5; j++)
		{
//			glColor3f(1.0 - 0.25*i, 0.5 + 0.125*(i - j), 0.25*j);
			glColor3f(0.25*(i + j - 0.5*i*j), 0.25*j, 0.25*(4 - i - j + 0.25*i*j));
			glTranslatef(2.0, 0.0, 0.0);
			drawCube();
		}
		glPopMatrix();
	}



	glutSwapBuffers();
	return;
}

void reshape(int w, int h)
{
	screenWidth = w;
	screenHeight = h;
	if (w > 0 && h > 0)
	{
	    glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	    gluPerspective(45.0, (float)w/(float)h, 1.0, 1000.0);
		glViewport(0, 0, w, h);
		glutPostRedisplay();
	}
	return;
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'l':
		
		if(lightOn)
			glDisable(GL_LIGHT0);
		else
			glEnable(GL_LIGHT0);

		lightOn = !lightOn;

		break;

		case ESC:
			exit(0);
			break;
		default:
			break;
	}
	glutPostRedisplay();
	return;
}


void specialKeys(int key, int x, int y)
{
	int factor = -1;
	if((sin(camYaw * PI/360.0) > -.90) && (sin(camYaw * PI/360.0) < .45))
					factor = 1;
	switch (key)
	{
		
		//Moving the Scene (change to mouse)
		case GLUT_KEY_LEFT:
			
				
				//if((sin(camYaw * PI/360.0) > -.45) && (sin(camYaw * PI/360.0) < .45))
				//	factor = 1;

				
				camCenterX += factor*(1 - abs(sin(camYaw * PI/180.0)));
				camCenterZ += factor*(1 * abs(sin(camYaw * PI/180.0)));
				break;

		case GLUT_KEY_RIGHT:
				camCenterX -= factor*(1 - abs(sin(camYaw * PI/180.0)));
				camCenterZ -= factor*(1 * abs(sin(camYaw * PI/180.0)));
			break;
		case GLUT_KEY_DOWN:


			camCenterY -=  1 * abs(cos(camPitch * PI/360.0));
			camCenterZ -=  1 - abs(cos(camPitch * PI/360.0));
			break;
		case GLUT_KEY_UP:
			camCenterY +=  1 * abs(cos(camPitch * PI/360.0));
			camCenterZ +=  1 - abs(cos(camPitch * PI/360.0));
			break;
		case GLUT_KEY_PAGE_UP:
			camCenterZ++;
			break;
		case GLUT_KEY_PAGE_DOWN:
			camCenterZ--;
			break;
		default:
			break;
		//Move the Camera (use keyboard)


			//since just camCenterX++ will move righ to relation of board and not
			//to relation of self, we use sin(yawAngleRad) * cos(pitchAngleRad) to find
			//location


	}
	glutPostRedisplay();
	return;
}


void setView()
{
//	Establish the position and orientation of the camera

	float yawAngleRad = camYaw * PI/180.0;
	float pitchAngleRad = camPitch * PI/360.0;
	float camX = camDist * sin(yawAngleRad) * cos(pitchAngleRad);
	float camZ = camDist * cos(yawAngleRad) * cos(pitchAngleRad);
	float camY = camDist * sin(pitchAngleRad);
	//cout << "CamX = " << camX/camDist << endl << "CamY = " << camY/camDist << endl << "CamZ" << camZ/camDist << endl;
	gluLookAt(camCenterX - camX, camCenterY - camY,camCenterZ - camZ, camCenterX, camCenterY, camCenterZ, 0.0, 1.0, 0.0);
	return;
}


void drawAxes()
{
	glBegin(GL_LINES);
	
	//	Draw red x-axis

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(100.0, 0.0, 0.0);

	//	Draw green y-axis

		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 100.0, 0.0);

	//	Draw blue z-axis

		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 100.0);
	
	//	Draw cyan negative x-axis

		glColor3f(0.0, 1.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(-100.0, 0.0, 0.0);

	//	Draw magenta negative y-axis

		glColor3f(1.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, -100.0, 0.0);

	//	Draw yellow negative z-axis

		glColor3f(1.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, -100.0);
	glEnd();
	
	return;
}


void drawCube()
{
	 //glBindTexture(GL_TEXTURE_2D, texture);
	glColor4f(1.0, 1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	
		//glTexCoord2f(1, 1); 
		glVertex3f(0.0, 0.0, 0.0);
		//glTexCoord2f(1, 0);
		glVertex3f(0.0, 1.0, 0.0);
		//glTexCoord2f(0, 0); 
		glVertex3f(1.0, 1.0, 0.0);
		//glTexCoord2f(0, 1); 
		glVertex3f(1.0, 0.0, 0.0);
		
		//glTexCoord2f(1, 1); 
		glVertex3f(0.0, 0.0, 0.0);
		//glTexCoord2f(1, 0);
		glVertex3f(0.0, 0.0, 1.0);
		//glTexCoord2f(0, 0);
		glVertex3f(0.0, 1.0, 1.0);
		//glTexCoord2f(0, 1); 
		glVertex3f(0.0, 1.0, 0.0);
		
		//glTexCoord2f(1, 1);
		glVertex3f(0.0, 0.0, 0.0);
		//glTexCoord2f(1, 0); 
		glVertex3f(1.0, 0.0, 0.0);
		//glTexCoord2f(0, 0);
		glVertex3f(1.0, 0.0, 1.0);
		//glTexCoord2f(0, 1);
		glVertex3f(0.0, 0.0, 1.0);
		
		//glTexCoord2f(1, 1);
		glVertex3f(0.0, 0.0, 1.0);
		//glTexCoord2f(1, 0);
		glVertex3f(0.0, 1.0, 1.0);
		//glTexCoord2f(0, 0);
		glVertex3f(1.0, 1.0, 1.0);
		//glTexCoord2f(0, 1);
		glVertex3f(1.0, 0.0, 1.0);
		
		//glTexCoord2f(1, 1);
		glVertex3f(1.0, 0.0, 0.0);
		//glTexCoord2f(1, 0);
		glVertex3f(1.0, 1.0, 0.0);
		//glTexCoord2f(0, 0);
		glVertex3f(1.0, 1.0, 1.0);
		//glTexCoord2f(0, 1);
		glVertex3f(1.0, 0.0, 1.0);
		
		//glTexCoord2f(1, 1);
		glVertex3f(0.0, 1.0, 0.0);
		//glTexCoord2f(1, 0);
		glVertex3f(0.0, 1.0, 1.0);
		//glTexCoord2f(0, 0);
		glVertex3f(1.0, 1.0, 1.0);
		//glTexCoord2f(0, 1);
		glVertex3f(1.0, 1.0, 0.0);
		
	glEnd();
	
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
		
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(1.0, 1.0, 0.0);
		
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 1.0);
		
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(1.0, 1.0, 0.0);
		
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 1.0, 1.0);
		
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(1.0, 0.0, 1.0);
		
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, 1.0);
		
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(0.0, 1.0, 1.0);
		
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(1.0, 0.0, 1.0);
		
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(1.0, 1.0, 0.0);
	glEnd();
	
	return;
}
