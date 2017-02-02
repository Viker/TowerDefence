#include "Arrow.hpp"
#include "Vec3f.hpp"
#include "glm.h"

using namespace siut;

static GLMmodel* _arrow_model = NULL;

Arrow::Arrow()
{
	speed_ = 150;
	_done = false; 
	_fired = false;
}

Arrow::~Arrow()
{

}

void Arrow::privateInit()
{
	
}

void Arrow::privateRender()
{
	if(_fired && !_done)
	{
		glPushAttrib(GL_LIGHTING_BIT);
			glColor3f(1.0,0.0,0.0);
			gluSphere(gluNewQuadric(),1,4, 4 );
			glColor3f(1.0,1.0,1.0);
		glPopAttrib();
	}
}


void Arrow::privateUpdate()
{
	if(_fired)
	{
		Vec3f pos =  Vec3f ( matrix_[12], matrix_[13], matrix_[14]); 
				
		Vec3f a = m->getPos() - pos;

		if( length(a) <= 1.9 )
		{
				_done = true; 
				_fired = false;
				_done = false;
		}
		a.normalize();
		matrix_.translate(a * speed_ * sslf_);
	}
}
void Arrow::setStart(siut::Vec3f st)
{
	if(!_fired)
	{
			
	  matrix_[12] = st[0]; 
	  matrix_[13] = st[1] + 30 ;
	  matrix_[14] = st[2]; 
	}
}

void Arrow::setEnd(boost::shared_ptr<Minion> st)
{
	
	if(!_fired)
	 {
		m = st;
	 }
}






