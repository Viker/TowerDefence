#ifndef _TOWER_HPP_
#define _TOWER_HPP_

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include "ParticleSystem.hpp"


struct Point // Tniop
{
	float x;
	float z;
};

struct AABB //Axis Aligned Bounding Box
{
	Point min;
	Point max;
};


class Tower : public SceneObject
{
public:
	Tower(float x, float z,boost::shared_ptr<ParticleSystem> ps);
	~Tower();

	void setPos(siut::Vec3f );
	void setDraw(bool b);
	
	siut::Vec3f getPos(); //Redeclared coz of errors in compiler
	 
	AABB getAABB();
	float getRange() {return range_;}
	void setAABB2(AABB b);
	void setBoundingBoxList(std::vector<AABB> bbl);
	void forceRender();
	bool UpGrade();
	void Select() {selected = true ;}
	void DeSelect() {selected = false;}
	bool IsBuild(){ return !_ToDraw;}
	bool IsBuildAble();
	bool ToShoot();
	int getIndex(){ return myIndex;}
	float DoDamage();
	
protected:
	void privateInit();
	void privateRender();
	void privateUpdate();

private:

	bool ChekBBCollision(const AABB& aabb, const Point& point);
	void ChekIfBuldable();
	void UpdateAABB();


	bool _ToDraw;
	bool _Buildable; 
	bool initDone; 
	bool selected; 
	bool _selecting;
	bool _toShoot;

	int scale,myIndex, lvl; 
	float _damage; 

	GLint id_list;

	AABB tower2; 
	float angle;
	float color;
	float rotAngle; 
	
	AABB _boundingBox; 

	std::vector<AABB>	_BoundingBoxList; 
	
	siut::Vec3f _position;
	siut::Vec3f _position_prev;
	siut::Vec3f _position_next;
	boost::shared_ptr<ParticleSystem> _ps;

	float range_;
	float fireDelay_;
	float _accumsslf; 
	// ...


};

#endif //_TOWER_HPP