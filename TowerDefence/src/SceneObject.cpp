#include "SceneObject.hpp"

#include <windows.h>
#include <GL/gl.h>

// NB! Check matrix mult and scoped_ptr

SceneObject::SceneObject()
{
  matrix_.setIdentity();
}

SceneObject::~SceneObject()
{
}

void SceneObject::render()
{
  glPushMatrix();
    //this->matrix_.multMatrix();
    glMultMatrixf(&matrix_[0]);
    this->privateRender();
    for(std::vector<boost::shared_ptr<SceneObject> >::iterator it = children_.begin();
        it != children_.end(); it++)
        (*it)->render();
  glPopMatrix();
}

void SceneObject::update(double sslf)
{
  this->sslf_ = sslf;
  this->privateUpdate();
  for(std::vector<boost::shared_ptr<SceneObject> >::iterator it = children_.begin();
      it != children_.end(); it++)
      (*it)->update(sslf);
}

void SceneObject::init()
{
  this->privateInit();
  for(std::vector<boost::shared_ptr<SceneObject> >::iterator it = children_.begin();
      it != children_.end(); it++)
      (*it)->init();
}

void SceneObject::addSubObject(boost::shared_ptr<SceneObject> newchild)
{
  children_.push_back(newchild);
}

void SceneObject::removeSubObject(const boost::shared_ptr<SceneObject> child)
{
  for(std::vector<boost::shared_ptr<SceneObject> >::iterator it = children_.begin();
      it != children_.end(); it++)
    if(*it == child)
    {
      children_.erase(it);
      break;
    }
}


