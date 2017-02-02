
#include "Minion.hpp"
#include "Vec3f.hpp"
#include "glm.h"
#include "BMPLoader.hpp"
#include "ParticleSystem.hpp"

using namespace siut;

static GLMmodel* _minion_model = NULL;

static GLfloat SpecRef[] =			{ 0.7f, 0.7f, 0.7f, 1.0f };
static GLfloat AmbientLight[] =	{ 0.5f, 0.0f, 0.0f, 1.0f };
static GLfloat DiffuseLight[] =	{ 1.0f, 1.0f, 0.5f, 1.0f };
static GLubyte Shine =	128;


Minion::Minion(int s,int hp)
{
		speed_ = s;
		life_  = hp;

		waypoints_.push_back(Vec3f(110.0,		10.0,	0.0));
		angle_.push_back(0.0f);
 		
		waypoints_.push_back(Vec3f(110.0,		10.0,	100.0));
		angle_.push_back(0.0f);
 		
		waypoints_.push_back(Vec3f(210.0,		10.0,	100.0));
		angle_.push_back(90.0f);
 		
		waypoints_.push_back(Vec3f(210.0,		10.0,	190.0));
		angle_.push_back(-90.0f);
 		
		waypoints_.push_back(Vec3f(70.0,		10.0,	190.0));
		angle_.push_back(-90.0f);
 		
		waypoints_.push_back(Vec3f(70.0,		10.0,	150.0));
		angle_.push_back(-90.0f);
 		
		waypoints_.push_back(Vec3f(10.0,		10.0,	150.0));
		angle_.push_back(90.0f);
		
		waypoints_.push_back(Vec3f(10.0,		10.0,	250.0));
		angle_.push_back(90.0f);
		
		waypoints_.push_back(Vec3f(130.0,		10.0,	250.0));
		angle_.push_back(90.0f);
		
		waypoints_.push_back(Vec3f(130.0,		10.0,	430.0));
		angle_.push_back(-90.0f);
		
		waypoints_.push_back(Vec3f(70.0,		10.0,	430.0));
		angle_.push_back(-90.0f);
		
		waypoints_.push_back(Vec3f(70.0,		10.0,	510.0));
		angle_.push_back(90.0f);
		
		waypoints_.push_back(Vec3f(280.0,		10.0,	510.0));
		angle_.push_back(90.0f);
		
		waypoints_.push_back(Vec3f(280.0,		10.0,	0.0));
		angle_.push_back(90.0f);

		matrix_.translate(waypoints_[0]);
		_direction = siut::Vec3f(1.0,0.0,0.0);
		nextWP_ = 1;


		_healthbar = 12;
		_ratio = 12/life_;

		angle = -90.0;
		privateInit();

		_reachedgoal = false;

}

Minion::~Minion()
{

}

void Minion::privateInit()
{
	if(!_minion_model)
	{
		_minion_model = glmReadOBJ("wrt.obj");
		if (!_minion_model)
			exit(0);

		glmUnitize(_minion_model);
		glmFacetNormals(_minion_model);
		glmVertexNormals(_minion_model, 90);
	}

	id_list = glGenLists(1);
	glNewList(id_list,GL_COMPILE);
		glmDraw(_minion_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
	glEndList();


}

void Minion::privateRender() // Healthbar written by  Alfred Kolsing Wæhle  and used Under Permission
{
	
  glPushAttrib(GL_LIGHTING_BIT);
	glPushMatrix();
	
		glLineWidth(1.0f);
		
		glBegin(GL_LINE_LOOP);
		glVertex2f( 0, 8);
		glVertex2f( 0, 7);
		glVertex2f(12, 7);
		glVertex2f(12, 8);
		glEnd();

		glLineWidth(4.0f);
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex2f( 0, 7.5);
		glVertex2f(_healthbar, 7.5);
		glEnd();
		glLineWidth(1.0f);
		
	glPopMatrix();

	glPushMatrix();
		glColor3f(1.0,1.0,1.0);
		glScalef(10,10,10);
		glRotatef(angle ,0.0,1.0,0.0);
		glCallList(id_list);
	glPopMatrix();
	glPopAttrib();
	

}

void Minion::privateUpdate()
{
	
		Vec3f pos =  Vec3f ( matrix_[12], matrix_[13], matrix_[14]); 
		
		Vec3f a = waypoints_[nextWP_] - pos;
						 
		if( length(a) <= 1.9 )
			{
			if(nextWP_ < waypoints_.size() -1 )
			{
				nextWP_++;
				angle += angle_[nextWP_];
				
			}
			else
			{
				_reachedgoal = true;
				nextWP_ = 0;
				angle += 180;
			}
			}
		a.normalize();
		matrix_.translate(a * speed_ * sslf_);
		

}

std::vector< siut::Vec3f > Minion::getWayPoints()
{
	return waypoints_;
}

siut::Vec3f Minion::getPos()
{
	_position[0] = matrix_[12]; 
	_position[1] = matrix_[13];
	_position[2] = matrix_[14];
	
	return _position;

}

void Minion::TakeDamage(float dmg)
{
	life_ -= dmg;

	_healthbar -= (_ratio * (dmg)); //From Alfred :) 
	if(_healthbar <= 0)
		_healthbar = 0;

}

void Minion::CalculateOrientation()
{
	
}

siut::Vec3f* Minion::getPosPtr() //NOT IN USE 
{
	_position[0] = matrix_[12]; 
	_position[1] = matrix_[13];
	_position[2] = matrix_[14];
	
	return &_position;
}

bool Minion::HasReachedGoal()
{
	if(_reachedgoal)
	{
		_reachedgoal = false;
		return true;
	}
	else return false; 
}