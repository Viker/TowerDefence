/**********************************************************************
 * 
 *  File: 
 * 
 *  Created:
 *
 *  $Rev: 811 $ 
 *  $Id: Vec3f.hpp 811 2008-07-31 14:10:26Z karianc $
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

#ifndef _SIUT_SIMD_STANDARD_VEC3F_HPP_
#define _SIUT_SIMD_STANDARD_VEC3F_HPP_

#include <iostream>
#include <math.h>
#include <cmath>

namespace siut {

/** \brief Standard: class for doing vector length 3 calculations */

class Vec3f
{
    
public:
  
  /*-----------------------------------------------------------------------*/
  /*   Vec3f                                                               */
  /*-----------------------------------------------------------------------*/
  
  //constructor, elements are not initialized.
  inline Vec3f();

  inline Vec3f(float x, float y, float z);
  inline Vec3f(const float *pf);
  inline Vec3f(float tab[3]);
  inline Vec3f(const Vec3f &v);
  inline Vec3f(const float s);
  

  /*-----------------------------------------------------------------------*/
  /*    operators +  -  *  /                                               */
  /*-----------------------------------------------------------------------*/
  
  inline Vec3f operator + (const Vec3f &v) const;
  inline Vec3f operator + (const float s) const;
  
  inline Vec3f operator - (const Vec3f &v) const;
  inline Vec3f operator - (const float s) const;
  
  inline Vec3f operator * (const Vec3f &v) const; 
  inline Vec3f operator * (const float s) const;
  
  inline Vec3f operator / (const Vec3f &v) const; 
  inline Vec3f operator / (const float s) const;

  /*-----------------------------------------------------------------------*/
  /*    operators += -= *= /=                                              */
  /*-----------------------------------------------------------------------*/

  inline Vec3f & operator += (const Vec3f &v);
  inline Vec3f & operator += (const float s);

  inline Vec3f & operator -= (const Vec3f &v);
  inline Vec3f & operator -= (const float s);

  inline Vec3f & operator *= (const Vec3f &v); 
  inline Vec3f & operator *= (const float s);

  inline Vec3f & operator /= (const Vec3f &v); 
  inline Vec3f & operator /= (const float s);

  /*-----------------------------------------------------------------------*/
  /*    operators == != <= >= < >                                       */
  /*-----------------------------------------------------------------------*/

  inline bool operator == (const Vec3f &u) const;

  //comparison, checks if at least one corresponding element is different.
  inline bool operator != (const Vec3f &v) const; 

  inline bool operator <= (const Vec3f &v) const;
  inline bool operator >= (const Vec3f &v) const;
  inline bool operator < (const Vec3f &v) const;
  inline bool operator > (const Vec3f &v) const;

  /*-----------------------------------------------------------------------*/
  /*    functions dot boolean cross abs l_inf normalize is                 */
  /*-----------------------------------------------------------------------*/
  
  inline float dot (const Vec3f &v) const;

  /** \brief function, checks if any elements are 0, return true if zero elements are 0. */
  inline float boolean (const Vec3f &v) const;

  inline Vec3f cross (const Vec3f &v) const;
  inline void abs ();

  /** \brief function, returns the biggest number in absolute value. */
  inline float l_inf (const Vec3f &v) const;

  inline void normalize ();

  //sets the elements.
  inline void is (float x,  float y, float z);

  /*-----------------------------------------------------------------------*/
  /*    functions x() y() z()  vec_[]                                         */
  /*-----------------------------------------------------------------------*/

  inline const float & x() const;
  inline float & x();
  inline const float & y() const;
  inline float & y();
  inline const float & z() const;
  inline float & z();

  //returns the ite element in vector. (obs. first element har index 0)
  inline float & operator[](int i) { return vec_[i]; }
  inline const float & operator[](int i) const { return vec_[i]; }
  
  /*-----------------------------------------------------------------------*/
  /*    read  writhe                                                       */
  /*-----------------------------------------------------------------------*/

  inline void read(std::istream& is);
  inline void write(std::ostream& os) const;

