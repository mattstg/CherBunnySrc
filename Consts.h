#ifndef CONSTS_H
#define CONSTS_H

#include "AllGlutInc.h"
#include <stdlib.h>    
	

	struct Vect3{
	float x; float y; float z;
	};
	
	const int FLOOR_GRID_ROWS = 19;
	const int FLOOR_GRID_SIZE = 50; //Tile size
	const int LAND_SIZE = 900;
	const float GRAVITY = -1.0f;
	const float REFRESH_TIMER = 50; //the update func will be called every 50 ms
	const float BUNNY_SPEED = 5;
	const float BUNNY_HEIGHT = 16;
	const float PI = PI; //some ppl cant reach maths pi for some reason

	enum MousePressed{ LEFT,RIGHT,NONE};
	enum BunnyStates{ HOPPING, GROUND, ROCKET, EXPLODE};
	struct square2D{int x; int y; int size;};
	

	void static G_LoadTexture(GLuint texture_obj, const char *tFileName) {
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
		
	};

	//return true is a exists between || touching lb and ub (lower/upper bound)
	bool static G_BoundCheck(int a, int lb, int ub)
	{
		if(a >= lb && a <= ub)
			return true;
		return false;
	}

	//returns true if two 2D squares collide 
	bool static G_BoundCheckSquares(square2D a, square2D b)
	{
		if(G_BoundCheck(a.x,b.x,b.x + b.size) || G_BoundCheck(a.x+a.size,b.x,b.x+b.size) || G_BoundCheck(a.y,b.y,b.y + b.size) || G_BoundCheck(a.y+a.size,b.y,b.y+b.size))
			return true;
		return false;
	}
	
	
int static getRand()
	{		
		return rand();
	}


#endif