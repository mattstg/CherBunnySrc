#ifndef FLOORMAP_H
#define FLOORMAP_H

#include "Consts.h"  //has all glut include
#include <time.h>
#include <iostream> //C++ I/O
#include <vector>




struct Floor{int x,z;};



class FloorMap{
	
public:
	
	GLuint textureGrass;


	Floor * floorMap;


	FloorMap();
	FloorMap(int offestX,int offsetY);

	void LoadTexture();
	
	void Draw();
private:


};
#endif