#include "FloorMap.h"


FloorMap::FloorMap()
{
	//Create array
	textureGrass = 0;
	floorMap = new Floor[FLOOR_GRID_ROWS*FLOOR_GRID_ROWS];  //includes 2D array
	for(int i = 0; i < FLOOR_GRID_ROWS*FLOOR_GRID_ROWS; i++)
	{		
		floorMap[i].x = (i % FLOOR_GRID_ROWS);
		floorMap[i].z = (i / FLOOR_GRID_ROWS);

	}

}

FloorMap::FloorMap(int offSetX, int offSetY)
{
	//Create array
	textureGrass = 0;
	floorMap = new Floor[FLOOR_GRID_ROWS*FLOOR_GRID_ROWS];  //includes 2D array
	for(int i = 0; i < FLOOR_GRID_ROWS*FLOOR_GRID_ROWS; i++)
	{		
		floorMap[i].x = (i % FLOOR_GRID_ROWS) + (offSetX*FLOOR_GRID_ROWS);
		floorMap[i].z = (i / FLOOR_GRID_ROWS) + (offSetY*FLOOR_GRID_ROWS);

	}

}

void FloorMap::LoadTexture()
{
	//glGenTextures(1,textureGrass);	
	//glGenTextures(1,&textureGrass);
	G_LoadTexture(textureGrass,"CherBunnySrc/textures/grass.jpg");
	//load map


}



void FloorMap::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,textureGrass);
	glColor3f(0.0,0.5,1.0);
	for(int i = 0; i < FLOOR_GRID_ROWS*FLOOR_GRID_ROWS; i++)
	{
		glPushMatrix();
		glTranslatef(floorMap[i].x*FLOOR_GRID_SIZE, 0.0, floorMap[i].z*FLOOR_GRID_SIZE);	
				
		glBegin(GL_QUADS);
		glNormal3f(0,1,0);
		glTexCoord2f(0,0); glVertex3f(0,0,0);
		glTexCoord2f(0,1); glVertex3f(0,0,-FLOOR_GRID_SIZE);
		glTexCoord2f(1,1); glVertex3f(-FLOOR_GRID_SIZE,0,-FLOOR_GRID_SIZE);
		glTexCoord2f(1,0); glVertex3f(-FLOOR_GRID_SIZE,0,0);
		
		glEnd();
		
		glPopMatrix();

	}
	glColor3f(1.0,1.0,1.0);
	glDisable(GL_TEXTURE_2D);
}