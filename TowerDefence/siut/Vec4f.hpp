/**********************************************************************
 * 
 *  File: 
 * 
 *  Created:
 *
 *  $Rev: 811 $ 
 *  $Id: Vec4f.hpp 811 2008-07-31 14:10:26Z karianc $
 *
 *  This file is part of the Siut library.
 *  Copyright (C) 2007 by SINTEF.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 * 
 *  For using Sima with software that can not be combined with the
 *  GNU GPL, please contact SINTEF for aquiring a commercial license
 *  and support.
 *
 *  SINTEF, Pb 124 Blindern, N-0314 Oslo, Norway
 *  http://www.sintef.no
 *********************************************************************/

#ifndef _SIUT_SIMD_STANDARD_VEC4F_HPP_
#define _SIUT_SIMD_STANDARD_VEC4F_HPP_

#include <iostream>
#include <math.h>
#include <cmath>

namespace siut {

/** \brief Standard: class for doing vector length 3 calculations */

class Vec4f
{

public:
  
  /*-----------------------------------------------------------------------*/
  /*   Vec4f                                                               */
  /*-----------------------------------------------------------------------*/

  //constructor, elements are not initialized.
  Vec4f();

  Vec4f(float x, float y, float z, float w);
  Vec4f(const float *pf);
  Vec4f(float tab[4]);
  Vec4f(const Vec4f &v);
  Vec4f(const float s);

  /*-----------------------------------------------------------------------*/
  /*    operators +  -  *  /                                               */
  /*-----------------------------------------------------------------------*/

  inline Vec4f operator + (const Vec4f &v) const;
  inline Vec4f operator + (const float s) const;

  inline Vec4f operator - (const Vec4f &v) const;
  inline Vec4f operator - (const float s) const;

  inline Vec4f operator * (const Vec4f &v) const;
  inline Vec4f operator * (const float s) const;

  inline Vec4f operator / (const Vec4f &v) const;
  inline Vec4f operator / (const float s) const;

  /*-----------------------------------------------------------------------*/
  /*    operators += -= *= /=                                              */
  /*-----------------------------------------------------------------------*/

  inline void operator += (const Vec4f &v);
  inline void operator += (const float s);

  inline void operator -= (const Vec4f &v);
  inline void operator -= (const float s);

  inline void operator *= (const Vec4f &v);
  inline void operator *= (const float s);

  inline void operator /= (const Vec4f &v);
  inline void operator /= (const float s);

  /*-----------------------------------------------------------------------*/
  /*    operators == != <= >= < >                                       */
  /*-----------------------------------------------------------------------*/

  inline bool operator == (const Vec4f &u) const;

  //comparison, checks if at least one corresponding element is different.
  inline bool operator != (const Vec4f &v) const; 

  inline bool operator <= (const Vec4f &v) const;
  inline bool operator >= (const Vec4f &v) const;
  inline bool operator < (const Vec4f &v) const;
  inline bool operator > (const Vec4f &v) const;

  /*-----------------------------------------------------------------------*/
  /*    functions dot boolean abs l_inf normalize is                       */
  /*-----------------------------------------------------------------------*/
  
  inline float dot (const Vec4f &v) const;

  /** \brief function, checks if any elements are 0, return true if zero elements are 0. */
  inline float boolean (const Vec4f &v) const;

  inline void abs ();

  /** \brief function, returns the biggest number in absolute value. */
  inline float l_inf (const Vec4f &v) const;

  inline void normalize ();

  //sets the elements.
  inline void is (float x,  float y, float z, float w);

  /*-----------------------------------------------------------------------*/
  /*    functions x() y() z()  w() vec_[]                                     */
  /*-----------------------------------------------------------------------*/

  inline const float & x() const;
  inline float & x();
  inline const float & y() const;
  inline float & y();
  inline const float & z() const;
  inline float & z();
  inline const float & w() const;
  inline float & w();