  /*-----------------------------------------------------------------------*/
  /*    operators + - * / ^ with friend                                    */
  /*-----------------------------------------------------------------------*/

  inline friend Vec3f operator + (float s, const Vec3f &v); 
  inline friend Vec3f operator - (float s, const Vec3f &v); 
  inline friend Vec3f operator * (float s, const Vec3f &v); 
 
  /** \brief only ^2 and ^3 (anything but 2 gives 3) */
  inline friend Vec3f operator ^ (const Vec3f &v, int i);

  /*-----------------------------------------------------------------------*/
  /*    functions dot max min sqrt length normalize with friend            */
  /*-----------------------------------------------------------------------*/  

  inline friend float dot (const Vec3f &u, const Vec3f &v);

  //maximums of two vectors, ie. returns a vector with the maximums of the corresponding elements.
  inline friend Vec3f max_vec (const Vec3f &u , const Vec3f &v);

  //minima of two vectors, ie. returns a vector with the minima of the corresponding elements.
  inline friend Vec3f min_vec (const Vec3f &u , const Vec3f &v);

  inline friend Vec3f sqrt (const Vec3f &v);

  /** \brief function, calculates the length of a vector, ie. the square root of the sum of the element squared. */
  inline friend float length (const Vec3f &v);

  /** \brief function, calculates the length of a vector, ie. the sum of the element squared. */
  inline friend float length_2 (const Vec3f &v);

  inline friend Vec3f normalize (const Vec3f &v);

private:

