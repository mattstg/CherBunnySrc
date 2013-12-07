#include "Particle.h"
#include <stdlib.h> 

Particle::Particle(float x, float y, float z){
	position.x = x; 
	position.y = y; 
	position.z = z; 
	acceleration.x = 0; 
	acceleration.y =-9.8f; 
	acceleration.z = 0; 
	velocity.x = -2 + (rand()/ (float)RAND_MAX)*4.0f; 
	velocity.y = -4.0f + ((float)rand() /(float)RAND_MAX)*-4.0f; 
	velocity.z = 0; 
}
void Particle::Update(const float &time){
	position.x = (velocity.x*time + acceleration.x*time)*time; 
	position.y = (velocity.y*time + acceleration.y*time)*time; 
	position.z = (velocity.z*time + acceleration.z*time)*time;
}