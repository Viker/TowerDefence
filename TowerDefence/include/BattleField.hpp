#ifndef _BATTLEFIELD_H_
#define _BATTLEFIELD_H_

#include <windows.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <time.h>


#include "SceneObject.hpp"
#include "Vec3f.hpp"
#include "BMPLoader.hpp"
#include "Tuple.hpp"
#include "Tower.hpp"

/*
//////////////////////////////////////////////////////////////////////////
//BattleField Class 
// Draws the battlefield and the castle wall
//	
// Points of intererest in the class:
// *Bounding Box Generation from Waypoints
// *Normal Generation from vertex
// *Random bumped terrain 
// Written by Nasser Ukla
//////////////////////////////////////////////////////////////////////////
*/
class BattleField : public SceneObject
{
	public:
		BattleField();
		~BattleField();
		
		siut::Vec3f getPos();
		
		void setPos(siut::Vec3f newPos);
		std::vector<AABB> getBBList();

  protected:
	    virtual void privateInit();
		virtual void privateRender();
		virtual void privateUpdate();


  private:
	
	void genBoundingBoxes(); 

	std::vector<AABB>					_BoundingBoxList; 
	std::vector< siut::Vec3f >			vertexArray_; // Maybe two-dim vector and several arrays
	std::vector< siut::Vec3f >			waypoints_; 
	
	std::vector< siut::Vec3f >			 _my_vert_array;
	std::vector< siut::Vec3f >			 _my_normal_array;
	
	std::vector< std::vector<int> >		 _my_index_array;
	std::vector< siut::Tuple<float, 2> > _my_texCor_array;
    GLuint _textName[2];

	siut::Vec3f _position;


};

#endif //_BATTLEFIELD_H_