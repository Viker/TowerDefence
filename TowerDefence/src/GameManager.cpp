#include "GameManager.hpp"

GLuint _textureId;

GameManager::GameManager()
{
	ListToDate = false; 
}

GameManager::~GameManager()
{
}

void GameManager::privateInit()
{
	std::cout << "GameManager Initialized." << std::endl;
	glEnable(GL_CULL_FACE);

	initParticle();

	cam_.reset(new Camera());
	
	bf_.reset(new BattleField());
	_sun.reset(new Sun());
	
	this->addSubObject(bf_);
	this->addSubObject(_sun);
	

	_TIMER_minion = 0;
	_TIMER_tower = 0; 
	_TIMER_wave = 0;
	_gold = 53;
	_Tprice = 20; 
	_score = 0;
	_lives = 50;
	_minions_in_play = 20;
	_minions_in_wave = 13;
	
	_killed = 0; 

	_text.init();

}

void GameManager::privateRender()
{
	char buffer[80];
	
	glPushMatrix();
	glLoadIdentity();

	sprintf(buffer, "Gold: %d", _gold);
	_text.setPos(-10.0f, 10.0f, -20.0f);
	_text.printString(buffer, Text::FONT_NORMAL);
	
	sprintf(buffer, "Buy tower (B) - Cost 20 Gold", _gold);
	_text.setPos(-10.0f, 9.0f, -20.0f);
	_text.printString(buffer, Text::FONT_NORMAL);
	
	sprintf(buffer, "Upgrade Tower (U) - Cost 30 Gold", _gold);
	_text.setPos(-10.0f, 8.0f, -20.0f);
	_text.printString(buffer, Text::FONT_NORMAL);

	sprintf(buffer, "Lives: %d", _lives);
	_text.setPos(10.0f, 9.0f, -20.0f);
	_text.printString(buffer, Text::FONT_NORMAL);
	
	sprintf(buffer, "Score: %d", _score);
	_text.setPos(10.0f, 10.0f, -20.0f);
	_text.printString(buffer, Text::FONT_NORMAL);

	sprintf(buffer, "Killed Minions: %d", _killed);
	_text.setPos(10.0f, 8.0f, -20.0f);
	_text.printString(buffer, Text::FONT_NORMAL);
	

	if(_lives == 0)
	{
		sprintf(buffer, "GAME OVER", _score);
		_text.setPos(0.0f, 0.0f, -20.0f);
		_text.printString(buffer, Text::FONT_NORMAL);
	}

	glLoadIdentity();
	glPopMatrix();
}

void GameManager::privateUpdate()
{
	if(_arrows.size() > _towers.size() + 5)
		_arrows.clear();
	GLenum err = glGetError();
	if(err != GL_NO_ERROR)
		std::cout << "OpenGL error: " << gluErrorString(err) << std::endl;
	// Instead of adding alle objects in the scene as subobject to the camera they are added as subobjects
	// to the game manager. Therefore, we set the game manager matrix equal to the camera matrix. 
	this->matrix_ = cam_->getMatrix();
	_particleEngine->advance(0.010);
	if (!ListToDate)
	{
		_MasteBBList = bf_->getBBList();
		ListToDate = true;
	}

	_TIMER_minion += sslf_; //Counter how often to add minions 

	if(_TIMER_minion >= 1.5)
	{
		//if( _minions_in_wave > 0)
		AddMinion();
		_TIMER_minion = 0;
	}

	if(_lives != 0)
		ChekTowerToMinion();
	



}

boost::shared_ptr<Camera> GameManager::getCam()
{
	return cam_;
}

bool GameManager::AddTower()
{
	if(CurrentSelectedTower != NULL)
	{
		CurrentSelectedTower->DeSelect();
		CurrentSelectedTower.reset();
	}
	if(_gold >= _Tprice)
	{
		boost::shared_ptr<Tower> t;
		t.reset(new Tower(0.0,0.0,_particleEngine));
		this->addSubObject(t);

		_MasteBBList.push_back(t->getAABB()); 

		t->setBoundingBoxList(_MasteBBList);


		_towers.push_back(t);

		CurrentTower = t; 
		_gold -= _Tprice;
		std::cout<< _gold << std::endl;
		return true;
	}
	else
		return false;

}

void GameManager::AddTowerDone() //Call when tower placing is done, used only for tower placing 
{
	_MasteBBList.push_back(CurrentTower->getAABB());
}

void GameManager::initParticle() //Loads and inits particles used on lvl 3 towers 
{
	BMPClass _myBmpClass;

	std::string _textPath = "../data/circle.bmp";
	BMPLoad(_textPath, _myBmpClass);

	glGenTextures(1, &_textureId22);

	_particleEngine.reset(new ParticleSystem(_textureId22));
	

}

