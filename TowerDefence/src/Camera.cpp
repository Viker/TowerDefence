#include "Camera.hpp"


using namespace siut;

#define PIOVER180 0.0174532925199

Camera::Camera()
{
  matrix_.setIdentity();
 
  
}


Camera::~Camera()
{
	matrix_[12] = -110;
	matrix_[13] = -50;
	matrix_[14] = -390;
}

void Camera::privateInit()
{
}


void Camera::privateRender()
{
  // not drawing any camera geometry
}

void Camera::privateUpdate()
{




}

Vec3f Camera::getPosition()
{
	
	return Vec3f(matrix_[12],matrix_[13],matrix_[14]);
}

void Camera::moveRight()
{
	std::cout << "X" << matrix_[12] << ",Y " << matrix_[13] << " ,Z " << matrix_[14] << std::endl;
	if(matrix_[12] >= -280)
		matrix_.translate(-5.0f, 0.0f, 0.0f);
}
void Camera::moveLeft()
{
	if(matrix_[12] <= -5)
		matrix_.translate(5.0f, 0.0f, 0.0f);
}
void Camera::moveUp()
{
	if(matrix_[13] > -160)
		matrix_.translate(0.0f, -5.0f, 0.0f);
}
void Camera::moveDown()
{
	if(matrix_[13] < -5)
		matrix_.translate(0.0f, 5.0f, 0.0f);
}
void Camera::moveForward()
{

	if(matrix_[14] < -100)
		  matrix_.translate(0.0f, 0.0f, 5.0f);
}
void Camera::moveBackward()
{
	if(matrix_[14] > -600)
		matrix_.translate(0.0f, 0.0f, -5.0f);
}

