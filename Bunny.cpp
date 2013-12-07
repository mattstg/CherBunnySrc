#include "Bunny.h"


Bunny::Bunny(char *s,glm::vec4 loc, float scale) : Model(s,loc,scale)
{
	metabolism = rand() % 4;
	glow = 0;
	curAte = 0;
	maxAte = 500; //set to zero, increases when collides with carrot
	state = GROUND;
	
};


void Bunny::Update(){

	if(state != ROCKET && state != EXPLODE) //if in a normal state
	if(maxAte != 0)  //if maxDig is not zero, then he is digesting
	{
		if(curAte < maxAte) //still chewing his food
		{
			curAte += metabolism;
		} else { //bunny has finished eating his food, now becomes a firework
			state = ROCKET;
		}
	}

	//Else bunny is in the other states
	if(state == ROCKET)
	{
		HAng += 20.0f;
	}

	Model::Update();
};

void Bunny::Draw(){
	
	Model::Draw();
}
