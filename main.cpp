
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iostream> //C++ I/O
#include <vector>
#include "Model.h"
#include "Skybox.h"
#include "Consts.h"  //all glut inc
#include "Bunny.h"
#include "FloorMap.h"
#include "Firework.h"
#include <math.h>
#include "SuperMap.h"
#include <ctime>

using namespace std;

//	Constants
#define PI 3.1415265359
const int ESC = 27;



const float zoomFactor = pow(2, 0.1);
const float yawIncr = 2.0;
const float pitchIncr = 2.0;
static const float CAM_MOVE = .1f;
static float ZOOM_SPEED_FACTOR = 1;
static float MOUSE_SENSITIVITY = .01f;
static float ZOOM_SPEED = 10;
static MousePressed MOUSE_PRESSED = NONE;

static bool DISABLE_MOUSE = false;

//Camera
Vect3 camPos;
Vect3 camLA;
float camRAD;
float HAng;
float VAng;

//Color change 
float colorR = 0.91f; 
float colorB = 0.14f; 
float TreecolorR = 0.5f; 
float TreecolorB = 0.07f; 
float reductionR;
float reductionG;
float reductionB;
//	Globals
int screenWidth = 800;
int screenHeight = 600;

float camDist = 15.0;
float camYaw = 30.0;
float camPitch = 30.0;

float camCenterX = 0.0;
float camCenterY = 0.0;
float camCenterZ = 0.0;


bool lightOn = true;


//Model 
vector<Model> models;
vector<Bunny> bunnies;
vector<Model> carrots;
vector<Model> trees;

//fireworks 
vector<Firework> fireworks; 




//Floor map
//SuperMap Map;
FloorMap TestMap;


//Skybox
GLuint sbTextureId[6]; 

#define SKY_FRONT 0
#define SKY_RIGHT 1
#define SKY_LEFT 2
#define SKY_BACK 3
#define SKY_UP 4
#define SKY_DOWN 5

//Model functions
void loadModels();
void drawModels();

//	Function prototypes
void Update(int value);
void init();
//void glutTimerFunc(unsigned int msecs, void (*func)(int value), int value);
void display();
void UpdateBunnies();
void UpdateFireworks(); 
void setView();
void CamMove(bool foward);
void reshape(int, int);
void updateMouse(int x, int y);
void mouseClick(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);
void printInstructions();
void drawAxes();
void calcCam();
void SpawnCarrot();
void drawFloorMap();
void DrawFireworks(); 
void drawCube();
void drawFloor(int size);
void loadTexture(GLuint texture_obj, const char *tFileName);
void ColiTester();
void Deletes();
void setReductionColorValue(); 
void BringEverythingIntoSkybox();
void MoveToOuterSkybox(Model * t);


GLuint texture = NULL;

int main(int argc, char* argv[])
{
	IntzRand();
	
	 SDL_Init(SDL_INIT_EVERYTHING); 
	screenHeight = 480;
	screenWidth = 640;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Chernobyl Bunnies");
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
		{			
			MOUSE_PRESSED = LEFT;
		}
		else if(button == GLUT_RIGHT_BUTTON)		
		{			
			
			MOUSE_PRESSED = RIGHT;
		} 			
	}else if (state == GLUT_UP)
		MOUSE_PRESSED = NONE;
		
	return;

};

void MouseMoveUpdate()
{
	if(MOUSE_PRESSED != NONE) //A mouse key is pressed during update
	{
		
	CamMove(MOUSE_PRESSED == LEFT);
	
	//cout << camPos.x << "  " << camPos.y << "  " << camPos.z << endl;
	//cout << HAng << "  " << VAng << endl;
	
	}


}

void Update(int value)
{
	MouseMoveUpdate();
	UpdateBunnies();
	ColiTester();
	Deletes();
	UpdateFireworks();
	BringEverythingIntoSkybox();
	setReductionColorValue();	
	glutPostRedisplay();
	glutTimerFunc(REFRESH_TIMER, &Update, value);
};



void UpdateBunnies() //All logic updates for bunny should be done in here
{
	for(vector<Bunny>::iterator it = bunnies.begin(); it != bunnies.end(); ++it) 
		  it->Update();
	
}

