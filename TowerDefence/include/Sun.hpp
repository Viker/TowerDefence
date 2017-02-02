#ifndef _SUN_HPP_
#define _SUN_HPP_

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"

class Sun : public SceneObject
{
public:
	Sun();
	~Sun();

protected:
	void privateInit();
	void privateRender();
	void privateUpdate();

private:
	GLfloat sunpos[3];
	int list_id;
	// ...
};

#endif //_SUN_HPP_