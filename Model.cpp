#include "Model.h";




Model::Model(){
	world = glm::mat4(1.0f);
	location = glm::vec4(1.0f);
	scale = 1.0f;
	HAng = 0;
	//loadModel("");
}

Model::Model(char *s){
	world = glm::mat4(1.0f);
	location = glm::vec4(1.0f);
	scale = 1.0f;
	HAng = 0;
	loadModel(s);
}

Model::Model(char *s, glm::vec4 loc){
	world = glm::mat4(1.0f);
	location = loc;
	scale = 1.0f;
	HAng = 0;
	loadModel(s);
}

Model::Model(char *s, glm::vec4 loc, float scale){
	world = glm::mat4(1.0f);
	location = loc;
	scale = scale;
	HAng = 0;
	loadModel(s, scale);
	
}
/*
Model::~Model(){
	delete model;
}
*/
void Model::Update(){



}

void Model::Draw(){
	
	glPushMatrix();
	GLfloat mat2_ambient[ ] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat2_diffuse[ ] = {0.5, 0.5, 0.5, 1.0};
	GLfloat mat2_specular[ ] = {0.7, 0.6, 0.6, 1.0};
	GLfloat mat2_shininess[ ] = {32.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat2_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat2_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat2_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat2_shininess);
	glTranslatef(location.x,location.y,location.z);
	GenRotateMatrix();
	
	
	glmDraw(model, GLM_SMOOTH|GLM_MATERIAL);
	glPopMatrix();
}

void Model::GenRotateMatrix()
{
	glRotatef(HAng, 0.0, 1.0, 0.0);
	//can add vertical ang here as well, and any other rotations for flying into air




}

void Model::moveModel(glm::vec4 v){
	location += v;
}

void Model::setPosition(glm::vec4 v){
	location = v;
}


glm::vec4 Model::getPosition(){
	return location;
}

bool Model::loadModel(char* s) {
    model = glmReadOBJ(s);
	glmUnitize(model);
	glmFacetNormals(model);
	glmVertexNormals(model, 90.0);
	return true;
}

bool Model::loadModel(char* s, float scale) {
    model = glmReadOBJ(s);
	glmUnitize(model);
    glmScale(model, scale);
	glmFacetNormals(model);
	glmVertexNormals(model, 90.0);
	return true;
}