void Deletes()
{
	
	for(vector<Bunny>::iterator it = bunnies.begin(); it != bunnies.end(); ++it) 
		if(it->toDelete == true)	
		{
			//bunnies.erase(it);
			//If a bunny needs to be deleted, it is because it exploded into a firework, instead, he will fall to the ground, create a firework and light on this location
			
			Firework firework = Firework((int)(it->GetPowerFactor()*500),it->GetPowerFactor()/2+1);
			
			//Firework firework = Firework();
			firework.BuildFirework(it->location.x,it->location.y,it->location.z);
			fireworks.push_back(firework);

			//bunnies.erase(it);
			it->toDelete = false;
			it->ResetBunny();

		}
		

	for(vector<Model>::iterator it = carrots.begin(); it != carrots.end(); ++it) 
		  if(it->toDelete == true)	
		  {
			  
			//carrots.erase(it);
			  
			  it->location.x = (rand() % (GAME_MAP_BOUND_W - GAME_MAP_BOUND_W_LB)) + GAME_MAP_BOUND_W_LB;
			  it->location.z = (rand() % (GAME_MAP_BOUND_W - GAME_MAP_BOUND_W_LB)) + GAME_MAP_BOUND_W_LB;
			  it->toDelete = false;

		  }

	for(vector<Model>::iterator it = models.begin(); it != models.end(); ++it) 
		  if(it->toDelete == true)		
			models.erase(it);

	//
	//for(vector<Firework>::iterator it = fireworks.end(); it != fireworks.begin();) 
	if(!fireworks.empty())
	for(int i = fireworks.size() - 1; i >= 0; i--)
	{
		if(fireworks[i].IsDead == true)	
		{			
			fireworks.erase(fireworks.begin() + i);
		}
		
	}

}


void UpdateFireworks(){
	if(!fireworks.empty()){
		vector<Firework>::iterator fid; 
		for(fid = fireworks.begin(); fid != fireworks.end(); ++fid){
			fid-> UpdateFirework();
		}
	}
}
void updateMouse(int x, int y)
{
	if(!DISABLE_MOUSE)
	if(x != screenWidth/2 && y != screenWidth/2) //to prevent the infinite loop call caused by glutWarpPointer
	{
     float Hdif = (x - screenWidth/2);  //move x by amount mouse moved
	 float Vdif = (y - screenHeight/2); //move y by amount mouse moved from center
	 
	 HAng += Hdif * MOUSE_SENSITIVITY;
	 VAng -= Vdif * MOUSE_SENSITIVITY;  
	 
	 glutWarpPointer(screenWidth/2, screenHeight/2);  //reset mouse to center, it recalls update mouse... stupid
	 calcCam(); //recalc the cam
	 //then need to redraw
	 glutPostRedisplay();
	}
	
	
	
	return;

	
};

void drawLights()
{
glPushMatrix();
	//glTranslatef(camPos.x, LAND_SIZE, camPos.z);
	glEnable(GL_LIGHT0);
	GLfloat light_Pos0[4] = {camPos.x+LAND_SIZE/2,LAND_SIZE/4, camPos.z-LAND_SIZE/2, 1.0};   // Positioned at (5.0, 5.0, -10.0)
	GLfloat light_Ka0[4] = {0.3f, 0.3f, 0.3f, 1.0};    // ambient light parameters
	GLfloat light_Kd0[4] = {0.5f, 0.5f, 0.5f, 1.0}; // diffuse light parameters
	GLfloat light_Ks0[4] = {1.2f, 1.8f, 1.2f, 1.0};    //specular light parameters
	glLightfv(GL_LIGHT0, GL_POSITION, light_Pos0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks0);
glPopMatrix();
}


void SpawnCarrot()
{
	if(!carrots.empty())
	{
		int thisCarrot = rand() % carrots.size() - 1;
		if(thisCarrot < 0)
			thisCarrot = 0;
		carrots[thisCarrot].location.z = camPos.z;
		carrots[thisCarrot].location.x = camPos.x;		
	}

}

