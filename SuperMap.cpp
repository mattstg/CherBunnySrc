#include "SuperMap.h"




SuperMap::SuperMap()
{
	
	for(int i = 0; i < 16; i++)
	{
		map[i] = new Floors;
		map[i]->x = (i % 4) - 2;
		map[i]->y = (i / 4) - 2;
		map[i]->active = true;
		map[i]->fmap = new FloorMap(map[i]->x,map[i]->y);
		map[i]->fmap->LoadTexture();
		//all maps are set
	}
	


}


void SuperMap::Draw(float x, float y){

	//Given Cam po
	SetActives(x,y);
	
	//19 & 50, hardcode cause c++ not lettimg me make global .h constants
	for(int i = 0; i < 16; i++)
		if(map[i]->active)
			map[i]->fmap->Draw();

}

void SuperMap::SetActives(float x, float y)
{
	//Given Camera position, checks with skybox that is around cam
	//Find out which maps are within the bounds
	//Check all 4 corners of the box, and see if any of the 4 corners reside in the box

	for(int i = 0; i < 16; i++)
	{
		square2D a;
		a.x = x - LAND_SIZE/2;  //plus or minus, well find out
		a.y = y - LAND_SIZE/2;
		a.size = LAND_SIZE;

		square2D b;
		b.x = map[i]->x;
		b.y = map[i]->y;
		b.size = FLOOR_GRID_SIZE*FLOOR_GRID_ROWS;

		map[i]->active = G_BoundCheckSquares(a,b);
		


	}
	
}

void SuperMap::RearrangeGrid()
{





}



