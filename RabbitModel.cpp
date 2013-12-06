#include "RabbitModel.h"

RabbitModel::RabbitModel() : Model()
{
}

RabbitModel::RabbitModel(char *s) : Model(s)
{
}

RabbitModel::RabbitModel(char *s, vec4 loc) : Model(s, loc)
{
 direction = vec4(1,0,0,0);
 jumping = false;
}

RabbitModel::RabbitModel(char *s, vec4 loc, float scale) : Model(s, loc, scale)
{
  //Child constructor here
}

void RabbitModel::Move(){
	if(location != goToLoc){
		//vec4 movVec = goToLoc - location;
	}
}

void RabbitModel::MoveTo(vec4 v){
	goToLoc = v;
}

bool RabbitModel::Hop(){
	int frames = 20;
	

	if(!jumping){
		travelTo = location + direction; //calculate travelTo vector
		origionalx = location.x;
		origionalz = location.z;
		ticks = frames;
		jumping = true;
	}else if(ticks == 0){
		jumping = false;
		travelTo = vec4(0,0,0,0);
	}else{
		location.x += (travelTo.x-origionalx)/frames;	
		location.y = pow((double)(-(location.x-origionalx)), 2)+.95f; //SOMETHING IS WRONG WITH THIS.....
		location.z += (travelTo.z-origionalz)/frames; 
		ticks--;
	}		
	glutPostRedisplay();
	if(jumping){
		return true;
	}
	else{
		return false;
	}

}

void RabbitModel::Eat(){


}