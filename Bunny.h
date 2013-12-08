#ifndef BUNNY_H
#define BUNNY_H

#include "Model.h"


class Bunny: public Model{
public:
	Bunny(){};
	Bunny(char *s,glm::vec4 loc, float scale); //call this cnstr

	void Update();
	void Draw();
	void EatCarrot();
	void ResetBunny();
	float GetPowerFactor();
	float power;  //return the amount of power the bunny has, 0-1, 1 being max power a bunny can store

private:
	float metabolism;
	float glow;
	float curAte;
	float maxAte;
	float pause;
	Vect3 velo;
	BunnyStates state;






};


#endif