#include "Particle.h"
#include <stdlib.h> 

Particle::Particle(float x, float y, float z){
	factor = 0.1f; 
	position.x = x; 
	position.y = y; 
	position.z = z; 
	acceleration.x = 0; 
	acceleration.y =-0.25f; 
	acceleration.z = 0; 
	velocity.x = (rand()%30)-5; 
	velocity.y = (rand()%10)-5; 
	velocity.z = (rand()%30)-5; 
}
void Particle::Update(){
	position.x += velocity.x*factor; 
	position.y += velocity.y*factor;
	velocity.y += acceleration.y; 
	position.z += velocity.z*factor; 
}