void MoveToOuterSkybox(Model * it)
{

	int d = rand() % 4;
	if(d == 0)
	{
		it->location.x = camPos.x - LAND_SIZE/2;

		int tx = rand() % LAND_SIZE;
		tx -= LAND_SIZE/2;
		tx += camPos.z;
		it->location.z = tx;

		

	} else if (d == 1) {

		it->location.x = camPos.x + LAND_SIZE/2;

		int tx = rand() % LAND_SIZE;
		tx -= LAND_SIZE/2;
		tx += camPos.z;
		it->location.z = tx;

		
	} else if ( d == 2) {

		it->location.z = camPos.z - LAND_SIZE/2 ;

		int tx = rand() % LAND_SIZE;
		tx -= LAND_SIZE/2;
		tx += camPos.x;
		it->location.x = tx;

		


	} else if ( d == 3) {

		it->location.z = camPos.z + LAND_SIZE/2;

		int tx = rand() % LAND_SIZE;
		tx -= LAND_SIZE/2;
		tx += camPos.x;
		it->location.x = tx;

		

	}
	
	

}

void BringEverythingIntoSkybox()
{
	//grabs all models that reached too far out of range of the skybox and replaces them randomly just
	//outisde the skybox
	for(vector<Model>::iterator it = models.begin(); it != models.end(); ++it) 
	{
		square2D a;
		a.x = it->location.x;
		a.y = it->location.z;
		a.size = 1;

		square2D b; //acceptable render square
		b.x = camPos.x - LAND_SIZE/2 - 50;
		b.y = camPos.z - LAND_SIZE/2 - 50;
		b.size = LAND_SIZE + 200; 

		if(!G_BoundCheckSquares(a,b))
		{
			//then this object does not reside in the acceptable render square, place him somewhere randomly
			//around the sky box
			MoveToOuterSkybox(it->retSelf());
		}


	}

	for(vector<Bunny>::iterator it = bunnies.begin(); it != bunnies.end(); ++it)
	{
		square2D a;
		a.x = it->location.x;
		a.y = it->location.z;
		a.size = 1;

		square2D b; //acceptable render square
		b.x = camPos.x - LAND_SIZE/2 - 50;
		b.y = camPos.z - LAND_SIZE/2 - 50;
		b.size = LAND_SIZE + 200; 

		if(!G_BoundCheckSquares(a,b))
		{
			//then this object does not reside in the acceptable render square, place him somewhere randomly
			//around the sky box
			MoveToOuterSkybox(it->retSelf());
		}

	}

	for(vector<Model>::iterator it = trees.begin(); it != trees.end(); ++it) 
	{
		square2D a;
		a.x = it->location.x;
		a.y = it->location.z;
		a.size = 1;

		square2D b; //acceptable render square
		b.x = camPos.x - LAND_SIZE/2 - 50;
		b.y = camPos.z - LAND_SIZE/2 - 50;
		b.size = LAND_SIZE + 200; 

		if(!G_BoundCheckSquares(a,b))
		{
			//then this object does not reside in the acceptable render square, place him somewhere randomly
			//around the sky box
			MoveToOuterSkybox(it->retSelf());
		}
	}

	for(vector<Model>::iterator it = carrots.begin(); it != carrots.end(); ++it) {	  
		square2D a;
		a.x = it->location.x;
		a.y = it->location.z;
		a.size = 1;

		square2D b; //acceptable render square
		b.x = camPos.x - LAND_SIZE/2 - 50;
		b.y = camPos.z - LAND_SIZE/2 - 50;
		b.size = LAND_SIZE + 200; 

		if(!G_BoundCheckSquares(a,b))
		{
			//then this object does not reside in the acceptable render square, place him somewhere randomly
			//around the sky box
			MoveToOuterSkybox(it->retSelf());
		} 
	}




}

void static loadTexture(GLuint texture_obj, const char *tFileName) {
SDL_Surface *g_image_surface = NULL;
g_image_surface = IMG_Load(tFileName);
glBindTexture(GL_TEXTURE_2D, texture_obj);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
glTexImage2D(GL_TEXTURE_2D, 0, g_image_surface->format->BytesPerPixel,g_image_surface->w, g_image_surface->h,0,GL_RGB,GL_UNSIGNED_BYTE,g_image_surface->pixels);
SDL_FreeSurface(g_image_surface);
}

