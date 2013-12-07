#include "FloorMap.h"


FloorMap::FloorMap()
{
	//Create array
	floorMap = new Floor[FLOOR_GRID_ROWS*FLOOR_GRID_ROWS];  //includes 2D array
	for(int i = 0; i < FLOOR_GRID_ROWS*FLOOR_GRID_ROWS; i++)
	{
		//Intz all the FloorStructs
		floorMap[i].size = FLOOR_GRID_SIZE;

	}

}

GLuint FloorMap::getTextID()
{
	return textureGrass;



}

void FloorMap::Draw()
{
	for(int i = 0; i < FLOOR_GRID_ROWS*FLOOR_GRID_ROWS; i++)
	{
		glPushMatrix();
		glTranslatef((i % FLOOR_GRID_ROWS)*FLOOR_GRID_SIZE, 0.0, (i / FLOOR_GRID_ROWS)*FLOOR_GRID_SIZE);	
		glBindTexture(GL_TEXTURE_2D,textureGrass);
		glBegin(GL_QUADS);
		glTexCoord2f(1,1); glVertex3f(+FLOOR_GRID_SIZE,0,-FLOOR_GRID_SIZE);
		glTexCoord2f(0,1); glVertex3f(-FLOOR_GRID_SIZE,0,-FLOOR_GRID_SIZE);
		glTexCoord2f(0,0); glVertex3f(-FLOOR_GRID_SIZE,0,+FLOOR_GRID_SIZE);
		glTexCoord2f(1,0); glVertex3f(+FLOOR_GRID_SIZE,0,+FLOOR_GRID_SIZE);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

	}

}