#include <GL/GL.h>
#include "Consts.h"

class Particle{
public: 
	Vect3 position;
	Vect3 velocity; 
	Vect3 acceleration; 

	Particle(float x, float y, float z); 
	void Update(const float &timeElapsed);
};
