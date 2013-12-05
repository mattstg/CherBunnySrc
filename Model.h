#ifndef MODEL
#define MODEL

#include <GL/glut.h>
#include "glm.h"
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

	Model();
	Model(char *s);
	Model(char *s, glm::vec4 loc);
	Model(char *s, glm::vec4 loc, float scale);
	void Update();
	void Draw();
	void moveModel(glm::vec4 v);
	void setPosition(glm::vec4 v);
	glm::vec4 getPosition();
	
	//~Model();
private:
	bool loadModel(char *s);
	bool loadModel(char *s, float scale);
};
#endif