void initSkybox(void)
{
glGenTextures(6,sbTextureId);

G_LoadTexture(sbTextureId[SKY_FRONT],"CherBunnySrc/textures/night.jpg");
//loadTexture(sbTextureId[SKY_FRONT], "CherBunnySrc/textures/night.jpg");
loadTexture(sbTextureId[SKY_RIGHT], "CherBunnySrc/textures/night.jpg");

loadTexture(sbTextureId[SKY_LEFT], "CherBunnySrc/textures/night.jpg");
loadTexture(sbTextureId[SKY_BACK], "CherBunnySrc/textures/night.jpg");
loadTexture(sbTextureId[SKY_UP], "CherBunnySrc/textures/night.jpg");

loadTexture(sbTextureId[SKY_DOWN], "CherBunnySrc/textures/grass.jpg");




}

void drawSkybox(double D)
{
glPushMatrix();
glTranslatef(camPos.x,0,camPos.z); //move the box to the camera
glRotatef(HAng,0.0,1.0,0.0);

glEnable(GL_TEXTURE_2D);
 

//Move the box to follow the char





/* Sides */
glBindTexture(GL_TEXTURE_2D,sbTextureId[0]);
glBegin(GL_QUADS);
glTexCoord2f(0,0); glVertex3f(-D,0,-D);
glTexCoord2f(1,0); glVertex3f(+D,0,-D);
glTexCoord2f(1,1); glVertex3f(+D,+D,-D);
glTexCoord2f(0,1); glVertex3f(-D,+D,-D);
glEnd();


glBindTexture(GL_TEXTURE_2D,sbTextureId[1]);
glBegin(GL_QUADS);
glTexCoord2f(0,0); glVertex3f(+D,0,-D);
glTexCoord2f(1,0); glVertex3f(+D,0,+D);
glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
glTexCoord2f(0,1); glVertex3f(+D,+D,-D);
glEnd();

glBindTexture(GL_TEXTURE_2D,sbTextureId[2]);
glBegin(GL_QUADS);
glTexCoord2f(0,0); glVertex3f(+D,0,+D);
glTexCoord2f(1,0); glVertex3f(-D,0,+D);
glTexCoord2f(1,1); glVertex3f(-D,+D,+D);
glTexCoord2f(0,1); glVertex3f(+D,+D,+D);
glEnd();

glBindTexture(GL_TEXTURE_2D,sbTextureId[3]);
glBegin(GL_QUADS);
glTexCoord2f(0,0); glVertex3f(-D,0,+D);
glTexCoord2f(1,0); glVertex3f(-D,0,-D);
glTexCoord2f(1,1); glVertex3f(-D,+D,-D);
glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
glEnd();

glBindTexture(GL_TEXTURE_2D,sbTextureId[4]);
glBegin(GL_QUADS);
glTexCoord2f(0,0); glVertex3f(-D,+D,-D);
glTexCoord2f(1,0); glVertex3f(+D,+D,-D);
glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
glEnd();

/*
glBindTexture(GL_TEXTURE_2D,sbTextureId[5]);
glBegin(GL_QUADS);
glTexCoord2f(1,1); glVertex3f(+D,0,-D);
glTexCoord2f(0,1); glVertex3f(-D,0,-D);
glTexCoord2f(0,0); glVertex3f(-D,0,+D);
glTexCoord2f(1,0); glVertex3f(+D,0,+D);
glEnd();
*/
glDisable(GL_TEXTURE_2D);
glPopMatrix();

}

//Draw all fireworks 
void DrawFireworks(){
	if(!fireworks.empty()){
		vector<Firework>::iterator fid; 
		for(fid = fireworks.begin(); fid != fireworks.end(); ++fid){
			fid-> DrawFirework();
		}
	}
}

void init()
{
	glutSetCursor(GLUT_CURSOR_NONE);
		//Cam
	camPos.x = (GAME_MAP_BOUND_W + GAME_MAP_BOUND_W_LB) / 2;
	camPos.y = 15;
	camPos.z = (GAME_MAP_BOUND_W + GAME_MAP_BOUND_W_LB) / 2;
	std::cout << "Loading";
	
	//camLA.x = 5;
	//camLA.y = 5;
	//camLA.z = 0;
	
	camRAD = 5;
	HAng = -1.38;
	VAng = .03;
	calcCam();// intz the camLA

	//glClearColor(0.8, 0.8, 0.8, 0.0);
	glEnable(GL_DEPTH_TEST);

	//setup ambient test light
	//GLfloat light_position[] = { LAND_SIZE/2, LAND_SIZE/2, LAND_SIZE/2, 0.0 };
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	TestMap.LoadTexture();
	std::cout << ".";
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	 
	//glEnable(GL_COLOR_MATERIAL); //allow material to be effected by lighting
	glClearDepth(1.0);
	glDepthFunc(GL_LEQUAL);
	std::cout << ".";

	//glEnable(GL_FOG);
	//GLfloat fogColor[4] = {.9, 0.9, 0.9, 1.0};
	//glFogi(GL_FOG_MODE, GL_LINEAR );
	//glFogfv(GL_FOG_COLOR, fogColor);
	//glFogf(GL_FOG_START,35.0 );
	//glFogf(GL_FOG_END, 40.0 );

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	//loadTexture(texture,"Texture.jpg");
	initSkybox();
	
	loadModels();
	std::cout << ".";

	printInstructions();
	glutTimerFunc(50, &Update, 0); //first time calls after some gap in time in order to allow some render time
	return;
}


