#ifndef CONSTS_H
#define CONSTS_H

#include "AllGlutInc.h"
	

	struct Vect3{
	float x; float y; float z;
	};

	enum MousePressed{ LEFT,RIGHT,NONE};
	enum BunnyStates{ HOPPING, GROUND, ROCKET, EXPLODE};


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
		if(texture_obj == 0)
			texture_obj = 0;
};
	


#endif