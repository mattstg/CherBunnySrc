#ifndef SUPERMAP_H
#define SUPERMAP_H

#include "Consts.h"
#include "FloorMap.h"





class SuperMap{

	struct Floors{ FloorMap* fmap; int x; int y; bool active; };

public:
	Floors * map[9];

	SuperMap();

	//given camera pos
	void Draw(float x, float z);
	
	
private:
	void SetActives(float x, float z);

};


#endif