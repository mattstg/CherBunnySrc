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
private: 
	vector<Particle> _particles;  
	GLfloat alpha; 
	GLfloat color[3];

	Firework();
	void DeleteFirework(); 	
	void BuildFirework(float x, float y, float z);
	void UpdateFirework(const float &time); 
	void DrawFirework(); 
	void SetAplha(); 
};