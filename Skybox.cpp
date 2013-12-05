#include "Skybox.h"



void initSkybox(void)
{
/*
SKY_FRONT 0
SKY_RIGHT 1
SKY_LEFT 2
SKY_BACK 3
SKY_UP 4
SKY_DOWN 5

skybox[SKY_FRONT] = SDL_LoadBMP("../textures/txStormydays_front.bmp");
skybox[SKY_RIGHT] = loadTexBMP("../textures/txStormydays_right.bmp");
skybox[SKY_LEFT] = loadTexBMP("../textures/txStormydays_left.bmp");
skybox[SKY_BACK] = loadTexBMP("../textures/txStormydays_back.bmp");
skybox[SKY_UP] = loadTexBMP("../textures/txStormydays_up.bmp");
skybox[SKY_DOWN] = loadTexBMP("../textures/txStormydays_down.bmp");
*/
}

void drawSkybox(double D, int* skybox)
{
//glColor3fv(white);
glEnable(GL_TEXTURE_2D);
 
/* Sides */
glBindTexture(GL_TEXTURE_2D,skybox[SKY_RIGHT]);
glBegin(GL_QUADS);
glTexCoord2f(0,0); glVertex3f(-D,-D,-D);
glTexCoord2f(1,0); glVertex3f(+D,-D,-D);
glTexCoord2f(1,1); glVertex3f(+D,+D,-D);
glTexCoord2f(0,1); glVertex3f(-D,+D,-D);
glEnd();
glBindTexture(GL_TEXTURE_2D,skybox[SKY_FRONT]);
glBegin(GL_QUADS);
glTexCoord2f(0,0); glVertex3f(+D,-D,-D);
glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
glTexCoord2f(0,1); glVertex3f(+D,+D,-D);
glEnd();
glBindTexture(GL_TEXTURE_2D,skybox[SKY_LEFT]);
glBegin(GL_QUADS);
glTexCoord2f(0,0); glVertex3f(+D,-D,+D);
glTexCoord2f(1,0); glVertex3f(-D,-D,+D);
glTexCoord2f(1,1); glVertex3f(-D,+D,+D);
glTexCoord2f(0,1); glVertex3f(+D,+D,+D);
glEnd();
glBindTexture(GL_TEXTURE_2D,skybox[SKY_BACK]);
glBegin(GL_QUADS);
glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
glTexCoord2f(1,0); glVertex3f(-D,-D,-D);
glTexCoord2f(1,1); glVertex3f(-D,+D,-D);
glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
glEnd();
 
/* Top and Bottom */
glBindTexture(GL_TEXTURE_2D,skybox[SKY_UP]);
glBegin(GL_QUADS);
glTexCoord2f(0,0); glVertex3f(-D,+D,-D);
glTexCoord2f(1,0); glVertex3f(+D,+D,-D);
glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
glEnd();
glBindTexture(GL_TEXTURE_2D,skybox[SKY_DOWN]);
glBegin(GL_QUADS);
glTexCoord2f(1,1); glVertex3f(+D,-D,-D);
glTexCoord2f(0,1); glVertex3f(-D,-D,-D);
glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
glEnd();
 
glDisable(GL_TEXTURE_2D);
}