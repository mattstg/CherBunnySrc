#include "Consts.h"

class Particle{
public: 
	Vect3 position;
	Vect3 velocity; 
	Vect3 acceleration; 
	float factor; 
	Particle(float x, float y, float z); 
	void Update();
};
