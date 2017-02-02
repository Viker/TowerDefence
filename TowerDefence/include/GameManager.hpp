#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

#include "SceneObject.hpp"
#include "BattleField.hpp"
#include "Minion.hpp"
#include "Camera.hpp"
#include "Tower.hpp"
#include "Sun.hpp"
#include "Tuple.hpp"
#include "ParticleSystem.hpp"
#include "Text.hpp"
#include "Arrow.hpp"

#define BUFSIZE 64

/*
//////////////////////////////////////////////////////////////////////////
//	GameManager Class 
// Manages the game
//	
// Points of intererest in the class:
// *OpenGl Pick code
// 
//	
// Written by Nasser Ukla parts borrower from Alfred Wæhle 
//////////////////////////////////////////////////////////////////////////
*/

class GameManager : public SceneObject
{

public:
	
	GameManager();
	~GameManager();

	bool AddTower(); 
	void AddTowerDone(); 
	void AddMinion();

	void PickObject(int x,int y); 

	void UpGradeSelected();

	boost::shared_ptr<Camera> getCam();
	boost::shared_ptr<BattleField> bf_;
	boost::shared_ptr<ParticleSystem> _particleEngine;
	
	boost::shared_ptr<Tower> CurrentTower;
	boost::shared_ptr<Tower> CurrentSelectedTower;

protected:
	virtual void privateInit();
	virtual void privateRender();
	virtual void privateUpdate();

private:
	void removeMinion(boost::shared_ptr<Minion> m, int index);
	void initParticle();
	void ChekTowerToMinion();

	void processHits(GLint hits, GLuint* names);

	bool ListToDate;
	
	GLuint selectBuf[BUFSIZE];
	GLint hits;

	double _TIMER_minion, _TIMER_tower, _TIMER_wave;
	int _minions_in_wave, wave_num, _gold, _Tprice;
	
	int _minions_in_play, _score,_lives,_killed; 
	Text _text;
	boost::shared_ptr<Minion> minion_;

	std::vector<AABB>	_MasteBBList; 

	std::vector<boost::shared_ptr<Tower>> _towers;
	std::vector<boost::shared_ptr<Arrow>> _arrows;
	std::vector<boost::shared_ptr<Minion>> _minions;


	GLuint _textureId22; 
	boost::shared_ptr<Sun> _sun;
	boost::shared_ptr<Camera> cam_;	

	GLuint _textName[2];
};

#endif //_GAME_MANAGER_H_