#include "Model.h"
#include "glm.h"
#include <GL/glut.h>
#include <time.h>

class RabbitModel : public Model{
public: 
	RabbitModel();
	RabbitModel(char *s);
	RabbitModel(char *s, vec4 loc);
	RabbitModel(char *s, vec4 loc, float scale);
	void MoveTo(vec4 v);
	bool Hop();
	void Eat();
	void SetAngle();
	void Move();
private:
	vec4 goToLoc;
	vec4* jumpAry;
	int ticks;
	bool jumping;
	int angle;
	vec4 direction;
	vec4 travelTo;
	int origionalx;
	int origionalz;

};