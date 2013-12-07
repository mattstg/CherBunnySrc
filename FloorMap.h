#ifndef FLOORMAP_H
#define FLOORMAP_H

#include "Consts.h"  //has all glut include
#include <time.h>
#include <iostream> //C++ I/O
#include <vector>


const int FLOOR_GRID_ROWS = 40;
const int FLOOR_GRID_SIZE = 50; //LAND SIZE

struct Floor{int size;};



class FloorMap{
	
public:
	
	GLuint textureGrass;


	Floor * floorMap;

	void LoadTexture();
	FloorMap();
	void Draw();
private:


};
#endif