  float vec_[3] ;
};
  /*
/// Stream extraction for Vec3f.
  std::istream& operator>>(std::istream& is, Vec3f& v);

/// Stream insertion for Vec3f.
std::ostream& operator<<(std::ostream& os, const Vec3f& v);
  */

  /*-----------------------------------------------------------------------*/
  /*    IMPLEMENTATION                                                     */
  /*-----------------------------------------------------------------------*/
    /*-----------------------------------------------------------------------*/
  /*   Vec3f                                                               */
  /*-----------------------------------------------------------------------*/
  
  Vec3f::Vec3f()
  {
  }

  Vec3f::Vec3f( float x,  float y, float z)
  {
    vec_[0]=x;
    vec_[1]=y;
    vec_[2]=z;
  }
  
  Vec3f::Vec3f(const float *pf)
  {
    vec_[0]=pf[0];
    vec_[1]=pf[1];
    vec_[2]=pf[2];
  }
  
  Vec3f::Vec3f(float tab[3])
  {
    vec_[0]=tab[0];
    vec_[1]=tab[1];
    vec_[2]=tab[2];
  }
  
  Vec3f::Vec3f(const Vec3f &v)
  {
    vec_[0]=v.vec_[0];
    vec_[1]=v.vec_[1];
    vec_[2]=v.vec_[2];
  }
  
  Vec3f::Vec3f(const float s)
  {
    for (int i = 0; i < 3; ++i)
      vec_[i] = s;
  }

  /*-----------------------------------------------------------------------*/
  /*    operators +  -  *  /                                               */
  /*-----------------------------------------------------------------------*/
  
  
  //operators +
  inline Vec3f Vec3f::operator + (const Vec3f &v) const
  {   
    Vec3f res(*this);
    res += v;
    return res;
  }
  inline Vec3f Vec3f::operator + (const float s) const
  {   
    Vec3f res(*this);
    res += s;
    return res;
  }
  
  
  //operators -
  inline Vec3f Vec3f::operator - (const Vec3f &v) const
  {   
    Vec3f res(*this);
    res -= v;
    return res;
  }
  inline Vec3f Vec3f::operator - (const float s) const
  {   
    Vec3f res(*this);
    res -= s;
    return res;
  }


  //operators *
  inline Vec3f Vec3f::operator * (const Vec3f &v) const
  {   
    Vec3f res(*this);
    res *= v;
    return res;
  }
  inline Vec3f Vec3f::operator * (const float s) const
  {   
    Vec3f res(*this);
    res *= s;
    return res;
  }


  //operators /
  Vec3f Vec3f::operator / (const Vec3f &v) const
  {   
    Vec3f res(*this);
    res /= v;
    return res;
  }
  inline Vec3f Vec3f::operator / (const float s) const
  {   
    Vec3f res(*this);
    res /= s;
    return res;
  }

  /*-----------------------------------------------------------------------*/
  /*    operators += -= *= /=                                              */
  /*-----------------------------------------------------------------------*/

  inline Vec3f &  Vec3f::operator += (const Vec3f &v)
  {
    vec_[0]+=v.vec_[0];
    vec_[1]+=v.vec_[1];
    vec_[2]+=v.vec_[2];
    return *this;
  }
  inline Vec3f & Vec3f::operator += (const float s)
  {
    vec_[0] += s;
    vec_[1] += s;
    vec_[2] += s;
    return *this;
  }
  
  inline Vec3f &  Vec3f::operator -= (const Vec3f &v)
  {
    vec_[0]-=v.vec_[0];
    vec_[1]-=v.vec_[1];
    vec_[2]-=v.vec_[2];
    return *this;
  } 
  inline Vec3f & Vec3f::operator -= (const float s)
  {
    vec_[0] -= s;
    vec_[1] -= s;
    vec_[2] -= s;
    return *this;
  }
  
  inline Vec3f &  Vec3f::operator *= (const Vec3f &v)
  {
    vec_[0]*=v.vec_[0];
    vec_[1]*=v.vec_[1];
    vec_[2]*=v.vec_[2];
    return *this;
  }
  inline Vec3f & Vec3f::operator *= (const float s)
  {
    vec_[0] *= s;
    vec_[1] *= s;
    vec_[2] *= s;
    return *this;
  }
  
  inline Vec3f &  Vec3f::operator /= (const Vec3f &v)
  {
    vec_[0]/=v.vec_[0];
    vec_[1]/=v.vec_[1];
    vec_[2]/=v.vec_[2];
    return *this;
  }
  inline Vec3f & Vec3f::operator /= (const float s)
  {
    vec_[0] /= s;
    vec_[1] /= s;
    vec_[2] /= s;
    return *this;
  }
  
  /*-----------------------------------------------------------------------*/
  /*    operators == != <= >= < >                                       */
  /*-----------------------------------------------------------------------*/

  //operator ==
  inline bool Vec3f::operator == (const Vec3f &u) const
  {    
    float res[3];
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
    
    if (res[0] * res[1] * res[2] == 0)
      {return 0;}
    else 
      {return 1;}
  } 
  
  
  //operator != 
  //forskjellig hvis ett tall er forskjellig
  inline bool Vec3f::operator != (const Vec3f &u) const
  {    
    float res[3];
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
    
    if (res[0] * res[1] * res[2] == 0)
      {return 1;}
    else 
      {return 0;}
  } 


  //operator <=
  inline bool Vec3f::operator <= (const Vec3f &u) const
  {    
    float res[3];
    if (vec_[0]<=u.vec_[0])
      res[0]=1.;
    else   
      res[0]=0.;
    if (vec_[1]<=u.vec_[1])
      res[1]=1.;
    else   
      res[1]=0.;
    if (vec_[2]<=u.vec_[2])
      res[2]=1.;
    else   
      res[2]=0.;
    
    if (res[0] * res[1] * res[2] == 0)
      {return 0;}
    else 
      {return 1;}
  } 
  
  //operator >=
  inline bool Vec3f::operator >= (const Vec3f &u) const
  {    
    float res[3];
    if (vec_[0]>=u.vec_[0])
      res[0]=1.;
    else   
      res[0]=0.;
    if (vec_[1]>=u.vec_[1])
      res[1]=1.;
    else   
      res[1]=0.;
    if (vec_[2]>=u.vec_[2])
      res[2]=1.;
    else   
      res[2]=0.;
    
    if (res[0] * res[1] * res[2] == 0)
      {return 0;}
    else 
      {return 1;}
  } 
  
  //operator <
  inline bool Vec3f::operator < (const Vec3f &u) const
  {    
    float res[3];
    if (vec_[0]<u.vec_[0])
      res[0]=1.;
    else   
      res[0]=0.;
    if (vec_[1]<u.vec_[1])
      res[1]=1.;
    else   
      res[1]=0.;
    if (vec_[2]<u.vec_[2])
      res[2]=1.;
    else   
      res[2]=0.;
    
    if (res[0] * res[1] * res[2] == 0)
      {return 0;}
    else 
      {return 1;}
  } 


  //operator >=
  inline bool Vec3f::operator > (const Vec3f &u) const
  {    
    float res[3];
    if (vec_[0]>u.vec_[0])
      res[0]=1.;
    else   
      res[0]=0.;
    if (vec_[1]>u.vec_[1])
      res[1]=1.;
    else   
      res[1]=0.;
    if (vec_[2]>u.vec_[2])
      res[2]=1.;
    else   
      res[2]=0.;
    
    if (res[0] * res[1] * res[2] == 0)
      {return 0;}
    else 
      {return 1;}
  } 

  /*-----------------------------------------------------------------------*/
  /*    functions dot boolean cross abs l_inf normalize is                 */
  /*-----------------------------------------------------------------------*/

  //operator dot (scalar product)
  inline float Vec3f::dot (const Vec3f &v) const
  {   
    return(vec_[0]*v.vec_[0] + vec_[1]*v.vec_[1] + vec_[2]*v.vec_[2] );
  }

  //operator boolean
  inline float Vec3f::boolean (const Vec3f &v) const
  {   
    if (v.vec_[0] * v.vec_[1] * v.vec_[2] == 0)
      {return 0;}
    else 
      {return 1;}
  }

  //operator cross
  inline Vec3f Vec3f::cross (const Vec3f &v) const
  {   
    Vec3f res(*this);
    Vec3f aux;
    aux.vec_[0] = res.vec_[1] * v.vec_[2] - v.vec_[1] * res.vec_[2];
    aux.vec_[1] = res.vec_[2] * v.vec_[0] - v.vec_[2] * res.vec_[0];
    aux.vec_[2] = res.vec_[0] * v.vec_[1] - v.vec_[0] * res.vec_[1];
    return aux;
  }

  //func abs
  inline void Vec3f::abs ()
  {
    Vec3f res(*this);
    if (res.vec_[0] < 0)
      vec_[0] = res.vec_[0] * (-1);
    if (res.vec_[1] < 0)
      vec_[1] = res.vec_[1] * (-1);
    if (res.vec_[2] < 0)
      vec_[2] = res.vec_[2] * (-1);
  }

  //func l_inf
  inline float Vec3f::l_inf (const Vec3f &v) const
  {
    float f;
    float g;
    Vec3f res;
    
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

    if (res.vec_[0] >= res.vec_[1])
      f = res.vec_[0];
    else 
      f = res.vec_[1];
    
      g = res.vec_[2];
    
    if (g >= f)
      return g;
    else 
      return f;
  }

  //func normalize
  inline void Vec3f::normalize ()
  {   
    float length=std::sqrt(vec_[0]*vec_[0] + vec_[1]*vec_[1] + vec_[2]*vec_[2]);
    vec_[0]/=length;
    vec_[1]/=length;
    vec_[2]/=length;
  }

  //func is
  inline void Vec3f::is (float x, float y, float z)
  {   
    vec_[0] = x;
    vec_[1] = y;
    vec_[2] = z;
  }

  /*-----------------------------------------------------------------------*/
  /*    functions x() y() z()                                              */
  /*-----------------------------------------------------------------------*/

  inline const float & Vec3f::x() const 
  {    return vec_[0];  }

  inline float & Vec3f::x()
  {    return vec_[0];  }
  
  inline const float & Vec3f::y() const 
  {    return vec_[1];  } 
  
  inline float & Vec3f::y() 
  {    return vec_[1];  }
  
  inline const float & Vec3f::z() const 
  {    return vec_[2];  } 
  
  inline float & Vec3f::z() 
  {    return vec_[2];  }
  
  /*-----------------------------------------------------------------------*/
  /*    read  writhe                                                       */
  /*-----------------------------------------------------------------------*/

  //operators read write
  inline void Vec3f::read(std::istream& is)
  {
    is >> vec_[0] >> vec_[1] >> vec_[2] ;
  }
  
  inline void Vec3f::write(std::ostream& os) const
  {
    os << vec_[0] << " "
       << vec_[1] << " "
       << vec_[2];
  }

  /*-----------------------------------------------------------------------*/
  /*    operators + - * / ^ with friend                                    */
  /*-----------------------------------------------------------------------*/

  //operators + - * / ^ with friend
  inline Vec3f operator + (float s, const Vec3f &v)
  {   
    Vec3f res(s);
    res += v;
    return res;
  }
  
  inline Vec3f operator - (float s, const Vec3f &v)
  {   
    Vec3f res(s);
    res -= v;
    return res;
  }
  
  inline Vec3f operator * (float s, const Vec3f &v)
  {   
    Vec3f res(s);
    res *= v;
    return res;
  }
  
  inline Vec3f operator ^ (const Vec3f &v, int i)
  {   
    Vec3f res;
    if (i == 2)
      {
	res.vec_[0]=v.vec_[0]*v.vec_[0];
	res.vec_[1]=v.vec_[1]*v.vec_[1];
	res.vec_[2]=v.vec_[2]*v.vec_[2];
      }
    else 
      {
	res.vec_[0]=v.vec_[0]*v.vec_[0]*v.vec_[0];
	res.vec_[1]=v.vec_[1]*v.vec_[1]*v.vec_[1];
	res.vec_[2]=v.vec_[2]*v.vec_[2]*v.vec_[2];
      }
    return res;
  }
  
  /*-----------------------------------------------------------------------*/
  /*    functions dot max min sqrt length normalize with friend            */
  /*-----------------------------------------------------------------------*/  

  //func dot with friend
  
  inline float dot (const Vec3f &u, const Vec3f &v) 
  {   
    return(u.vec_[0]*v.vec_[0] + u.vec_[1]*v.vec_[1] + u.vec_[2]*v.vec_[2] );
  }

  //func max/min with friend

  inline Vec3f min_vec (const Vec3f &u , const Vec3f &v) 
  {   
    Vec3f res;
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
    return res;
}
  
  
  inline Vec3f max_vec (const Vec3f &u , const Vec3f &v) 
  {   
    Vec3f res;
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
    return res;
  }
  
  //operator sqrt 
  inline Vec3f sqrt (const Vec3f &v)
  {   
    Vec3f res;
    res.vec_[0] = std::sqrt(v.vec_[0]);
    res.vec_[1] = std::sqrt(v.vec_[1]);
    res.vec_[2] = std::sqrt(v.vec_[2]);
    return res;
  }

  //operator length 
  inline float length (const Vec3f &v)
  {   
    return std::sqrt(v.vec_[0]*v.vec_[0]+v.vec_[1]*v.vec_[1]+v.vec_[2]*v.vec_[2]);
  }
  
  //operator length_2 
  inline float length_2 (const Vec3f &v)
  {   
    return (v.vec_[0]*v.vec_[0]+v.vec_[1]*v.vec_[1]+v.vec_[2]*v.vec_[2]);
  }
  
  inline Vec3f normalize (const Vec3f &v)
  {
    Vec3f res;
    float norm=(v.vec_[0]*v.vec_[0]+v.vec_[1]*v.vec_[1]+v.vec_[2]*v.vec_[2]);
    
    res = std::sqrt(norm);
    res = v/res;
    return res;
  }
  
  inline std::istream& operator>>(std::istream& is, Vec3f& v)
  { 
    v.read(is); 
    return is; 
  }
  
  // Stream insertion for Vec3f.
  inline std::ostream& operator<<(std::ostream& os, const Vec3f& v)
  { 
    v.write(os); 
    return os; 
  }
  
} //namespace siut

#endif // _SIUT_SIMD_STANDARD_VEC3F_HPP_