void GameManager::AddMinion() // Adds minions that are stronger and faster
{
	_minions_in_wave--;
	double speed = 20 + (_minions_in_play * 0.05);
	//double life = 13;
	double life = 12 + ( 0.34 * _minions_in_play);
	_minions_in_play++;
	boost::shared_ptr<Minion> m;
	m.reset(new Minion(speed,life));
	this->addSubObject(m);
	_minions.push_back(m);

}

void GameManager::ChekTowerToMinion() //Cheks and updates status of towers, parts written by Alfred Whale
{
	
	for each(boost::shared_ptr<Tower> t in _towers)
	{
		for(int i = 0; i < _minions.size(); i++)
		{
			boost::shared_ptr<Minion> minion = _minions[i];

			siut::Vec3f dir = minion->getPos() - t->getPos();
			
			if(minion->HasReachedGoal())
				_lives--;

			// Sjekker om minion er innenfor rekkevidden til tower
			if(length(dir) <= t->getRange())// && !tower->hasTarget())
			{
				// Sjekker om minion er død
				if(minion->getHP() <= 0)
				{
					_gold += 1;
					removeMinion(minion, i);
					_score += _minions_in_play / 2;
					i--;
		
				}

				//Chek if tower is acctualy build 
				if (t->IsBuild())
					minion->TakeDamage(t->DoDamage());
				
				//Cheks if the tower is ready to shoot
				if(t->ToShoot())
				{
					bool ArrowFire = false;

					for each(boost::shared_ptr<Arrow> arw in _arrows) //Finds and empty arrow to draw
					{
						if(!arw->IsFiring())
						{
							arw->setStart(t->getPos());
							arw->setEnd(minion);
							arw->Fire();
							ArrowFire = true;
						}
					}

					if(!ArrowFire) // if all arrows used make a new one 
					{
						boost::shared_ptr<Arrow> aa;
						aa.reset(new Arrow());
						this->addSubObject(aa);
						_arrows.push_back(aa);
						aa->setStart(t->getPos());
						aa->setEnd(minion);
						aa->Fire();
					}
					
				}
				break;
			}
		}


	}
	int i = 0;




}

void GameManager::PickObject(int x, int y) //OpenGL Tower Picker 
{

	
	GLuint buff[64] = {0};
	GLint hits, view[4];

	int id;

	glSelectBuffer(64,buff);
	glGetIntegerv(GL_VIEWPORT, view);

	glRenderMode(GL_SELECT);
	glInitNames();

	glPushName(0);

	glMatrixMode(GL_PROJECTION);

	glPushMatrix();
	glLoadIdentity();

	gluPickMatrix(x,view[3]-y,1, 1, view);

	float ratio = (view[2]+0.0) / view[3];
	gluPerspective(60,ratio,1,3000);

	glMatrixMode(GL_MODELVIEW);
	render();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	hits = glRenderMode(GL_RENDER);

	processHits(hits, buff);

	glMatrixMode(GL_MODELVIEW);


}

void GameManager::processHits(GLint hits, GLuint* buffer) // Cheks the if towers have been selected
{
	unsigned int i, j;
	GLuint names, *ptr;
	int test = 0;
	
	ptr = (GLuint *) buffer;
	for (i = 0; i < hits; i++)
	{ 
		names = *ptr;

		ptr++;
		(float) *ptr/0x7fffffff;
		ptr++;
		(float) *ptr/0x7fffffff;
		ptr++;
		for (j = 0; j < names; j++)
		{    
			test = *ptr;
			ptr++;

		}
		
	}

	if(test != 0)
	{
		for each(boost::shared_ptr<Tower> t in _towers)
		{
			if(t->getIndex() == test)
			{
				if(CurrentSelectedTower != NULL)
					CurrentSelectedTower->DeSelect();
				t->Select();
				CurrentSelectedTower = t;
				break;
			}
		}
	}
	else if(CurrentSelectedTower != NULL)
	{
		CurrentSelectedTower->DeSelect();
		CurrentSelectedTower.reset();
	}


}

void GameManager::removeMinion(boost::shared_ptr<Minion> m, int index) //Removes minions
{
	_killed++;
	this->removeSubObject(m);
	_minions.erase(_minions.begin() + index);
	m->~Minion();
}

void GameManager::UpGradeSelected() //Tower 
	{
		if(CurrentSelectedTower != NULL && _gold >= 20)
			{
				if(CurrentSelectedTower->UpGrade())
					_gold -= 30;


			}
	}