#include "Tower.hpp"
#include "Vec3f.hpp"
#include "glm.h"
#include "BMPLoader.hpp"
#include "ParticleSystem.hpp"

using namespace siut;

static GLMmodel* _tower_model = NULL;
static int pickIndex = 100;

static GLfloat SpecRef[] =			{ 0.7f, 0.7f, 0.7f, 1.0f };
static GLfloat AmbientLight[] =	{ 0.5f, 0.0f, 0.0f, 1.0f };
static GLfloat DiffuseLight[] =	{ 1.0f, 1.0f, 0.5f, 1.0f };
static GLubyte Shine =	128;

const int TIMER_MS = 25;

Tower::Tower(float x, float z,boost::shared_ptr<ParticleSystem> ps)
{
	_ps = ps; 
	range_ = 50;
	matrix_.translate(x,15,z);

	_position = Vec3f(0.0,0.0,0.0);

	_toShoot = true; 
	_ToDraw = false;
	_Buildable = true; 
	selected = false; 
	_selecting = false;
	_damage = 5;
	rotAngle = 10;
	lvl = 1;
	fireDelay_ = 1.0;
	_accumsslf = 1.0;

	scale = 10;
	_boundingBox.min.x = matrix_[12] - 19; 
	_boundingBox.min.z = matrix_[14] - 19;

	_boundingBox.max.x = matrix_[12] + 19; 
	_boundingBox.max.z = matrix_[14] + 19;

	pickIndex++;
	myIndex = pickIndex;
	
}

Tower::~Tower()
{
	initDone = true; 
}


void Tower::UpdateAABB()
{
	_boundingBox.min.x = matrix_[12] - 19; 
	_boundingBox.min.z = matrix_[14] - 19;

	_boundingBox.max.x = matrix_[12] + 19; 
	_boundingBox.max.z = matrix_[14] + 19;
}

void Tower::setDraw(bool b)
{
	_ToDraw = b; 
	privateInit();
}




void Tower::setPos(siut::Vec3f newPos)
{

	_position_next = newPos - _position;
	_position = newPos;

	matrix_.translate(_position_next[0],_position_next[1],_position_next[2]);

}

void Tower::privateRender()
{	

glPushAttrib(GL_LIGHTING_BIT);
	glPushName(myIndex);
	glPushMatrix();
	glTranslatef(0.0,-5.5 + lvl,0.0);
		if (_ToDraw)
		{
			glDisable(GL_DEPTH_TEST);
			
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			if(_Buildable)
				glColor4f(0,0,1,0.5);
			else
				glColor4f(1,0,0,0.5);
			glEnable(GL_COLOR_MATERIAL);
			glScalef(scale,scale,scale);

				glmDraw(_tower_model,GLM_TEXTURE );

			UpdateAABB();

		}
		
		glEnable(GL_DEPTH_TEST);
		glScalef(scale,scale,scale);
		
		if(!_ToDraw)
		{
			glColor3f(1.0,1.0,1.0);
			glCallList(id_list);
		}
			
		glMaterialfv(GL_FRONT, GL_SPECULAR, SpecRef);
		glMaterialf(GL_FRONT, GL_SHININESS, Shine);


		glTranslatef(0.0,0.9,0.0);
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if(lvl == 3)
			{
				glColor4f(1,0.1,0.3,0.2);
				gluSphere(gluNewQuadric(),0.30,20, 30 );
				_ps->render();

			}
		
		glDisable(GL_BLEND);
		glLineWidth(4.0f);
		
		
	glPopMatrix();
	glPopAttrib();

	//TOWER SWEEPER
	glPushAttrib(GL_LIGHTING_BIT);
	if(!_selecting)
	{
		glRotatef(rotAngle,0.0,-1.0,0.0);
		if(selected | _ToDraw )
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glBegin(GL_LINE_LOOP);
			for(int i = 0; i < 360; i++)
			{
				angle = i * 3.14159/180;
				color = i / 360.0; 
						
				glColor4f(0.1, color, 0.0f,color); //Sweeper COLOR 
				glVertex3f(cos(angle) * range_, -1.5f, sin(angle) * range_);
				
				
			}
			glEnd();
			glDisable(GL_BLEND);
			glBegin(GL_LINES);
			
			glVertex3f(0,0,0);
			glVertex3f(cos(angle) * range_, -1.5f, sin(angle) * range_);
			
			glEnd();

		}	
	
	}
	glPopAttrib();


}

void Tower::privateInit()
{
	
	if(initDone)
	{
		std::cout << "Tower Initialized." << std::endl;
		if(!_tower_model)
		{
			_tower_model = glmReadOBJ("tower.obj");
			if (!_tower_model)
				exit(0);

			glmUnitize(_tower_model);
			glmFacetNormals(_tower_model);
			glmVertexNormals(_tower_model, 90);
		}
		
		id_list = glGenLists(1);
		glNewList(id_list,GL_COMPILE);
		glmDraw(_tower_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
		glEndList();



		initDone = false; 
	}

}

void Tower::privateUpdate()
{
	_accumsslf += sslf_;
	rotAngle++;

	if(_ToDraw)
		ChekIfBuldable();
	
	UpdateAABB();
}

AABB Tower::getAABB()
{
	return this->_boundingBox;
}

void Tower::setAABB2(AABB b)
{
	tower2 = b;
}

bool Tower::ChekBBCollision(const AABB& aabb, const Point& point)
{
	return (point.x >= aabb.min.x && point.x <= aabb.max.x) &&
		(point.z >= aabb.min.z && point.z <= aabb.max.z);

}

void Tower::setBoundingBoxList(std::vector<AABB> bbl)
{
	_BoundingBoxList = bbl;
}

void Tower::ChekIfBuldable()
{

	Point temp;

	temp.x = matrix_[12];
	temp.z = matrix_[14];

	bool tempBool = false;

	for each(AABB box in _BoundingBoxList)
	{
		tempBool = ChekBBCollision(box, temp);
		if(tempBool)
			break;
	}

	if(tempBool)
	{
		_Buildable = false; 

	}
	else
		_Buildable = true; 



}

bool Tower::IsBuildAble()
{
	return _Buildable;
}
 
siut::Vec3f Tower::getPos()
{
	return _position;
}

void Tower::forceRender()
{
	_selecting = true;
	privateRender();
	_selecting = false;
}

float Tower::DoDamage()
{
	
	if (_accumsslf > 1.0)
	{
		_accumsslf = 0.0;
		_toShoot = true;
		return _damage;
	}
	else return 0.0; 
}

bool Tower::ToShoot()
{
	if (_toShoot)
	{
		_toShoot = false; 
		return true;
	}
	else return false; 

}

bool Tower::UpGrade()
	{
		if(lvl < 3)
			{
				lvl++;
				_damage += (lvl*5) + 5 ;
				scale += 5;
				return true;
			}
		else return false;
	}

