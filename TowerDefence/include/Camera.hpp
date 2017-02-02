#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include "SceneObject.hpp"
#include <vector>
#include "Quaternion.hpp"
#include "Vec3f.hpp"

class Camera : public SceneObject
{
	public:
		Camera();
		~Camera();

		void moveRight();
		void moveLeft();
		void moveUp();
		void moveDown();
		void moveBackward();
		void moveForward();
		siut::Vec3f getPosition();

	protected:
		void privateInit();
		void privateRender();
		void privateUpdate();


	
};

#endif //_CAMERA_HPP_

