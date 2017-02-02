#include "BattleField.hpp"
#include "Vec3f.hpp"
#include "glm.h"

GLMmodel* _gate_model = NULL;

GLMmodel* _wall_model = NULL;

using namespace siut;

GLfloat SpecRef1[] =		{ 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat AmbientLight1[] =	{ 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat DiffuseLight1[] =	{ 0.7f, 0.7f, 0.7f, 1.0f };
GLubyte Shine1 =	100;

BattleField::BattleField()
{
	
}

BattleField::~BattleField()
{

}

void BattleField::genBoundingBoxes()
{

	AABB _boundingBox;  //Bounding box for the field

	waypoints_.push_back(Vec3f(110.0,		10.0,	0.0));
	waypoints_.push_back(Vec3f(110.0,		10.0,	100.0));
	waypoints_.push_back(Vec3f(210.0,		10.0,	100.0));
	waypoints_.push_back(Vec3f(210.0,		10.0,	190.0));
	waypoints_.push_back(Vec3f(70.0,		10.0,	190.0));
	waypoints_.push_back(Vec3f(70.0,		10.0,	150.0));
	waypoints_.push_back(Vec3f(10.0,		10.0,	150.0));
	waypoints_.push_back(Vec3f(10.0,		10.0,	250.0));
	waypoints_.push_back(Vec3f(130.0,		10.0,	250.0));
	waypoints_.push_back(Vec3f(130.0,		10.0,	430.0));
	waypoints_.push_back(Vec3f(70.0,		10.0,	430.0));
	waypoints_.push_back(Vec3f(70.0,		10.0,	510.0));
	waypoints_.push_back(Vec3f(280.0,		10.0,	510.0));
	waypoints_.push_back(Vec3f(280.0,		10.0,	0.0));
	



	//BB generations from Waypoints 
	for(int i = 0; i < waypoints_.size() - 1; i++)
	{
		siut::Vec3f current_ = waypoints_[i];
		siut::Vec3f next_ = waypoints_[i+1];
		
		if(current_[0] > next_[0] )
		{
			_boundingBox.min.x = next_[0] - 20; 
			_boundingBox.max.x = current_[0] + 20; 
		}
		else
		{
			_boundingBox.min.x = current_[0] - 20; 
			_boundingBox.max.x = next_[0] + 20; 
		}
		
		if(current_[2] > next_[2] )
		{
			_boundingBox.min.z = next_[2] - 20;
			_boundingBox.max.z = current_[2] + 20;

			
		}
		else
		{
			_boundingBox.min.z = current_[2] - 20;
			_boundingBox.max.z = next_[2] + 20;
		}
		_BoundingBoxList.push_back(_boundingBox);
	}

	

}

Vec3f BattleField::getPos()
{
	return _position;
}

void BattleField::setPos(siut::Vec3f newPos)
{
	_position = newPos;
}

void BattleField::privateInit()
{	
	genBoundingBoxes();
	
	srand( time(NULL));
	
	_position = Vec3f(0.0,0.0,0.0);

	BMPClass _myBmpClass;

	std::string _textPath = "../data/level11.bmp";  //Load the texture 
	BMPLoad(_textPath, _myBmpClass);

	glGenTextures(2, _textName);
	
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	
	glBindTexture(GL_TEXTURE_2D, _textName[0]);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D,0,3,_myBmpClass.width,_myBmpClass.height,0,GL_RGB,GL_UNSIGNED_BYTE,_myBmpClass.bytes);
	
	for(int i = 0; i < 330; i += 10 ) //Fill the array with Vertexes
		for(int j = 0; j < 650; j+= 10)
			{
				int rnd = (rand() % (1 - -1 +1))+ 0;
				_my_vert_array.push_back( Vec3f (i,rnd,j) );
				Tuple<float,2> tmp;
				tmp[0] = i / 320.0f;
				tmp[1] = j / 640.0f; 
				_my_texCor_array.push_back(tmp);
			}

	
	int	j = 0;
	int counter = 65;

	_my_index_array.push_back( std::vector<int>() ); //Fill Index

	for(int i = 0; i < _my_vert_array.size(); i++)
				{
					if(i == counter)
						{
						  counter += 65;
						  j++;
						  _my_index_array.push_back(  std::vector<int>()); 
						}

					
					_my_index_array[j].push_back( i + 65 );
					_my_index_array[j].push_back( i );	

				}


	// NORMAL CALCULATION FOR GROUND 

	for(int i = 0; i < _my_vert_array.size() - 65; i++)
	{
		Vec3f U = _my_vert_array[i];
		Vec3f V = _my_vert_array[i+1];
		Vec3f W = _my_vert_array[i+65];

		Vec3f V1 = V - U;
		Vec3f V2 = W - U;

		Vec3f _myNormal = V1.cross(V2);
		_myNormal.normalize();

		_my_normal_array.push_back(_myNormal);
	}


	//MODEL LOADING
	
	if(!_gate_model)
	{
		_gate_model = glmReadOBJ("gate.obj");
		if (!_gate_model)
			exit(0);

		glmUnitize(_gate_model);
		glmFacetNormals(_gate_model);
		glmVertexNormals(_gate_model, 90);

	}

	if(!_wall_model)
	{
		_wall_model = glmReadOBJ("wall.obj");
		if (!_wall_model)
			exit(0);

		glmUnitize(_wall_model);
		glmFacetNormals(_wall_model);
		glmVertexNormals(_wall_model, 90);

	}

}

void BattleField::privateRender()
{

 glPushAttrib(GL_LIGHTING_BIT);
	glPushMatrix();
	
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, &_my_vert_array[0]);
		glTexCoordPointer(2, GL_FLOAT, 0, &_my_texCor_array[0]);

		glEnable(GL_LIGHTING);
		
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D,_textName[0]);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				
		glNormalPointer(GL_FLOAT,0, &_my_normal_array[0]);
		glVertexPointer(3, GL_FLOAT, 0 , &_my_vert_array[0]);
		
		for( int i = 0; i < _my_index_array.size()-1; i++)
			{
				glDrawElements(GL_QUAD_STRIP,130, GL_UNSIGNED_INT, &_my_index_array[i][0]);
			}
		
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);

		glColor3f(1.0,1.0,1.0);
		glScalef(70,70,70);
		glTranslatef(1.55,0.5,0.0);
		glRotatef(90.0,0.0,1.0,0.0);
		
		glmDraw(_gate_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
		glPushMatrix();
			glScalef(0.3,0.3,0.3);
			glRotatef(90,0.0,1.0,0.0);
			glTranslatef(-4,-0.85,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
		glPopMatrix();
		glPushMatrix();
			glScalef(0.3,0.3,0.3);
			glRotatef(90,0.0,1.0,0.0);
			glTranslatef(4,-0.85,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
		glPopMatrix();
		glPushMatrix();
			glScalef(0.3,0.3,0.3);
			//glRotatef(90,0.0,1.0,0.0);
			glTranslatef(0,-0.85,-5.2);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
		glPopMatrix();

		glPushMatrix();
			glScalef(0.3,0.3,0.3);
			//glRotatef(90,0.0,1.0,0.0);
			glTranslatef(0,-0.85,10);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
			glTranslatef(-2,0.0,0);
			glmDraw(_wall_model,GLM_SMOOTH | GLM_TEXTURE | GLM_MATERIAL  );
		glPopMatrix();

		
		
		
	
	glPopMatrix();
	glPopAttrib();
	
}

void BattleField::privateUpdate()
{
}

std::vector<AABB> BattleField::getBBList()
{
	return _BoundingBoxList; 
}

