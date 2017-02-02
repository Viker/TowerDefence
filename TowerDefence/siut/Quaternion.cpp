#include "Quaternion.hpp"
#include <math.h>

#define SIUT_PI 3.141592653589

namespace siut {


Quaternion::Quaternion(const float newX, const float newY, const float newZ, const float newW)
{
  quat_[0] = newX;
  quat_[1] = newY;
  quat_[2] = newZ;
  quat_[3] = newW;
}

Quaternion::Quaternion(Vec3f axis, float angle)
{
	float temp1, temp2;
  temp1 = length(axis);
	//assert(temp1 != 0 && "Quaternion axis is zero!");
  temp2 = sinf(angle * 0.5f) / temp1;
	setValues(axis[0] * temp2, axis[1] * temp2, axis[2] * temp2, cosf(angle * 0.5f));
}

Quaternion &Quaternion::operator () (const float newX, const float newY, const float newZ)
{
  quat_[0] = newX;
  quat_[1] = newY;
  quat_[2] = newZ;
	return *this;
}

Quaternion &Quaternion::operator () (const float newX,const float newY,const float newZ,const float newW)
{
  quat_[0] = newX;
  quat_[1] = newY;
  quat_[2] = newZ;
  quat_[3] = newW;
	return *this;
}

Quaternion &Quaternion::operator () (Quaternion &other)
{
  quat_[0] = other[0];
  quat_[1] = other[1];
  quat_[2] = other[2];
  quat_[3] = other[3];
	return *this;
}

Quaternion &Quaternion::operator () (Vec3f axis, float angle)
{
	float temp1,temp2;
  temp1 = length(axis);
	//assert(temp1 != 0 && "Quaternion axis is zero!");
	temp2 = sinf(angle * 0.5f) / temp1;
	setValues(axis[0] * temp2, axis[1] * temp2, axis[2] * temp2, cosf(angle * 0.5f));
	return *this;
}

Quaternion &Quaternion::operator = (Quaternion &other)
{
  quat_[0] = other[0];
  quat_[1] = other[1];
  quat_[2] = other[2];
  quat_[3] = other[3];
	return *this;
}

Quaternion &Quaternion::operator ~ ()
{
	quat_[0]=-quat_[0];
	quat_[1]=-quat_[1];
	quat_[2]=-quat_[2];
	return *this;
}

Quaternion &Quaternion::setValues(float newX, float newY, float newZ, float newW)
{
	quat_[0] = newX;
	quat_[1] = newY;
	quat_[2] = newZ;
	quat_[3] = newW;
	return *this;
}

bool Quaternion::operator == (Quaternion &other)
{
  if ((quat_[0]==other[0]) && (quat_[1]==other[1]) && (quat_[2]==other[2]) && (quat_[3]==other[3])) return true;
	return false;
}

bool Quaternion::operator != (Quaternion &other)
{
	if ((quat_[0] != other[0]) || (quat_[1] != other[1]) || (quat_[2] != other[2]) || (quat_[3] != other[3])) return true;
	return false;
}

Quaternion Quaternion::operator - ()
{
	return Quaternion(-quat_[0],-quat_[1],-quat_[2],-quat_[3]);
}

Quaternion Quaternion::operator + (Quaternion &other)
{
	Quaternion temp;
	temp(other[0] + quat_[0],other[1] + quat_[1], other[2] + quat_[2], other[3] + quat_[3]);
	return temp;
}

Quaternion Quaternion::operator - (Quaternion &other)
{
	Quaternion temp;
	temp(other[0]-quat_[0],other[1]-quat_[1],other[2]-quat_[2],other[3]-quat_[3]);
	return temp;
}

Quaternion Quaternion::operator * (Quaternion &other)
{
	return Quaternion(
		quat_[3] * other[0] + quat_[0] * other[3] + quat_[1] * other[2] - quat_[2] * other[1],
		quat_[3] * other[1] + quat_[1] * other[3] + quat_[2] * other[0] - quat_[0] * other[2],
		quat_[3] * other[2] + quat_[2] * other[3] + quat_[0] * other[1] - quat_[1] * other[0],
		quat_[3] * other[3] - quat_[0] * other[0] - quat_[1] * other[1] - quat_[2] * other[2]); 
}


Quaternion &Quaternion::operator += (Quaternion &other)
{
	quat_[0]+=other[0];
	quat_[1]+=other[1];
	quat_[2]+=other[2];
	quat_[3]+=other[3];
	return *this;
}

Quaternion &Quaternion::operator -= (Quaternion &other)
{
	quat_[0]-=other[0];
	quat_[1]-=other[1];
	quat_[2]-=other[2];
	quat_[3]-=other[3];
	return *this;
	}

Quaternion &Quaternion::operator *= (Quaternion &other)
{
	quat_[0]=quat_[3] * other[0] + quat_[0] * other[3] + quat_[1] * other[2] - quat_[2] * other[1],
	quat_[1]=quat_[3] * other[1] + quat_[1] * other[3] + quat_[2] * other[0] - quat_[0] * other[2],
	quat_[2]=quat_[3] * other[2] + quat_[2] * other[3] + quat_[0] * other[1] - quat_[1] * other[0],
	quat_[3]=quat_[3] * other[3] - quat_[0] * other[0] - quat_[1] * other[1] - quat_[2] * other[2]; 
	return *this;
}

Quaternion &Quaternion::operator /= (float &scalar)
{
	return setValues(quat_[0]/scalar, quat_[1]/scalar, quat_[2]/scalar, quat_[3]/scalar);
}

Quaternion &Quaternion::operator *= (float &scalar)
{
	return setValues(quat_[0]*scalar, quat_[1]*scalar, quat_[2]*scalar, quat_[3]*scalar);
}

Quaternion &Quaternion::setEuler(float yaw, float pitch, float roll)
{
	float cosY = cosf(yaw / 2.0f);
	float sinY = sinf(yaw / 2.0f);
	float cosP = cosf(pitch / 2.0f);
	float sinP = sinf(pitch / 2.0f);
	float cosR = cosf(roll / 2.0f);
	float sinR = sinf(roll / 2.0f);
	setValues(
		cosR * sinP * cosY + sinR * cosP * sinY,
		cosR * cosP * sinY - sinR * sinP * cosY,
		sinR * cosP * cosY - cosR * sinP * sinY,
		cosR * cosP * cosY + sinR * sinP * sinY
		);
	return *this;
}

Quaternion &Quaternion::normalize(void)
{
	float length=getLength();
	quat_[0]/=length;
	quat_[1]/=length;
	quat_[2]/=length;
	quat_[3]/=length;
	return *this;
}

float Quaternion::getLength(void)
{
	return sqrtf(quat_[3] * quat_[3] + quat_[0] * quat_[0] + quat_[1] * quat_[1] + quat_[2] * quat_[2]);
}

Mat4f Quaternion::getMatrix(void)
{
	return Mat4f(
		Vec4f(1 - 2.0f*(quat_[1]*quat_[1]) - 2.0f*(quat_[2]*quat_[2]), 
          2.0f*(quat_[0]*quat_[1]+quat_[2]*quat_[3]), 
          2.0f*(quat_[0]*quat_[2]-quat_[1]*quat_[3]), 
          0.0f),
		Vec4f(2.0f*(quat_[0]*quat_[1]-quat_[2]*quat_[3]), 
          1 - 2.0f*(quat_[0]*quat_[0]) - 2*(quat_[2]*quat_[2]), 
          2*(quat_[2]*quat_[1]+quat_[0]*quat_[3]), 
          0.0f),
		Vec4f(2*(quat_[0]*quat_[2]+quat_[1]*quat_[3]), 
          2*(quat_[1]*quat_[2]-quat_[0]*quat_[3]), 
          1 - 2*(quat_[0]*quat_[0]) - 2*(quat_[1]*quat_[1]), 
          0.0f), 
    Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
}


Quaternion &Quaternion::setAxisAngle(float x, float y, float z, float degrees)
{
	float angle = float((degrees / 180.0f) * SIUT_PI);
	float result = float(sin( angle / 2.0f ));

	quat_[0] = float(x * result);
	quat_[1] = float(y * result);
	quat_[2] = float(z * result);
	quat_[3] = float(cos( angle / 2.0f ));
  return *this;
}

//-------------

Quaternion operator * (const Quaternion &first, const Quaternion &second)
{
	return Quaternion(
			first[3] * second[0] + first[0] * second[3] + first[1] * second[2] - first[2] * second[1],
			first[3] * second[1] + first[1] * second[3] + first[2] * second[0] - first[0] * second[2],
			first[3] * second[2] + first[2] * second[3] + first[0] * second[1] - first[1] * second[0],
			first[3] * second[3] - first[0] * second[0] - first[1] * second[1] - first[2] * second[2]); 
}


Quaternion operator + (const Quaternion &first, const Quaternion &second)
{
	return Quaternion(first[0]+second[0],first[1]+second[1],first[2]+second[2],first[3]+second[3]);
}


Quaternion operator - (const Quaternion &first, const Quaternion &second)
{
	return Quaternion(first[0]-second[0],first[1]-second[1],first[2]-second[2],first[3]-second[3]);
}


Quaternion operator - (const Quaternion &quaternion)
{
	return Quaternion(-quaternion[0], -quaternion[1], -quaternion[2], -quaternion[3]);
}

Quaternion operator * (Quaternion quaternion, float scalar)
{
	return Quaternion(quaternion[0]*scalar, quaternion[1]*scalar, quaternion[2]*scalar, quaternion[3]*scalar);
}

Quaternion operator * (float scalar, Quaternion quaternion)
{
	return Quaternion(quaternion[0]*scalar, quaternion[1]*scalar, quaternion[2]*scalar, quaternion[3]*scalar);
}

Quaternion rotationArc(Vec3f v0, Vec3f v1)
{
	Quaternion quaternion;
	// v0.normalize(); 
	// v1.normalize();  // If vector is already unit length then why do it again?
  Vec3f temp = v0.cross(v1); // check if this is the correct order

  float d = v0.dot(v1);
  float s = (float)sqrtf((1.0f+d)*2.0f);
	quaternion[0] = temp[0] / s;
	quaternion[1] = temp[1] / s;
	quaternion[2] = temp[2] / s;
	quaternion[3] = s /2.0f;
	return quaternion;
}

float dotProduct(const Quaternion &first, const Quaternion &second)
{
	return first[0] * second[0] + first[1] * second[1] + first[2] * second[2] + first[3] * second[3];
}

Quaternion slerp(const Quaternion &from, const Quaternion &to, float interpolation)
{
	Quaternion temp;
	float omega, cosO, sinO;
	float scale0, scale1;

	cosO = dotProduct(from, to);

	if (cosO < 0.0)
	{
		cosO = -cosO;
		temp = -to;
	}
	else
	{
		temp = -to;
	}

	if ((1.0 - cosO) > ERROR_TOLERANCE)
	{
		omega = (float)acos(cosO);
		sinO = sinf(omega);
		scale0 = sinf((1.0f - interpolation) * omega) / sinO;
		scale1 = sinf(interpolation * omega) / sinO;
  }
	else
	{
		scale0 = 1.0f - interpolation;
		scale1 = interpolation;
	}
	return from*scale0 + temp*scale1;
}

} // end namespace siut