void printInstructions()
{
	cout << "Welcome to the Game!" << endl << endl;
	
	cout << "Press + to zoom in." << endl;
	cout << "Press - to zoom out." << endl << endl;
	
	cout << "Use the arrow keys to rotate camera left, right, up, and down." << endl << endl;
		
	cout << "To quit, press ESC, then hit any key." << endl;
	
	return;
}

void loadModels(){

	char * objects[4];
	objects[0] = "CherBunnySrc/objs/rabbit.obj";
	objects[1] = "CherBunnySrc/objs/bush.obj";
	objects[2] = "CherBunnySrc/objs/tree.obj";
	objects[3] = "CherBunnySrc/objs/carrot.obj";

	//Load Rabbits
	std::cout << endl << "Loading Rabbits";
	for(int i = 0; i < MaxRabbit; i++){
		
		
		//int x = rand() % 200;
		//int z = rand() % 200;

		int x = (rand() % LAND_SIZE) + camPos.x - LAND_SIZE/2;
		int z = (rand() % LAND_SIZE) + camPos.x - LAND_SIZE/2;
		Bunny temp (objects[0], glm::vec4(x, 0.95f, z, 1.0),1.0);	
		bunnies.push_back(temp);
		std::cout << ".";
	}

	std::cout << endl << "Loading Shrubbery";	
		//Load Bushes
	for(int i = 0; i < MaxBush; i++){
		int x = (rand() % LAND_SIZE) + camPos.x - LAND_SIZE/2;
		int z = (rand() % LAND_SIZE) + camPos.x - LAND_SIZE/2;
		Model temp (objects[1], glm::vec4(x, 0.95f, z, 1.0));	
		models.push_back(temp);
		std::cout << ".";
	}
	
	std::cout << endl << "Loading Trees";	
		//Load Trees
	for(int i = 0; i < MaxTree; i++){
		int x = (rand() % LAND_SIZE) + camPos.x - LAND_SIZE/2;
		int z = (rand() % LAND_SIZE) + camPos.x - LAND_SIZE/2;
		float size = rand() % 10;
		Model temp (objects[2], glm::vec4(x, size, z, 1.0), size);	
		trees.push_back(temp);
		std::cout << ".";
	}
	
	std::cout << endl << "Loading Carrots";
		//Load Carrots
	for(int i = 0; i < MaxCarrot; i++){
			
		
		int x = (rand() % LAND_SIZE) + camPos.x - LAND_SIZE/2;
		int z = (rand() % LAND_SIZE) + camPos.x - LAND_SIZE/2;
		int y = -1.0f;
		//int x = (rand() % LAND_SIZE) - LAND_SIZE/2;
		//int z = (rand() % LAND_SIZE) - LAND_SIZE/2;
		Model temp (objects[3], glm::vec4(x, 0.95f, z, 1.0));	
		carrots.push_back(temp);
		std::cout << ".";
	}
	
}
void setReductionColorValue(){
	if(colorR>=0.9f && colorB>=0.13f){
		reductionB = -0.05f; 
		reductionR = -0.05f; 
	}
	if(colorR<=0 && colorB<=0){
		reductionR = 0.05f; 
		reductionB = 0.05f; 
	}
	colorR += reductionR; 
	colorB += reductionB; 
	TreecolorR += reductionR; 
	TreecolorB += reductionB; 
}
void drawModels(){
	
	for(vector<Model>::iterator it = models.begin(); it != models.end(); ++it) 
	{
	  glColor3f(TreecolorR,0.5f,TreecolorR); 
	  it->Draw();
      glColor3f(1,1,1);
	}

	for(vector<Bunny>::iterator it = bunnies.begin(); it != bunnies.end(); ++it) 
	  it->Draw();

	for(vector<Model>::iterator it = trees.begin(); it != trees.end(); ++it) 
	{
		glColor3f(TreecolorR,0.3f,TreecolorR); 
	  it->Draw();
      glColor3f(1,1,1);

	}

	for(vector<Model>::iterator it = carrots.begin(); it != carrots.end(); ++it) {	  
		glColor3f(colorR,0.5f,colorB); 
	  it->Draw();
	  glColor3f(1,1,1); 
	}
 
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	setView();
	drawLights();
	//drawFloor(LAND_SIZE);
	drawSkybox(LAND_SIZE/2);	
	DrawFireworks();
	drawModels();
	drawFloorMap();
	
/*  //drawCube();
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
*/
	glutSwapBuffers();
	return;
}

