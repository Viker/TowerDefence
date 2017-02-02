#ifndef _MINION_H_
#define _MINION_H_

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"

/*
//////////////////////////////////////////////////////////////////////////
//	Minion Class 
//	Represents a minion
//	
// Points of intererest in the class:
// *Orientation
// 
// Healthbar by Alfred Wæhle 
//	
// Written by Nasser Ukla
//////////////////////////////////////////////////////////////////////////
*/

class Minion : public SceneObject
{
	public:
		Minion(int s,int hp);

		siut::Vec3f getPos(); //Redeclared coz of errors in compiler
		siut::Vec3f* getPosPtr();
		void TakeDamage(float dmg);
		float getHP(){return life_;}
		~Minion();
		
		bool HasReachedGoal();
		
  protected:
		void privateInit();
		void privateRender();
		void privateUpdate();
		std::vector< siut::Vec3f > getWayPoints();

	private:
		
		void CalculateOrientation();
		
		float _healthbar;
		float _ratio;
		
		bool _reachedgoal;
		float angle;
		float toRotate; 
		float speed_;
		float life_;
		float armor_;
		GLint id_list;
		GLuint geomID_;
		int nextWP_;
	
	std::vector< float > angle_;

	siut::Vec3f _position;
	siut::Vec3f _direction; 
    std::vector< siut::Vec3f > waypoints_;

    
};

#endif //_MINION_HPP_