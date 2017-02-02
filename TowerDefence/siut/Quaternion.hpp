#define ERROR_TOLERANCE 1e-6
#include "Vec3f.hpp"
#include "Mat4f.hpp"

namespace siut
{

class Quaternion
{
  public:
    Quaternion(void)
    {
     quat_[0]=0.0f;
     quat_[1]=0.0f;
     quat_[2]=0.0f;
     quat_[3]=1.0f; 
    }
	  Quaternion(const float newX,const float newY,const float newZ,const float newW);
    Quaternion(siut::Vec3f axis, float angle);

	  Quaternion &operator () (const float newX, const float newY, const float newZ);
	  Quaternion &operator () (const float newX, const float newY, const float newZ, const float newW);
	  Quaternion &operator () (Quaternion &other);
    Quaternion &operator () (siut::Vec3f axis, float angle);
	  Quaternion &operator = (Quaternion &other);
	  Quaternion &operator ~ ();
	  Quaternion &setValues(float newX, float newY, float newZ, float newW);

    inline float & operator[](int i) { return quat_[i]; }
    inline const float & operator[](int i) const { return quat_[i]; }

  	bool operator == (Quaternion &other);
	  bool operator != (Quaternion &other);

	  Quaternion operator - ();
	  Quaternion operator + (Quaternion &other);
	  Quaternion operator - (Quaternion &other);
	  Quaternion operator * (Quaternion &other);

	  Quaternion &operator += (Quaternion &other);
	  Quaternion &operator -= (Quaternion &other);
	  Quaternion &operator *= (Quaternion &other);

    Quaternion &operator /= (float &scalar);
	  Quaternion &operator *= (float &scalar);

  	Quaternion &setEuler(float yaw, float pitch, float roll);
    Quaternion &setAxisAngle(float x, float y, float z, float degrees);
	  Quaternion &normalize(void);
	  float getLength (void);
    siut::Mat4f getMatrix(void);
    
  private:
  	float quat_[4];

};

  Quaternion operator * (const Quaternion &first, const Quaternion &second);
  Quaternion operator + (const Quaternion &first, const Quaternion &second);
  Quaternion operator - (const Quaternion &first, const Quaternion &second);
  Quaternion operator - (const Quaternion &quaternion);

  Quaternion operator * (Quaternion quaternion, float scalar);
  Quaternion operator * (float scalar, Quaternion quaternion);

  Quaternion rotationArc(siut::Vec3f v0, siut::Vec3f v1);
  inline float dotProduct(const Quaternion &first, const Quaternion &second);
  inline Quaternion slerp(const Quaternion &from, const Quaternion &to, float interpolation);

} // end namespace siut