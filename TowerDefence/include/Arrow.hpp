#ifndef _ARROW_H_
#define _ARROW_H_

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include "Minion.hpp"
/*
Arrow Class !
Used for Drawing projectiles from Target to Tower 

*/
class Arrow : public SceneObject 
{
public:
	Arrow();

	siut::Vec3f getPos(); //Redeclared coz of errors in compiler
	
	void setStart(siut::Vec3f st);

	void setEnd(boost::shared_ptr<Minion> st);

	void Fire(){_fired = true;}
	bool IsFiring(){return _fired;}
	~Arrow();
	
protected:
	void privateInit();
	void privateRender();
	void privateUpdate();
	
private:
	
	float speed_;
	bool _done,_fired; 
	GLint id_list;
	siut::Vec3f b;
	siut::Vec3f pos;
	siut::Vec3f _position;
	siut::Vec3f _target; 
	boost::shared_ptr<Minion> m;
	std::vector< siut::Vec3f > waypoints_;

};

#endif //_MINION_HPP_