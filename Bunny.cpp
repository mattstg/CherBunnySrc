#include "Bunny.h"


Bunny::Bunny(char *s,glm::vec4 loc, float scale) : Model(s,loc,scale)
{
	pause = rand() % 3000;
	metabolism = rand() % 4;
	glow = 0;
	curAte = 0;
	maxAte = 0; //set to zero, increases when collides with carrot
	state = GROUND;
	velo.x = 0; velo.y =0; velo.z= 0;
	
};


void Bunny::Update(){

	if(state != ROCKET && state != EXPLODE) //if in a normal state
	{
		if(maxAte != 0)  //if maxDig is not zero, then he is digesting
		{
			if(curAte < maxAte) //still chewing his food
			{
				curAte += metabolism;
			} else { //bunny has finished eating his food, now becomes a firework
				state = ROCKET;
			}
		}
		//Hops around
	}

	if(state == HOPPING)
	{
		location.x += velo.x;
		location.y += velo.y;
		location.z += velo.z;
		velo.y += GRAVITY;

		if(location.y < BUNNY_HEIGHT/2)
		{
			location.y = BUNNY_HEIGHT/2;
			state = GROUND;
			pause = rand() % 3000;
			velo.x = 0;
			velo.y = 0;
			velo.z = 0;
		}
	}

	if(state == GROUND)
	{
		pause -= REFRESH_TIMER;
		
		if(pause < 0)
		{
			//hop into air
			state = HOPPING;
			velo.y = 2; 
			location.y = BUNNY_HEIGHT/2 + 2;
			
	
			HAng = (getRand() % 628) / 100.0f;  
			
			velo.z = cos(HAng) *  BUNNY_SPEED;
			velo.x = sin(HAng) *  BUNNY_SPEED;

			

			
			HAng = HAng * (180/3.14f); //using PI constant causes infinity error.
			
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