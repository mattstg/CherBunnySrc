#include <GL/glut.h>
#include <vector> 
#include "Consts.h"
#include "Particle.h"
using namespace std; 
#include "glm.h"
#include "glm\glm\glm.hpp"
#include "glm\glm\gtx\transform.hpp"
using namespace glm;

class Firework{
public: 
public: 
	vector<Particle> _particles;  
	GLfloat alpha; 
	GLfloat color[3];
	bool IsDead; 
	float explosiveForce;
	int numParticles;
public : 
	Firework();
	Firework(int numOfParticles, float explosiveForceMultiplier);
	~Firework(); 
	void DeleteFirework(); 	
	void BuildFirework(float x, float y, float z);
	void UpdateFirework(); 
	void DrawFirework(); 
};