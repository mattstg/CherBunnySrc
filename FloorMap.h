#ifndef FLOORMAP_H
#define FLOORMAP_H


#include "Consts.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>

#include <iostream> //C++ I/O
#include <vector>
#include <GL/glut.h>
#include <cstdlib>
#include "glm.h"

const int FLOOR_GRID_ROWS = 3;
const int FLOOR_GRID_SIZE = 900; //LAND SIZE

struct Floor{int size;};



class FloorMap{
	
public:
	GLuint textureGrass;


	Floor * floorMap;

	GLuint getTextID();
	FloorMap();
	void Draw();
private:


};
#endif