void drawFloorMap()
{
	//Map.Draw(camPos.x,camPos.y);
	TestMap.Draw();
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
	case 'p':				
		DISABLE_MOUSE = !DISABLE_MOUSE;
		if(!DISABLE_MOUSE)		
			glutSetCursor(GLUT_CURSOR_NONE);
		else
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

		

		break;

	case 'w':
		VAng += CAM_MOVE;
		break;
	case 's':
		VAng -= CAM_MOVE;			
		break;
	case 'd':
		HAng += CAM_MOVE;
		break;
	case 'a':
		HAng -=CAM_MOVE;
		break;
	case 'q':
		CamMove(true);
		break;
	case 'e':
		CamMove(false);
		break;
	case 'f':
		VAng = 0;
		break;
	case 'r':
		SpawnCarrot();
		break;

	case 'z':
		ZOOM_SPEED_FACTOR += .5f;
		break;
	case 'x':
		ZOOM_SPEED_FACTOR -= .5f;
		if(ZOOM_SPEED_FACTOR < .5f)
			ZOOM_SPEED_FACTOR = .5f;
		break;		
	case 'l':
		
		if(lightOn){
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);

		lightOn = !lightOn;
		}
		else{
		lightOn = !lightOn;
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT3);
		}
		
		glutPostRedisplay();
		break;

		break;

		case ESC:
			//unload();
			exit(0);
			break;
		default:
			break;

		

	}
	calcCam(); 
	glutPostRedisplay();
	return;
}

void CamMove(bool foward)
{
	int mod = 1;
	if(!foward)
		mod = -1;

	//If cam in bounds from this move, then move

	if(G_BoundCheck(camPos.x + ZOOM_SPEED * cos(HAng) * ZOOM_SPEED_FACTOR * mod,GAME_MAP_BOUND_W_LB,GAME_MAP_BOUND_W))
		camPos.x += ZOOM_SPEED * cos(HAng) * ZOOM_SPEED_FACTOR * mod;	

	if(G_BoundCheck(camPos.z + ZOOM_SPEED * cos(HAng) * ZOOM_SPEED_FACTOR * mod,GAME_MAP_BOUND_W_LB,GAME_MAP_BOUND_W))
		camPos.z += ZOOM_SPEED * sin(HAng) * ZOOM_SPEED_FACTOR * mod;

	if(G_BoundCheck(camPos.y + ZOOM_SPEED * cos(VAng) * ZOOM_SPEED_FACTOR * mod,1,GAME_MAP_BOUND_H))
		camPos.y += ZOOM_SPEED * sin(VAng) * ZOOM_SPEED_FACTOR * mod;


	if(camPos.x > GAME_MAP_BOUND_W)
		camPos.x = GAME_MAP_BOUND_W -2;
	if(camPos.z > GAME_MAP_BOUND_W)
		camPos.z = GAME_MAP_BOUND_W - 2;
	if(camPos.y > GAME_MAP_BOUND_H)
		camPos.y = GAME_MAP_BOUND_H - 2; 

	if(camPos.x < GAME_MAP_BOUND_W_LB)
		camPos.x = GAME_MAP_BOUND_W_LB;
	if(camPos.z < GAME_MAP_BOUND_W_LB)
		camPos.z = GAME_MAP_BOUND_W_LB;
	if(camPos.y < 0)
		camPos.y = 3; 
	
	
	std::cout << "cur pos xz y: " << (int)camPos.x << " , " << (int)camPos.z << " , " << (int)camPos.y << endl;

}


