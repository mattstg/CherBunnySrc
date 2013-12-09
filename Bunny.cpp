#include "Bunny.h"


Bunny::Bunny(char *s,glm::vec4 loc, float scale) : Model(s,loc,scale)
{
	ResetBunny();
	state = GROUND;
	power = 0;
	
	
};


void Bunny::Update(){

	if(state != ROCKET && state != EXPLODE) //If in an acceptable state for digestion
	{
		if(maxAte != 0)  //if maxDig is not zero, then he is digesting
		{
			
			curAte += metabolism;
			//metabolism += .015f;

			if(curAte > maxAte || maxAte > CARROT_FOOD_AMT*5 ) //if done chewing his food, or ate too much
			{				
				state = ROCKET;
				
				MoveBunny(G_IntzVector(0,3,0));
				//location.y = 3;
				VAng = -90;				
			}
		}
		//Hops around
	}

	if(state == HOPPING)
	{
		//location.x += velo.x;
		//location.y += velo.y;
		//location.z += velo.z;
		MoveBunny(G_IntzVector(velo.x,velo.y,velo.z));

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
			velo.y = .2f; 
			location.y = BUNNY_HEIGHT/2 + 2;
			
	
			HAng = (getRand() % 628) / 100.0f;  
			VAng = 0;
			
			velo.z = cos(HAng) *  BUNNY_SPEED;
			velo.x = sin(HAng) *  BUNNY_SPEED;
			
			HAng = HAng * (180/3.14f); //using PI constant causes infinity error.
			
		}
		
	}

	
	
	//Else bunny is in the other states
	if(state == ROCKET)
	{
		maxAte -= 5;
		HAng += 20.0f;
		location.y +=5.0f;

		if(maxAte <= 0 || location.y > LAND_SIZE/3) //bunny has digested all the fuel
		{
			state = HOPPING;
			toDelete = true;	
			VAng = 90; //face first back down		
			
			//bunny will fall back to ground
		}
	}

	glow = curAte / (5*CARROT_FOOD_AMT);  //max glow occurs after digesting 4 carrots worth
	if(glow >= 1)
		glow = 1;

	Model::Update();
};




void Bunny::MoveBunny(Vect3 move)
{
	location.x += move.x;
	location.y += move.y;
	location.z += move.z;
	
	if(location.x > GAME_MAP_BOUND_W)
		location.x = GAME_MAP_BOUND_W -2;
	if(location.z > GAME_MAP_BOUND_W)
		location.z = GAME_MAP_BOUND_W - 2;
	

	if(location.x < GAME_MAP_BOUND_W_LB)
		location.x = GAME_MAP_BOUND_W_LB;
	if(location.z < GAME_MAP_BOUND_W_LB)
		location.z = GAME_MAP_BOUND_W_LB;


}


void Bunny::ResetBunny()
{
	pause = rand() % 3000; 
	metabolism = rand() % 4;
	glow = 0;
	curAte = 0;
	maxAte = 0; //set to zero, increases when collides with carrot
	state = HOPPING;
	velo.x = 0; velo.y =0; velo.z= 0;
	power = 0;

}

float Bunny::GetPowerFactor()
{
	return power/(float)(5*CARROT_FOOD_AMT);


}

void Bunny::EatCarrot()
{
	maxAte += CARROT_FOOD_AMT;
	power += CARROT_FOOD_AMT;

}

void Bunny::Draw(){	

	glColor3f(1.0-glow,1.0,1.0-glow);
	Model::Draw();
	glColor3f(1.0,1.0,1.0);
}