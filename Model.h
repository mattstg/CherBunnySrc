#ifndef MODEL
#define MODEL



#include "Consts.h"
using namespace std;
#include "glm\glm\glm.hpp"
#include "glm\glm\gtx\transform.hpp"

using namespace glm;

class Model
{

public:
	GLMmodel *model;
	glm::mat4 world;
	glm::vec4 location;
	GLfloat scale;
	bool toDelete;
	float HAng; //horz rotate
	float VAng; //Vertical rotate
	
	Model();
	Model(char *s);
	Model(char *s, glm::vec4 loc);
	Model(char *s, glm::vec4 loc, float scale);


	Model* retSelf();
	void forceCnstr(char *s, glm::vec4 loc, float scale);
	void Update();
	void Draw();
	void GenRotateMatrix();
	void moveModel(glm::vec4 v);
	void setPosition(glm::vec4 v);
	glm::vec4 getPosition();
	
	//~Model();
private:
	bool loadModel(char *s);
	bool loadModel(char *s, float scale);
};
#endif