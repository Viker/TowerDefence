#ifndef _SCENE_OBJECT_H_
#define _SCENE_OBJECT_H_

#include <vector>
#include <boost/smart_ptr.hpp>
#include "Mat4f.hpp"

// The SceneObject class is the parent of all objects in the scene graph.
// To make an object to use in the scene graph, inherit this class and
// override the methods private_init, private_update and private_render.
//
// The rest of the magic creating the scene graph is implemented in the
// methods init, update and render. Do NOT override those methods.
//
// The application is to create a "root" instance of SceneObject (or another
// class inheriting SceneObject). Then:
//  Call the root.init after OpenGL is initialized,
//  call root.update in the render-function, and
//  call root.render after update has been called.
//
// private_init: Here all the initializer-code is put, this method is called
//      after OpenGL has been initialized.
// private_update: This method is called prior to any rendering, animation-
//      code is to be implemented in here (motion, collition-detection). When
//      this method is called, the member sslf_ has been set, so time-dependent
//      animation can use this value.
// private_render: This is where the rendering-code is implemented. Here you
//      do all the actual drawing.
//
// matrix_: This is the transformation matrix of the scene-object. This
//      transformation is relative to the object's parent. The transformation
//      is performed as part of the scene graph-magic.
//
// The storage of the children is handled by smart pointers, this is because

class SceneObject
{
 public:
  SceneObject();
  virtual ~SceneObject();

  // This method causes all children to be rendered, don't override this one!
  void render();
  // This method causes all children to be updated, don't override this one!
  void update(double sslf);
  // This method causes all children to be initialized,don't override this one!
  void init();

  void addSubObject(boost::shared_ptr<SceneObject> newchild);
  void removeSubObject(const boost::shared_ptr<SceneObject> child);
  // Dangerous to enable, and use SharedPtr if this is to be used!
  //  std::vector<ScopedPtr<SceneObject> >& getSubObjects();

  void setMatrix(const siut::Mat4f& m) { matrix_ = m; }
  siut::Mat4f& getMatrix() { return matrix_; }

 protected:
  // Override this method with your own render-implementation.
  virtual void privateRender() {}
  // Override this method with your own update-implementation.
  virtual void privateUpdate() {}
  // Override this method with your own init-implementation.
  virtual void privateInit() {}

  // This member contains the time since last frame. It is set
  // before privateUpdate is called.
  double sslf_;

  // This is the transformation-matrix of the scene object.
  // Relative to the object's parent. Defaults to the identity matrix.
  siut::Mat4f matrix_;

 private:
  // List of all SceneObjects that belong to the current object.
  std::vector<boost::shared_ptr<SceneObject> > children_;
};

#endif // _SCENE_OBJECT_H_
