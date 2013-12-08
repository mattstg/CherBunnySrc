#ifndef BUNNY_H
#define BUNNY_H

#include "Model.h"


class Bunny: public Model{
public:
	Bunny(){};
	Bunny(char *s,glm::vec4 loc, float scale); //call this cnstr

	void Update();
	void Draw();

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