void specialKeys(int key, int x, int y)
{
	
	switch (key)
	{
		
		//Moving the Scene (change to mouse)
		case GLUT_KEY_LEFT:
			
				
				//if((sin(camYaw * PI/360.0) > -.45) && (sin(camYaw * PI/360.0) < .45))
				//	factor = 1;

				
				HAng -= CAM_MOVE;
				break;

		case GLUT_KEY_RIGHT:
				HAng += CAM_MOVE;
			break;
		case GLUT_KEY_DOWN:


			VAng -= CAM_MOVE;
			break;
		case GLUT_KEY_UP:
			VAng += CAM_MOVE;
			break;
		case GLUT_KEY_PAGE_UP:
			CamMove(true);
			break;
		case GLUT_KEY_PAGE_DOWN:
			CamMove(false);
			break;
		default:
			break;
		//Move the Camera (use keyboard)


			//since just camCenterX++ will move righ to relation of board and not
			//to relation of self, we use sin(yawAngleRad) * cos(pitchAngleRad) to find
			//location


	}
	calcCam(); 
	glutPostRedisplay();
	return;
}

void calcCam()  //sets camera LA and POS from Ang
{
	camLA.x = camRAD * cos(HAng);
	camLA.z = camRAD * sin(HAng);
	if(VAng > PI/2)
		VAng = PI/2;
	if(VAng < -PI/2)
		VAng = -PI/2;
	camLA.y = camRAD * sin(VAng);
	//cout << "LA: " << camLA.x << " " << camLA.y << " " << camLA.z << endl << " POS:  "  << camPos.x << " " << camPos.y << " " << camPos.z << endl;

}

void ColiTester()
{
	//for_each (myvector.begin(), myvector.end(), myfunction);
	
	if(!bunnies.empty() && !carrots.empty())
	for(vector<Bunny>::iterator bid = bunnies.begin();bid != bunnies.end();++bid)
	{


	for(vector<Model>::iterator cid = carrots.begin();cid != carrots.end();++cid){
		square2D a;
		a.x = bid->location.x - BUNNY_HEIGHT/2;
		a.y = bid->location.z - BUNNY_HEIGHT/2;
		a.size = BUNNY_HEIGHT;
				
		square2D b;
		b.x = cid->location.x - CARROT_SIZE/2;
		b.y = cid->location.z - CARROT_SIZE/2;
		b.size = CARROT_SIZE;

		if(G_BoundCheckSquares(a,b))
		{
			//Bunny has collided with carrot!
			cid->toDelete = true;
			bid->EatCarrot();				
		}
	
	}


	for(vector<Model>::iterator tit = trees.begin();tit != trees.end();++tit){
		square2D a;
		a.x = bid->location.x - BUNNY_HEIGHT/2;
		a.y = bid->location.z - BUNNY_HEIGHT/2;
		a.size = BUNNY_HEIGHT;
				
		square2D b;
		b.x = tit->location.x - 2;
		b.y = tit->location.z - 2;
		b.size = 2;

		if(G_BoundCheckSquares(a,b))
		{
			//Bunny has collided with the tree
			std::cout << "Collided with tree" << std::endl;	
		}
	
	}


	}
}

void setView()
{
//	Establish the position and orientation of the camera
	//cout << "LA: " << camLA.x << " " << camLA.y << " " << camLA.z << endl << " POS:  "  << camPos.x << " " << camPos.y << " " << camPos.z << endl;
	//cout << HAng << " , " << VAng << endl;
	gluLookAt(camPos.x, camPos.y,camPos.z, camLA.x + camPos.x, camLA.y + camPos.y, camLA.z + camPos.z, 0.0, 1.0, 0.0);
	return;
}


void drawFloor(int size){
	glColor3f(0.1f, 0.9f, 0.1f);
	glBegin(GL_QUADS);
	glVertex3f(-size/2, 0, -size/2);
	glVertex3f(-size/2, 0, size/2);
	glVertex3f(size/2, 0, size/2);
	glVertex3f(size/2, 0, -size/2);
	glEnd();
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