  //returns the ite element in vector. (obs. first element has index 0)
  inline float & operator[](int i) { return vec_[i]; }
  inline const float & operator[](int i) const { return vec_[i]; }

  /*-----------------------------------------------------------------------*/
  /*    read  writhe                                                       */
  /*-----------------------------------------------------------------------*/

  void read(std::istream& is);
  void write(std::ostream& os) const;

  /*-----------------------------------------------------------------------*/
  /*    operators + - * / ^ with friend                                    */
  /*-----------------------------------------------------------------------*/

  inline friend Vec4f operator + (float s, const Vec4f &v); 
  inline friend Vec4f operator - (float s, const Vec4f &v); 
  inline friend Vec4f operator * (float s, const Vec4f &v); 
 
  /** \brief operator power, only ^2 and ^3 (anything but 2 gives 3) */
  inline friend Vec4f operator ^ (const Vec4f &v, int i);

  /*-----------------------------------------------------------------------*/
  /*    functions dot max min sqrt length normalize with friend            */
  /*-----------------------------------------------------------------------*/  

  inline friend float dot (const Vec4f &u, const Vec4f &v);

  //maximums of two vectors, ie. returns a vector with the maximums of the corresponding elements.
  inline friend Vec4f max_vec (const Vec4f &u , const Vec4f &v);

  //minima of two vectors, ie. returns a vector with the minima of the corresponding elements.
  inline friend Vec4f min_vec (const Vec4f &u , const Vec4f &v);

  inline friend Vec4f sqrt (const Vec4f &v);

  /** \brief function, calculates the length of a vector, ie. the square root of the sum of the element squared. */
  inline friend float length (const Vec4f &v);

  /** \brief function, calculates the length of a vector, ie. the sum of the element squared.  */
  inline friend float length_2 (const Vec4f &v); 

  inline friend Vec4f normalize (const Vec4f &v);

private:

