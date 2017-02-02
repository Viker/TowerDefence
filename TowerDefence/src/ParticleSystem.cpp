#include "ParticleSystem.hpp"
#include "Vec3f.hpp"

using namespace siut;

struct Particle
{
	Vec3f pos;
	Vec3f vel;
	Vec3f color;
	float timeAlive;
	float lifeSpan;
};

Particle particles[NUM_PARTICLES];

float randomFloat() 
{
	return (float)rand() / ((float)RAND_MAX + 1);
}

static Vec3f rotate(siut::Vec3f v, siut::Vec3f axis, float degrees)
{
	
	axis.normalize();
	float radians = degrees * PI / 180;
	float s = sin(radians);
	float c = cos(radians);
	return v * c + axis * axis.dot(v) * (1 - c) + v.cross(axis) * s;
}

static Vec3f adjParticlePos(Vec3f pos)
{
	return rotate(pos, Vec3f(1, 0, 0), -30);
}

static bool compareParticles(Particle* particle1, Particle* particle2)
{
	return adjParticlePos(particle1->pos)[2] < adjParticlePos(particle2->pos)[2];
}

void ParticleSystem::render()
{
	glPushAttrib(GL_LIGHTING_BIT);
	glPushMatrix();
		float size = PARTICLE_SIZE / 2;
		for(int i = 0; i < NUM_PARTICLES; i++)
		{
			ps.push_back(particles + i);
		}

		std::sort(ps.begin(), ps.end(), compareParticles);


		for(unsigned int i = 0; i < ps.size(); i++) 
		{
			p = ps[i];
			glColor4f(p->color[0], p->color[1], p->color[2], (1 - p->timeAlive / p->lifeSpan));

			pos = adjParticlePos(p->pos);

			glBegin(GL_QUADS);
			glNormal3f( 0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(pos[0] -size,pos[1] -size,  pos[2]);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(pos[0] +size,pos[1] -size,  pos[2]);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(pos[0] +size,pos[1]  +size,  pos[2]);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(pos[0] -size,pos[1]  +size,  pos[2]);
			
			glEnd();


			

		}
		ps.clear();
	glPopMatrix();
	glPopAttrib();

	
}


ParticleSystem::ParticleSystem(GLuint textureId1)
{
	textureId = textureId1;
	timeUntilNextStep = 0;
	colorTime = 0;
	angle = 0;
	for(int i = 0; i < NUM_PARTICLES; i++)
	{
		createParticle(particles + i);
	}
	for(int i = 0; i < 5 / STEP_TIME; i++)
	{
		step();
	}
	privateInit();
}

ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::advance(float dt)
{
	while (dt > 0) 
	{
		if (timeUntilNextStep < dt)
		{
			dt -= timeUntilNextStep;
			step();
			timeUntilNextStep = STEP_TIME;
		}
		else
		{
			timeUntilNextStep -= dt;
			dt = 0;
		}
	}
}



void ParticleSystem::privateRender()
{

}


void ParticleSystem::privateInit()
{
	std::cout << "ParticleSystem Initialized." << std::endl;
}

void ParticleSystem::privateUpdate()
{


}

void ParticleSystem::createParticle(Particle* p)
{
	p->pos = Vec3f(0, 0, 0);
	p->vel = curVelocity() + Vec3f(1.5f * randomFloat() - 0.25f,
		0.5f * randomFloat() - 0.25f,
		1.5f * randomFloat() - 0.25f);
	p->color = curColor();
	p->timeAlive = 0;
	p->lifeSpan = randomFloat() + 0;
}

Vec3f ParticleSystem::curColor()
{
	Vec3f color;

	color = Vec3f(colorTime * 30, colorTime * 10, colorTime * -5.0f);
	
	for(int i = 0; i < 3; i++) {
		if (color[i] < 0) {
			color[i] = 0;
		}
		else if (color[i] > 1) {
			color[i] = 1;
		}
	}

	return color;
}

Vec3f ParticleSystem::curVelocity()
{
	return Vec3f(0, 1, 0);
}

void ParticleSystem::step()
{
	colorTime += STEP_TIME / 10;
	while (colorTime >= 1) {
		colorTime -= 1;
	}

	angle += 0.0f * STEP_TIME;
	while (angle > 2 * PI) {
		angle -= 2 * PI;
	}

	for(int i = 0; i < NUM_PARTICLES; i++) {
		Particle* p = particles + i;

		p->pos += p->vel * STEP_TIME;
		p->vel += Vec3f(0.0f, -GRAVITY * STEP_TIME, 0.0f);
		p->timeAlive += STEP_TIME;
		if (p->timeAlive > p->lifeSpan) {
			createParticle(p);
		}
	}
}

