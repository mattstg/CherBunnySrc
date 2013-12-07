#include "Firework.h"
#define red 0
#define green 1
#define blue 2 

Firework::Firework(){
	//randomizes the color of the firework 
	color[red] = (rand() / (float)RAND_MAX); 
	color[green] = (rand() / (float)RAND_MAX); 
	color[blue] = (rand() / (float)RAND_MAX); 
	alpha = 1.0f; 
	IsDead = false; 
}

Firework::~Firework(){
	DeleteFirework();  
}

void Firework::BuildFirework(float x, float y, float z){
	for(int i = 0; i<100;i++){
		Particle p = Particle(x,y,z);  
		_particles.push_back(p);
	
	}
}
void Firework::DeleteFirework(){
	_particles.clear(); 
}
void Firework::UpdateFirework(){
	vector<Particle>::iterator pId; 
	for(pId = _particles.begin();pId != _particles.end(); ++pId){
		pId->Update();
	}
	alpha -= 0.01; 
	if(alpha<=0){	
		IsDead = true; 
	}
	
}
void Firework::DrawFirework(){
	glPointSize(3.0f);
	glEnable(GL_POINT_SMOOTH);
	glAlphaFunc(GL_GREATER,0.5f); 
    glEnable(GL_ALPHA_TEST); 
    glEnable(GL_BLEND);
	glBegin(GL_POINTS); 

	glColor4f(color[red],color[green], color[blue], alpha); 
	vector<Particle>::iterator pId; 
	for(pId = _particles.begin();pId != _particles.end(); ++pId){
		Vect3 &pos = pId->position; 
		glVertex3f(pos.x,pos.y,pos.z); 	
	}
	glEnd();
	glColor3f(1,1,1);
}