  float vec_[4]; 

};

/*
/// Stream extraction for Vec4f.
std::istream& operator>>(std::istream& is, Vec4f& v);

/// Stream insertion for Vec4f.
std::ostream& operator<<(std::ostream& os, const Vec4f& v);
*/

/*-----------------------------------------------------------------------*/
/*    IMPLEMENTATION                                                     */
/*-----------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/*   Vec4f                                                               */
/*-----------------------------------------------------------------------*/

inline Vec4f::Vec4f()
{
}

inline Vec4f::Vec4f( float x,  float y, float z, float w)
{
  vec_[0]=x;
  vec_[1]=y;
  vec_[2]=z;
  vec_[3]=w;
}

inline Vec4f::Vec4f(const float *pf)
{
  vec_[0]=pf[0];
  vec_[1]=pf[1];
  vec_[2]=pf[2];
  vec_[3]=pf[3];
}

inline Vec4f::Vec4f(float tab[4])
{
  vec_[0]=tab[0];
  vec_[1]=tab[1];
  vec_[2]=tab[2];
  vec_[3]=tab[3];
}

inline Vec4f::Vec4f(const Vec4f &v)
{
  vec_[0]=v.vec_[0];
  vec_[1]=v.vec_[1];
  vec_[2]=v.vec_[2];
  vec_[3]=v.vec_[3];
}

inline Vec4f::Vec4f(const float s)
{
  for (int i = 0; i < 4; ++i)
    vec_[i] = s;
}

/*-----------------------------------------------------------------------*/
/*    operators +  -  *  /                                               */
/*-----------------------------------------------------------------------*/

//operators +
inline Vec4f Vec4f::operator + (const Vec4f &v) const
{   
  Vec4f res(*this);
  res += v;
  return res;
}
inline Vec4f Vec4f::operator + (const float s) const
{   
  Vec4f res(*this);
  res += s;
  return res;
}

//operators -
inline Vec4f Vec4f::operator - (const Vec4f &v) const
{   
  Vec4f res(*this);
  res -= v;
  return res;
}
inline Vec4f Vec4f::operator - (const float s) const
{   
  Vec4f res(*this);
  res -= s;
  return res;
}


//operators *
inline Vec4f Vec4f::operator * (const Vec4f &v) const
{   
  Vec4f res(*this);
  res *= v;
  return res;
}
inline Vec4f Vec4f::operator * (const float s) const
{   
  Vec4f res(*this);
  res *= s;
  return res;
}

//operators /
inline Vec4f Vec4f::operator / (const Vec4f &v) const
{   
  Vec4f res(*this);
  res /= v;
  return res;
}
inline Vec4f Vec4f::operator / (const float s) const
{   
  Vec4f res(*this);
  res /= s;
  return res;
}

/*-----------------------------------------------------------------------*/
/*    operators +=  -=  *=  /=                                           */
/*-----------------------------------------------------------------------*/
inline void Vec4f::operator += (const Vec4f &v)
{
  vec_[0]+=v.vec_[0];
  vec_[1]+=v.vec_[1];
  vec_[2]+=v.vec_[2];
  vec_[3]+=v.vec_[3];
}
inline void Vec4f::operator += (const float s)
{
  vec_[0] += s;
  vec_[1] += s;
  vec_[2] += s;
  vec_[3] += s;
}

inline void Vec4f::operator -= (const Vec4f &v)
{
  vec_[0]-=v.vec_[0];
  vec_[1]-=v.vec_[1];
  vec_[2]-=v.vec_[2];
  vec_[3]-=v.vec_[3];
} 
inline void Vec4f::operator -= (const float s)
{
  vec_[0] -= s;
  vec_[1] -= s;
  vec_[2] -= s;
  vec_[3] -= s;
}

inline void Vec4f::operator *= (const Vec4f &v)
{
  vec_[0]*=v.vec_[0];
  vec_[1]*=v.vec_[1];
  vec_[2]*=v.vec_[2];
  vec_[3]*=v.vec_[3];
}
inline void Vec4f::operator *= (const float s)
{
  vec_[0] *= s;
  vec_[1] *= s;
  vec_[2] *= s;
  vec_[3] *= s;
}

inline void Vec4f::operator /= (const Vec4f &v)
{
  vec_[0]/=v.vec_[0];
  vec_[1]/=v.vec_[1];
  vec_[2]/=v.vec_[2];
  vec_[3]/=v.vec_[3];
}
inline void Vec4f::operator /= (const float s)
{
  vec_[0] /= s;
  vec_[1] /= s;
  vec_[2] /= s;
  vec_[3] /= s;
}


/*-----------------------------------------------------------------------*/
/*    operators == != <= >= < >                                       */
/*-----------------------------------------------------------------------*/

//operators ==
inline bool Vec4f::operator == (const Vec4f &u) const
{    
  float res[4];
  if (vec_[0]==u.vec_[0])
    res[0]=1.;
  else   
    res[0]=0.;
  if (vec_[1]==u.vec_[1])
    res[1]=1.;
  else   
    res[1]=0.;
  if (vec_[2]==u.vec_[2])
    res[2]=1.;
  else   
    res[2]=0.;
  if (vec_[3]==u.vec_[3])
    res[3]=1.;
  else   
    res[3]=0.;
  
  if (res[0] * res[1] * res[2] * res[3] == 0)
    {return 0;}
  else 
    {return 1;}
} 


//operator != 

//minst et tall er forskjellig
inline bool Vec4f::operator != (const Vec4f &u) const
{    
  float res[4];
  if (vec_[0]!=u.vec_[0])
    res[0]=0.;
  else   
    res[0]=1.;
  if (vec_[1]!=u.vec_[1])
    res[1]=0.;
  else   
    res[1]=1.;
  if (vec_[2]!=u.vec_[2])
    res[2]=0.;
  else   
    res[2]=1.;
  if (vec_[3]!=u.vec_[3])
    res[3]=0.;
  else   
    res[3]=1.;
  
  if (res[0] * res[1] * res[2] * res[3] == 0)
    {return 1;}
  else 
    {return 0;}
} 


//operator <=
inline  bool Vec4f::operator <= (const Vec4f &u) const
{    
  float res[4];
  if (vec_[0]<=u.vec_[0])
    res[0]=1.;
  else   
    res[0]=0.;
  if (vec_[1]<=u.vec_[1])
    res[1]=1.;
  else   
    res[0]=0.;
  if (vec_[2]<=u.vec_[2])
    res[2]=1.;
  else   
    res[0]=0.;
  if (vec_[3]<=u.vec_[3])
    res[3]=1.;
  else   
    res[0]=0.;
  
  if (res[0] * res[1] * res[2] * res[3] == 0)
    {return 0;}
  else 
    {return 1;}
} 

//operator >=
inline bool Vec4f::operator >= (const Vec4f &u) const
{    
  float res[4];
  if (vec_[0]>=u.vec_[0])
    res[0]=1.;
  else   
    res[0]=0.;
  if (vec_[1]>=u.vec_[1])
    res[1]=1.;
  else   
    res[0]=0.;
  if (vec_[2]>=u.vec_[2])
    res[2]=1.;
  else   
    res[0]=0.;
  if (vec_[3]>=u.vec_[3])
    res[3]=1.;
  else   
    res[0]=0.;
  
  if (res[0] * res[1] * res[2] * res[3] == 0)
    {return 0;}
  else 
    {return 1;}
} 

//operator <
inline bool Vec4f::operator < (const Vec4f &u) const
{    
  float res[4];
  if (vec_[0]<u.vec_[0])
    res[0]=1.;
  else   
    res[0]=0.;
  if (vec_[1]<u.vec_[1])
    res[1]=1.;
  else   
    res[0]=0.;
  if (vec_[2]<u.vec_[2])
    res[2]=1.;
  else   
    res[0]=0.;
  if (vec_[3]<u.vec_[3])
    res[3]=1.;
  else   
    res[0]=0.;
  
  if (res[0] * res[1] * res[2] * res[3] == 0)
    {return 0;}
  else 
    {return 1;}
} 


//operator >=
inline bool Vec4f::operator > (const Vec4f &u) const
{    
  float res[4];
  if (vec_[0]>u.vec_[0])
    res[0]=1.;
  else   
    res[0]=0.;
  if (vec_[1]>u.vec_[1])
    res[1]=1.;
  else   
    res[0]=0.;
  if (vec_[2]>u.vec_[2])
    res[2]=1.;
  else   
    res[0]=0.;
  if (vec_[3]>u.vec_[3])
    res[3]=1.;
  else   
    res[0]=0.;
  
  if (res[0] * res[1] * res[2] * res[3] == 0)
    {return 0;}
  else 
    {return 1;}
} 

/*-----------------------------------------------------------------------*/
/*    functions dot boolean abs l_inf nomalize is                        */
/*-----------------------------------------------------------------------*/

//operator dot (scalar product)
inline float Vec4f::dot (const Vec4f &v) const
{   
  return(vec_[0]*v.vec_[0] + vec_[1]*v.vec_[1] + vec_[2]*v.vec_[2] + vec_[3]*v.vec_[3]);
}

//operator boolean
inline float Vec4f::boolean (const Vec4f &v) const
{   
  if (v.vec_[0] * v.vec_[1] * v.vec_[2] * v.vec_[3] == 0)
    {return 0;}
  else 
    {return 1;}
}

inline void Vec4f::abs ()
{
  Vec4f res(*this);
  if (res.vec_[0] < 0)
    vec_[0] = res.vec_[0] * (-1);
  if (res.vec_[1] < 0)
    vec_[1] = res.vec_[1] * (-1);
  if (res.vec_[2] < 0)
    vec_[2] = res.vec_[2] * (-1);
  if (res.vec_[3] < 0)
    vec_[3] = res.vec_[3] * (-1);
}

inline float Vec4f::l_inf (const Vec4f &v) const
{
  float f;
  float g;
  Vec4f res;
  
  if (v.vec_[0] < 0)
    res.vec_[0] = v.vec_[0] * (-1);
  else
    res.vec_[0] = v.vec_[0];
  if (v.vec_[1] < 0)
    res.vec_[1] = v.vec_[1] * (-1);
  else
    res.vec_[1] = v.vec_[1];
  if (v.vec_[2] < 0)
    res.vec_[2] = v.vec_[2] * (-1);
  else
    res.vec_[2] = v.vec_[2];
  if (v.vec_[3] < 0)
    res.vec_[3] = v.vec_[3] * (-1);
  else
    res.vec_[3] = v.vec_[3];

  if (res.vec_[0] >= res.vec_[1])
    f = res.vec_[0];
  else 
    f = res.vec_[1];
  
  if (res.vec_[2] >= res.vec_[3])
    g = res.vec_[2];
  else 
    g = res.vec_[3];
  
  if (g >= f)
    return g;
  else 
    return f;
}

inline void Vec4f::normalize ()
{   
  float length=std::sqrt(vec_[0]*vec_[0] + vec_[1]*vec_[1] + vec_[2]*vec_[2] + vec_[3]*vec_[3]);
  vec_[0]/=length;
  vec_[1]/=length;
  vec_[2]/=length;
  vec_[3]/=length;
}

inline void Vec4f::is (float x, float y, float z, float w)
{   
  vec_[0] = x;
  vec_[1] = y;
  vec_[2] = z;
  vec_[3] = w;
}

/*-----------------------------------------------------------------------*/
/*    functions x() y() z()  w()                                         */
/*-----------------------------------------------------------------------*/

inline const float & Vec4f::x() const 
{    return vec_[0];  }

inline float & Vec4f::x()
{    return vec_[0];  }

inline const float & Vec4f::y() const 
{    return vec_[1];  } 

inline float & Vec4f::y() 
{    return vec_[1];  }

inline const float & Vec4f::z() const 
{    return vec_[2];  } 

inline float & Vec4f::z() 
{    return vec_[2];  }

inline const float & Vec4f::w() const 
{    return vec_[3];  } 

inline float & Vec4f::w() 
{    return vec_[3];  }


/*-----------------------------------------------------------------------*/
/*    read  write                                                        */
/*-----------------------------------------------------------------------*/

inline void Vec4f::read(std::istream& is)
{
  is >> vec_[0] >> vec_[1] >> vec_[2] >> vec_[3];
}

inline void Vec4f::write(std::ostream& os) const
{
  os << vec_[0] << " "
      << vec_[1] << " "
      << vec_[2] << " " 
      << vec_[3];
}

/*-----------------------------------------------------------------------*/
/*    operators + - * / ^ with friend                                    */
/*-----------------------------------------------------------------------*/

inline Vec4f operator + (float s, const Vec4f &v)
{   
  Vec4f res(s);
  res += v;
  return res;
}

inline Vec4f operator - (float s, const Vec4f &v)
{   
  Vec4f res(s);
  res -= v;
  return res;
}

inline Vec4f operator * (float s, const Vec4f &v)
{   
  Vec4f res(s);
  res *= v;
  return res;
}

inline Vec4f operator ^ (const Vec4f &v, int i)
{   
  Vec4f res;
  if (i == 2)
  {
    res.vec_[0]=v.vec_[0]*v.vec_[0];
    res.vec_[1]=v.vec_[1]*v.vec_[1];
    res.vec_[2]=v.vec_[2]*v.vec_[2];
    res.vec_[3]=v.vec_[3]*v.vec_[3];
  }
  else 
    {
      res.vec_[0]=v.vec_[0]*v.vec_[0]*v.vec_[0];
      res.vec_[1]=v.vec_[1]*v.vec_[1]*v.vec_[1];
      res.vec_[2]=v.vec_[2]*v.vec_[2]*v.vec_[2];
      res.vec_[3]=v.vec_[3]*v.vec_[3]*v.vec_[3];
    }
  return res;
}
  
/*-----------------------------------------------------------------------*/
/*    functions dot max min sqrt length normalize with friend            */
/*-----------------------------------------------------------------------*/  

//func dot with friend
inline float dot (const Vec4f &u, const Vec4f &v) 
{   
  return(u.vec_[0]*v.vec_[0] + u.vec_[1]*v.vec_[1] + u.vec_[2]*v.vec_[2] + u.vec_[3]*v.vec_[3]);
}

//func max/min with friend
inline Vec4f min_vec (const Vec4f &u , const Vec4f &v) 
{   
  Vec4f res;
  if (u.vec_[0] < v.vec_[0])
    res.vec_[0] = u.vec_[0];
  else
    res.vec_[0] = v.vec_[0];
  if (u.vec_[1] < v.vec_[1])
    res.vec_[1] = u.vec_[1];
  else
    res.vec_[1] = v.vec_[1];
  if (u.vec_[2] < v.vec_[2])
    res.vec_[2] = u.vec_[2];
  else
    res.vec_[2] = v.vec_[2];
  if (u.vec_[3] < v.vec_[3])
    res.vec_[3] = u.vec_[3];
  else
    res.vec_[3] = v.vec_[3];
  return res;
}
inline Vec4f max_vec (const Vec4f &u , const Vec4f &v) 
{   
  Vec4f res;
  if (u.vec_[0] > v.vec_[0])
    res.vec_[0] = u.vec_[0];
  else
    res.vec_[0] = v.vec_[0];
  if (u.vec_[1] > v.vec_[1])
    res.vec_[1] = u.vec_[1];
  else
    res.vec_[1] = v.vec_[1];
  if (u.vec_[2] > v.vec_[2])
    res.vec_[2] = u.vec_[2];
  else
    res.vec_[2] = v.vec_[2];
  if (u.vec_[3] > v.vec_[3])
    res.vec_[3] = u.vec_[3];
  else
    res.vec_[3] = v.vec_[3];
  return res;
}

//operator sqrt 
inline Vec4f sqrt (const Vec4f &v)
{   
  Vec4f res;
  res.vec_[0] = std::sqrt(v.vec_[0]);
  res.vec_[1] = std::sqrt(v.vec_[1]);
  res.vec_[2] = std::sqrt(v.vec_[2]);
  res.vec_[3] = std::sqrt(v.vec_[3]);
  return res;
}

//operator length 
inline float length (const Vec4f &v)
{   
  float f;
  f = std::sqrt(v.vec_[0]*v.vec_[0]+v.vec_[1]*v.vec_[1]+v.vec_[2]*v.vec_[2]+v.vec_[3]*v.vec_[3]);
  return f;
}


//operator length_2 
inline float length_2 (const Vec4f &v)
{   
  Vec4f res;
  return v.vec_[0]*v.vec_[0]+v.vec_[1]*v.vec_[1]+v.vec_[2]*v.vec_[2]+v.vec_[3]*v.vec_[3];
}


inline Vec4f normalize (const Vec4f &v)
{
  Vec4f res;
  float norm=std::sqrt(v.vec_[0]*v.vec_[0]+v.vec_[1]*v.vec_[1]+v.vec_[2]*v.vec_[2]+v.vec_[3]*v.vec_[3]);
  res = v/norm;
  return res;
}
  


inline std::istream& operator>>(std::istream& is, Vec4f& v)
{ 
  v.read(is); 
  return is; 
}

// Stream insertion for Vec4f.
inline std::ostream& operator<<(std::ostream& os, const Vec4f& v)
{ 
  v.write(os); 
  return os; 
}

} //namespace siut

#endif // _SIUT_SIMD_STANDARD_VEC4F_HPP_







