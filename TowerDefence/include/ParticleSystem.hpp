#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include "Vec3f.hpp"

//Particle system from tutoria

const float GRAVITY = -3.0f;
const int NUM_PARTICLES = 10;
//The interval of time, in seconds, by which the particle engine periodically
//steps.
const float STEP_TIME = 0.01f;
//The length of the sides of the quadrilateral drawn for each particle.
const float PARTICLE_SIZE = 0.07f;
const float PI = 3.1415926535f;

struct Particle;

class ParticleSystem : public SceneObject
{

public:
	ParticleSystem(GLuint textureId1);
	void advance(float dt);
	~ParticleSystem();

	void render();

protected:
	void privateInit();
	void privateRender();
	void privateUpdate();

private:

	siut::Vec3f curColor();
	siut::Vec3f curVelocity();


	void createParticle(Particle* p);
	void step();

	GLint textureId;

	float timeUntilNextStep;
	float colorTime;
	float angle;
	float size;
	siut::Vec3f pos;
	Particle* p;
	std::vector<Particle*> ps;


};

#endif //_PARTICLE_H_
