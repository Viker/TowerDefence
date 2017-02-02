#include "Sun.hpp"
#include "Vec3f.hpp"

using namespace siut;

GLfloat light_spec[] = {1.0, 0.0, 0.0, 1.0};
GLfloat light_amb[] = {0.5, 0.5, 0.0, 1.0};
GLfloat light_dif[] = {1.0, 1.0, 1.0, 1.0};

Sun::Sun()
{
	sunpos[0] = 1.0;
	sunpos[1] = 0.5;
	sunpos[2] = 1.5;
	sunpos[3] = 0.0;
}

Sun::~Sun()
{
}

void Sun::privateInit()
{
}

void Sun::privateRender()
{

	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, sunpos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_spec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);

}

void Sun::privateUpdate()
{
	
}