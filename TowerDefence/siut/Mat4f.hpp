/**********************************************************************
 * 
 *  File: 
 * 
 *  Created:
 *
 *  $Rev: 37 $ 
 *  $Id: Mat4f.hpp 37 2007-08-02 10:21:51Z kchriste $
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

#ifndef _SIUT_SIMD_STANDARD_MAT4F_HPP_
#define _SIUT_SIMD_STANDARD_MAT4F_HPP_

#include <iostream>
#include <math.h>
#include <cmath>
#include "Vec4f.hpp"
#include "Vec3f.hpp"

namespace siut {

#define M_PI 3.1415926
/** \brief Standard: class for doing matrix 4x4 calculations */

class Mat4f
{

public:

  /*-----------------------------------------------------------------------*/
  /*   Mat4f                                                               */
  /*-----------------------------------------------------------------------*/ 

  //constructor, elements are not initialized.
  inline Mat4f();

  //constructor, initializes colum 1, colum 2, colum 3 and colum 4.
  inline Mat4f(const Vec4f &x, const Vec4f &y, const Vec4f &z, const Vec4f &w);

  //by columns
  inline Mat4f(float m_11, float m_21, float m_31, float m_41, 
        float m_12, float m_22, float m_32, float m_42,
        float m_13, float m_23, float m_33, float m_43,
        float m_14, float m_24, float m_34, float m_44);
  
  inline Mat4f(const float *pf);

  //constructor, initializes colum 1, colum 2, colum 3 and colum 4.
  inline Mat4f(float tab1[4] , float tab2[4] , float tab3[4] , float tab4[4]);

  //by columns
  inline Mat4f(float tab[16]);

  inline Mat4f(const Mat4f &v);
  inline Mat4f(const float s);
  
  /*-----------------------------------------------------------------------*/
  /*    operators +  -  *  /                                                */
  /*-----------------------------------------------------------------------*/

  inline Mat4f operator + (const Mat4f &m) const;
  inline Mat4f operator + (const float s) const;

  inline Mat4f operator - (const Mat4f &m) const;
  inline Mat4f operator - (const float s) const;

  //matrix times matrix
  inline Mat4f operator * (const Mat4f &m) const;

  //matrix times vector
  inline Vec4f operator * (const Vec4f &v) const;

  inline Mat4f operator * (const float s) const;

  inline Mat4f operator / (const float s) const;


  /*-----------------------------------------------------------------------*/
  /*    operators += -= *= /=                                              */
  /*-----------------------------------------------------------------------*/
  
  inline void operator += (const Mat4f &m);
  inline void operator += (const float s);

  inline void operator -= (const Mat4f &m);
  inline void operator -= (const float s);

  //matrix times matrix
  inline void operator *= (const Mat4f &m);
  inline void operator *= (const float s);

  inline void operator /= (const float s);

  /*-----------------------------------------------------------------------*/
  /*    operators == !=                                                    */
  /*-----------------------------------------------------------------------*/
  
  inline bool operator == (const Mat4f &u) const;

  //comparison, checks if at least one corresponding element is different.
  inline bool operator != (const Mat4f &v) const;

  /*-----------------------------------------------------------------------*/
  /*    functions abs inverse det rotate translate setM...                 */
  /*-----------------------------------------------------------------------*/
  
  inline void abs ();


  //inverse and inverse_2 does the same, check whitch i quickest
  inline Mat4f inverse () const;
  inline Mat4f inverse_2 () const;

  /** \brief for matrix of form: row 4: [0 0 0 1] */
  inline Mat4f inverse_3x3 () const;
  /** \brief for matrix of form: row 4: [0 0 0 1] */
  inline float det_3x3 () const;

  inline float det_4x4 () const;

  inline void rotateX(float a);
  inline void rotateY(float a);
  inline void rotateZ(float a);
  
  inline void translate(const Vec3f &v);	 
  inline void translate(float x, float y, float z);
  
  inline void setIdentity () ;  
  
  inline void setFrustumMatrix(float left, float right, float bottom, float top, float near, float far);
  inline void setPerspectiveMatrix(float fovy, float aspect, float zNear, float zFar);
  
  inline Vec3f rotateVector(const Vec3f &v);
  
  /*-----------------------------------------------------------------------*/
  /*    functions c1 c2 c3 c4 r1 r2 r3 r4 []  ()                           */
  /*-----------------------------------------------------------------------*/
  
  //returns columns
  inline const Vec4f c1(const Mat4f &m) const;
  inline Vec4f c1(const Mat4f &m) ;
  inline const Vec4f c2(const Mat4f &m) const;
  inline Vec4f c2(const Mat4f &m) ;
  inline const Vec4f c3(const Mat4f &m) const;
  inline Vec4f c3(const Mat4f &m) ;
  inline const Vec4f c4(const Mat4f &m) const;
  inline Vec4f c4(const Mat4f &m) ;
  
  //returns rows
  inline const Vec4f r1(const Mat4f &m) const;
  inline Vec4f r1(const Mat4f &m) ;
  inline const Vec4f r2(const Mat4f &m) const;
  inline Vec4f r2(const Mat4f &m) ;
  inline const Vec4f r3(const Mat4f &m) const;
  inline Vec4f r3(const Mat4f &m) ;
  inline const Vec4f r4(const Mat4f &m) const;
  inline Vec4f r4(const Mat4f &m) ;


  /** \brief returns the ite element by columns. (obs. first element har index 0) */
  inline float & operator[](int i) { return v16[i]; }
  /** \brief returns the ite element by columns. (obs. first element har index 0) */
  inline const float & operator[](int i) const { return v16[i]; }

  /** \brief returns element (i,j), where i is column, and j is row) */
  inline float & operator()(int i, int j) { return v16[(i * 4) + j]; }
  /** \brief returns element (i,j), where i is column, and j is row) */
  inline const float & operator()(int i, int j) const { return v16[(i * 4) + j]; }
  
  /*-----------------------------------------------------------------------*/
  /*    read  writhe                                                       */
  /*-----------------------------------------------------------------------*/

  inline void read(std::istream& is);
  inline void write(std::ostream& os) const;

  /*-----------------------------------------------------------------------*/
  /*    operators + - * /  with friend                                     */
  /*-----------------------------------------------------------------------*/
  
  inline friend Mat4f operator + (float s, const Mat4f &v); 
  inline friend Mat4f operator - (float s, const Mat4f &v); 
  inline friend Mat4f operator * (float s, const Mat4f &v); 
  
  //vector times matrix
  inline friend Vec4f operator * (const Vec4f &v, const Mat4f &m);
  
  /*-----------------------------------------------------------------------*/
  /*    functions max min trace transpose with friend                                   */
  /*-----------------------------------------------------------------------*/  
  
  //maximums of two matrixes, ie. returns a matrix with the maximums of the corresponding elements.
  inline friend Mat4f max_mat (const Mat4f &u , const Mat4f &v);

  //minima of two matrixes, ie. returns a matrix with the minima of the corresponding elements.
  inline friend Mat4f min_mat (const Mat4f &u , const Mat4f &v);

  inline friend Mat4f transpose (const Mat4f &m);
  inline friend float trace (const Mat4f &m);
  
private:
  
  float v16[16];
  
};
  /*  
/// Stream extraction for SMat4f.
  std::istream& operator>>(std::istream& is, Mat4f& v);

/// Stream insertion for SMat4f.
std::ostream& operator<<(std::ostream& os, const Mat4f& v);
  */

  /*-----------------------------------------------------------------------*/
  /*    IMPLEMENTATION                                                     */
  /*-----------------------------------------------------------------------*/
  /*-----------------------------------------------------------------------*/
  /*   Mat4f                                                               */
  /*-----------------------------------------------------------------------*/ 


  Mat4f::Mat4f()
  { 
  }
  
  Mat4f::Mat4f(const Vec4f &x, const Vec4f &y, const Vec4f &z, const Vec4f &w)
  {
    v16[0 ] = x. x();
    v16[1 ] = x. y();
    v16[2 ] = x. z();
    v16[3 ] = x. w();
    
    v16[4 ] = y. x();
    v16[5 ] = y. y();
    v16[6 ] = y. z();
    v16[7 ] = y. w();

    v16[8 ] = z. x();
    v16[9 ] = z. y();
    v16[10] = z. z();
    v16[11] = z. w();
    
    v16[12] = w. x();
    v16[13] = w. y();
    v16[14] = w. z();
    v16[15] = w. w();
  }
  
  //by columns
  Mat4f::Mat4f(float m_11, float m_21, float m_31, float m_41, 
	       float m_12, float m_22, float m_32, float m_42,
	       float m_13, float m_23, float m_33, float m_43,
	       float m_14, float m_24, float m_34, float m_44)
  {
    v16[0 ] = m_11;
    v16[1 ] = m_21;
    v16[2 ] = m_31;
    v16[3 ] = m_41;
    
    v16[4 ] = m_12;
    v16[5 ] = m_22;
    v16[6 ] = m_32;
    v16[7 ] = m_42;

    v16[8 ] = m_13;
    v16[9 ] = m_23;
    v16[10] = m_33;
    v16[11] = m_43;
    
    v16[12] = m_14;
    v16[13] = m_24;
    v16[14] = m_34;
    v16[15] = m_44;  
  }
  
  Mat4f::Mat4f(const float *pf)
  {
    v16[0 ] = pf[0 ];
    v16[1 ] = pf[1 ];
    v16[2 ] = pf[2 ];
    v16[3 ] = pf[3 ];
    
    v16[4 ] = pf[4 ];
    v16[5 ] = pf[5 ];
    v16[6 ] = pf[6 ];
    v16[7 ] = pf[7 ];

    v16[8 ] = pf[8 ];
    v16[9 ] = pf[9 ];
    v16[10] = pf[10];
    v16[11] = pf[11];
    
    v16[12] = pf[12];
    v16[13] = pf[13];
    v16[14] = pf[14];
    v16[15] = pf[15];
  }
  
  Mat4f::Mat4f(float tab1[4] , float tab2[4] , float tab3[4] , float tab4[4])
  {
    v16[0 ] = tab1[0 ];
    v16[1 ] = tab1[1 ];
    v16[2 ] = tab1[2 ];
    v16[3 ] = tab1[3 ];
    
    v16[4 ] = tab2[0 ];
    v16[5 ] = tab2[1 ];
    v16[6 ] = tab2[2 ];
    v16[7 ] = tab2[3 ];

    v16[8 ] = tab3[0 ];
    v16[9 ] = tab3[1 ];
    v16[10] = tab3[2 ];
    v16[11] = tab3[3 ];
    
    v16[12] = tab4[0 ];
    v16[13] = tab4[1 ];
    v16[14] = tab4[2 ];
    v16[15] = tab4[3 ];
  }
  
  Mat4f::Mat4f(float tab[16])
  {
    v16[0 ] = tab[0 ];
    v16[1 ] = tab[1 ];
    v16[2 ] = tab[2 ];
    v16[3 ] = tab[3 ];
    
    v16[4 ] = tab[4 ];
    v16[5 ] = tab[5 ];
    v16[6 ] = tab[6 ];
    v16[7 ] = tab[7 ];

    v16[8 ] = tab[8 ];
    v16[9 ] = tab[9 ];
    v16[10] = tab[10];
    v16[11] = tab[11];
    
    v16[12] = tab[12];
    v16[13] = tab[13];
    v16[14] = tab[14];
    v16[15] = tab[15];
  }
  
  Mat4f::Mat4f(const Mat4f &v)
  {
    v16[0 ] = v.v16[0 ];
    v16[1 ] = v.v16[1 ];
    v16[2 ] = v.v16[2 ];
    v16[3 ] = v.v16[3 ];
    
    v16[4 ] = v.v16[4 ];
    v16[5 ] = v.v16[5 ];
    v16[6 ] = v.v16[6 ];
    v16[7 ] = v.v16[7 ];

    v16[8 ] = v.v16[8 ];
    v16[9 ] = v.v16[9 ];
    v16[10] = v.v16[10];
    v16[11] = v.v16[11];
    
    v16[12] = v.v16[12];
    v16[13] = v.v16[13];
    v16[14] = v.v16[14];
    v16[15] = v.v16[15];
  }
  
  Mat4f::Mat4f(const float s)  
  {
    v16[0 ] = s;
    v16[1 ] = s;
    v16[2 ] = s;
    v16[3 ] = s;
    
    v16[4 ] = s;
    v16[5 ] = s;
    v16[6 ] = s;
    v16[7 ] = s;
    
    v16[8 ] = s;
    v16[9 ] = s;
    v16[10] = s;
    v16[11] = s;
    
    v16[12] = s;
    v16[13] = s;
    v16[14] = s;
    v16[15] = s;
  } 
  
  /*-----------------------------------------------------------------------*/
  /*    operators +  -  *  /                                               */
  /*-----------------------------------------------------------------------*/
  
  //operators +
  inline Mat4f Mat4f::operator + (const Mat4f &m) const
  {   
    Mat4f res(*this);
    res += m;
    return res;
  }
  inline Mat4f Mat4f::operator + (const float s) const
  {   
    Mat4f res(*this);
    res += s;
    return res;
  }
  
  
  //operators -
  inline Mat4f Mat4f::operator - (const Mat4f &m) const
  {   
    Mat4f res(*this);
    res -= m;
    return res;
  }
  inline Mat4f Mat4f::operator - (const float s) const
  {   
    Mat4f res(*this);
    res -= s;
    return res;
  }

  
  //operators *
  inline Mat4f Mat4f::operator * (const Mat4f &m) const
  {   
    Mat4f res(*this);
    Mat4f aux;

    aux.v16[ 0] = res.v16[0]*m.v16[ 0] + res.v16[4]*m.v16[ 1] + res.v16[ 8]*m.v16[ 2] + res.v16[12]*m.v16[ 3];
    aux.v16[ 1] = res.v16[1]*m.v16[ 0] + res.v16[5]*m.v16[ 1] + res.v16[ 9]*m.v16[ 2] + res.v16[13]*m.v16[ 3];
    aux.v16[ 2] = res.v16[2]*m.v16[ 0] + res.v16[6]*m.v16[ 1] + res.v16[10]*m.v16[ 2] + res.v16[14]*m.v16[ 3];
    aux.v16[ 3] = res.v16[3]*m.v16[ 0] + res.v16[7]*m.v16[ 1] + res.v16[11]*m.v16[ 2] + res.v16[15]*m.v16[ 3];

    aux.v16[ 4] = res.v16[0]*m.v16[ 4] + res.v16[4]*m.v16[ 5] + res.v16[ 8]*m.v16[ 6] + res.v16[12]*m.v16[ 7];
    aux.v16[ 5] = res.v16[1]*m.v16[ 4] + res.v16[5]*m.v16[ 5] + res.v16[ 9]*m.v16[ 6] + res.v16[13]*m.v16[ 7];
    aux.v16[ 6] = res.v16[2]*m.v16[ 4] + res.v16[6]*m.v16[ 5] + res.v16[10]*m.v16[ 6] + res.v16[14]*m.v16[ 7]; 
    aux.v16[ 7] = res.v16[3]*m.v16[ 4] + res.v16[7]*m.v16[ 5] + res.v16[11]*m.v16[ 6] + res.v16[15]*m.v16[ 7];

    aux.v16[ 8] = res.v16[0]*m.v16[ 8] + res.v16[4]*m.v16[ 9] + res.v16[ 8]*m.v16[10] + res.v16[12]*m.v16[11];
    aux.v16[ 9] = res.v16[1]*m.v16[ 8] + res.v16[5]*m.v16[ 9] + res.v16[ 9]*m.v16[10] + res.v16[13]*m.v16[11];
    aux.v16[10] = res.v16[2]*m.v16[ 8] + res.v16[6]*m.v16[ 9] + res.v16[10]*m.v16[10] + res.v16[14]*m.v16[11]; 
    aux.v16[11] = res.v16[3]*m.v16[ 8] + res.v16[7]*m.v16[ 9] + res.v16[11]*m.v16[10] + res.v16[15]*m.v16[11];
    
    aux.v16[12] = res.v16[0]*m.v16[12] + res.v16[4]*m.v16[13] + res.v16[ 8]*m.v16[14] + res.v16[12]*m.v16[15];
    aux.v16[13] = res.v16[1]*m.v16[12] + res.v16[5]*m.v16[13] + res.v16[ 9]*m.v16[14] + res.v16[13]*m.v16[15];
    aux.v16[14] = res.v16[2]*m.v16[12] + res.v16[6]*m.v16[13] + res.v16[10]*m.v16[14] + res.v16[14]*m.v16[15]; 
    aux.v16[15] = res.v16[3]*m.v16[12] + res.v16[7]*m.v16[13] + res.v16[11]*m.v16[14] + res.v16[15]*m.v16[15];

    return aux;
  }
  inline Vec4f Mat4f::operator * (const Vec4f &v) const
  {
    Mat4f res(*this);
    Vec4f aux;

    aux[0] = v[0]*res.v16[0] + v[1]*res.v16[4] + v[2]*res.v16[8 ] + v[3]*res.v16[12];
    aux[1] = v[0]*res.v16[1] + v[1]*res.v16[5] + v[2]*res.v16[9 ] + v[3]*res.v16[13];
    aux[2] = v[0]*res.v16[2] + v[1]*res.v16[6] + v[2]*res.v16[10] + v[3]*res.v16[14];
    aux[3] = v[0]*res.v16[3] + v[1]*res.v16[7] + v[2]*res.v16[11] + v[3]*res.v16[15];

    return aux;
  }

  inline Mat4f Mat4f::operator * (const float s) const
  {   
    Mat4f res(*this);
    res *= s;
    return res;
  }
  
  inline Mat4f Mat4f::operator / (const float s) const
  {   
    Mat4f res(*this);
    res /= s;
    return res;
  }
  
  /*-----------------------------------------------------------------------*/
  /*    operators +=  -=  *= /=                                            */
  /*-----------------------------------------------------------------------*/
 
  inline void Mat4f::operator += (const Mat4f &m)
  {
    v16[0 ] += m.v16[0 ];
    v16[1 ] += m.v16[1 ];
    v16[2 ] += m.v16[2 ];
    v16[3 ] += m.v16[3 ];
    
    v16[4 ] += m.v16[4 ];
    v16[5 ] += m.v16[5 ];
    v16[6 ] += m.v16[6 ];
    v16[7 ] += m.v16[7 ];
    
    v16[8 ] += m.v16[8 ];
    v16[9 ] += m.v16[9 ];
    v16[10] += m.v16[10];
    v16[11] += m.v16[11];
    
    v16[12] += m.v16[12];
    v16[13] += m.v16[13];
    v16[14] += m.v16[14];
    v16[15] += m.v16[15];
  }
  inline void Mat4f::operator += (const float s)
  {
    v16[0 ] += s;
    v16[1 ] += s;
    v16[2 ] += s;
    v16[3 ] += s;
    
    v16[4 ] += s;
    v16[5 ] += s;
    v16[6 ] += s;
    v16[7 ] += s;
    
    v16[8 ] += s;
    v16[9 ] += s;
    v16[10] += s;
    v16[11] += s;
    
    v16[12] += s;
    v16[13] += s;
    v16[14] += s;
    v16[15] += s;
  }

  inline void Mat4f::operator -= (const Mat4f &m)
  {
    v16[0 ] -= m.v16[0 ];
    v16[1 ] -= m.v16[1 ];
    v16[2 ] -= m.v16[2 ];
    v16[3 ] -= m.v16[3 ];
    
    v16[4 ] -= m.v16[4 ];
    v16[5 ] -= m.v16[5 ];
    v16[6 ] -= m.v16[6 ];
    v16[7 ] -= m.v16[7 ];
    
    v16[8 ] -= m.v16[8 ];
    v16[9 ] -= m.v16[9 ];
    v16[10] -= m.v16[10];
    v16[11] -= m.v16[11];
    
    v16[12] -= m.v16[12];
    v16[13] -= m.v16[13];
    v16[14] -= m.v16[14];
    v16[15] -= m.v16[15];
  } 
  inline void Mat4f::operator -= (const float s)
  {
    v16[0 ] -= s;
    v16[1 ] -= s;
    v16[2 ] -= s;
    v16[3 ] -= s;
    
    v16[4 ] -= s;
    v16[5 ] -= s;
    v16[6 ] -= s;
    v16[7 ] -= s;
    
    v16[8 ] -= s;
    v16[9 ] -= s;
    v16[10] -= s;
    v16[11] -= s;
    
    v16[12] -= s;
    v16[13] -= s;
    v16[14] -= s;
    v16[15] -= s;
  }
  
  inline void Mat4f::operator *= (const Mat4f &m)
  {  
    Mat4f res(*this);

    v16[ 0] = res.v16[0]*m.v16[ 0] + res.v16[4]*m.v16[ 1] + res.v16[ 8]*m.v16[ 2] + res.v16[12]*m.v16[ 3];
    v16[ 1] = res.v16[1]*m.v16[ 0] + res.v16[5]*m.v16[ 1] + res.v16[ 9]*m.v16[ 2] + res.v16[13]*m.v16[ 3];
    v16[ 2] = res.v16[2]*m.v16[ 0] + res.v16[6]*m.v16[ 1] + res.v16[10]*m.v16[ 2] + res.v16[14]*m.v16[ 3];
    v16[ 3] = res.v16[3]*m.v16[ 0] + res.v16[7]*m.v16[ 1] + res.v16[11]*m.v16[ 2] + res.v16[15]*m.v16[ 3];

    v16[ 4] = res.v16[0]*m.v16[ 4] + res.v16[4]*m.v16[ 5] + res.v16[ 8]*m.v16[ 6] + res.v16[12]*m.v16[ 7];
    v16[ 5] = res.v16[1]*m.v16[ 4] + res.v16[5]*m.v16[ 5] + res.v16[ 9]*m.v16[ 6] + res.v16[13]*m.v16[ 7];
    v16[ 6] = res.v16[2]*m.v16[ 4] + res.v16[6]*m.v16[ 5] + res.v16[10]*m.v16[ 6] + res.v16[14]*m.v16[ 7]; 
    v16[ 7] = res.v16[3]*m.v16[ 4] + res.v16[7]*m.v16[ 5] + res.v16[11]*m.v16[ 6] + res.v16[15]*m.v16[ 7];

    v16[ 8] = res.v16[0]*m.v16[ 8] + res.v16[4]*m.v16[ 9] + res.v16[ 8]*m.v16[10] + res.v16[12]*m.v16[11];
    v16[ 9] = res.v16[1]*m.v16[ 8] + res.v16[5]*m.v16[ 9] + res.v16[ 9]*m.v16[10] + res.v16[13]*m.v16[11];
    v16[10] = res.v16[2]*m.v16[ 8] + res.v16[6]*m.v16[ 9] + res.v16[10]*m.v16[10] + res.v16[14]*m.v16[11]; 
    v16[11] = res.v16[3]*m.v16[ 8] + res.v16[7]*m.v16[ 9] + res.v16[11]*m.v16[10] + res.v16[15]*m.v16[11];
    
    v16[12] = res.v16[0]*m.v16[12] + res.v16[4]*m.v16[13] + res.v16[ 8]*m.v16[14] + res.v16[12]*m.v16[15];
    v16[13] = res.v16[1]*m.v16[12] + res.v16[5]*m.v16[13] + res.v16[ 9]*m.v16[14] + res.v16[13]*m.v16[15];
    v16[14] = res.v16[2]*m.v16[12] + res.v16[6]*m.v16[13] + res.v16[10]*m.v16[14] + res.v16[14]*m.v16[15]; 
    v16[15] = res.v16[3]*m.v16[12] + res.v16[7]*m.v16[13] + res.v16[11]*m.v16[14] + res.v16[15]*m.v16[15];

  }
  inline void Mat4f::operator *= (const float s)
  {
    v16[0 ] *= s;
    v16[1 ] *= s;
    v16[2 ] *= s;
    v16[3 ] *= s;
    
    v16[4 ] *= s;
    v16[5 ] *= s;
    v16[6 ] *= s;
    v16[7 ] *= s;
    
    v16[8 ] *= s;
    v16[9 ] *= s;
    v16[10] *= s;
    v16[11] *= s;
    
    v16[12] *= s;
    v16[13] *= s;
    v16[14] *= s;
    v16[15] *= s;
  }
  
  inline void Mat4f::operator /= (const float s)
  {
    v16[0 ] /= s;
    v16[1 ] /= s;
    v16[2 ] /= s;
    v16[3 ] /= s;
    
    v16[4 ] /= s;
    v16[5 ] /= s;
    v16[6 ] /= s;
    v16[7 ] /= s;
    
    v16[8 ] /= s;
    v16[9 ] /= s;
    v16[10] /= s;
    v16[11] /= s;
    
    v16[12] /= s;
    v16[13] /= s;
    v16[14] /= s;
    v16[15] /= s;
  }

  /*-----------------------------------------------------------------------*/
  /*    operators == !=                                                    */
  /*-----------------------------------------------------------------------*/

  //operators ==
  inline bool Mat4f::operator == (const Mat4f &u) const
  {    
    float res[16];
    int i;

    for (i=0;i<16;i++)
      {
	if (v16[i]==u.v16[i])
	  res[i]=1.;
	else   
	  res[i]=0.;
      }

    
  if (res[ 0] * res[ 1] * res[ 2] * res[ 3] * 
      res[ 4] * res[ 5] * res[ 6] * res[ 7] * 
      res[ 8] * res[ 9] * res[10] * res[11] * 
      res[12] * res[13] * res[14] * res[15] == 0)
    {return 0;}
  else 
    {return 1;}
  } 
  
  
  //operator != 
  inline bool Mat4f::operator != (const Mat4f &u) const
  {    
    float res[16];
    int i;

    for (i=0;i<16;i++)
      {
	if (v16[i]!=u.v16[i])
	  res[i]=0.;
	else   
	  res[i]=1.;
      }

    
  if (res[ 0] * res[ 1] * res[ 2] * res[ 3] * 
      res[ 4] * res[ 5] * res[ 6] * res[ 7] * 
      res[ 8] * res[ 9] * res[10] * res[11] * 
      res[12] * res[13] * res[14] * res[15] == 0)
    {return 1;}
  else 
    {return 0;}
  } 
  
  /*-----------------------------------------------------------------------*/
  /*    functions abs inverse det rotate translate setM...                 */
  /*-----------------------------------------------------------------------*/
 
  inline void Mat4f::abs ()
  {
    Mat4f res(*this);
    int i;
    
    for (i=0;i<16;i++)
      {
	if (res.v16[i] < 0)
	  v16[i] = res.v16[i] * (-1);
      }
  }
  
  inline Mat4f Mat4f::inverse () const                          //116)
  {
    const Mat4f &m = *this;
    Mat4f res;
    Mat4f aux;
    
    float a = ( m(2,2) * m(3,3) - m(2,3) * m(3,2) );       
    float b = ( m(2,0) * m(3,1) - m(2,1) * m(3,0) );
    float c = ( m(3,2) * m(0,3) - m(0,2) * m(3,3) );
    float d = ( m(3,0) * m(0,1) - m(0,0) * m(3,1) );
    float e = ( m(0,2) * m(1,3) - m(0,3) * m(1,2) );
    float f = ( m(0,0) * m(1,1) - m(0,1) * m(1,0) );
    float g = ( m(1,2) * m(2,3) - m(1,3) * m(2,2) );
    float h = ( m(1,0) * m(2,1) - m(1,1) * m(2,0) );
    float i = ( m(1,2) * m(3,3) - m(1,3) * m(3,2) );          
    float j = ( m(1,0) * m(3,1) - m(1,1) * m(3,0) );           
    float k = ( m(0,2) * m(2,3) - m(0,3) * m(2,2) );           
    float l = ( m(0,0) * m(2,1) - m(0,1) * m(2,0) );          
    
    res.v16[ 0] = m.v16[5] * ( a) + m.v16[ 9] * (-i) + m.v16[13] * ( g);    
    res.v16[ 1] = m.v16[1] * (-a) + m.v16[ 9] * (-c) + m.v16[13] * (-k);    
    res.v16[ 2] = m.v16[1] * ( i) + m.v16[ 5] * ( c) + m.v16[13] * ( e);    
    res.v16[ 3] = m.v16[1] * (-g) + m.v16[ 5] * ( k) + m.v16[ 9] * (-e);
    
    res.v16[ 4] = m.v16[4] * (-a) + m.v16[ 8] * ( i) + m.v16[12] * (-g);    
    res.v16[ 5] = m.v16[0] * ( a) + m.v16[ 8] * ( c) + m.v16[12] * ( k);    
    res.v16[ 6] = m.v16[0] * (-i) + m.v16[ 4] * (-c) + m.v16[12] * (-e);    
    res.v16[ 7] = m.v16[0] * ( g) + m.v16[ 4] * (-k) + m.v16[ 8] * ( e);
    
    res.v16[ 8] = m.v16[7] * ( b) + m.v16[11] * (-j) + m.v16[15] * ( h);    
    res.v16[ 9] = m.v16[3] * (-b) + m.v16[11] * (-d) + m.v16[15] * (-l);    
    res.v16[10] = m.v16[3] * ( j) + m.v16[ 7] * ( d) + m.v16[15] * ( f);    
    res.v16[11] = m.v16[3] * (-h) + m.v16[ 7] * ( l) + m.v16[11] * (-f);     
    
    res.v16[12] = m.v16[6] * (-b) + m.v16[10] * ( j) + m.v16[14] * (-h);    
    res.v16[13] = m.v16[2] * ( b) + m.v16[10] * ( d) + m.v16[14] * ( l);    
    res.v16[14] = m.v16[2] * (-j) + m.v16[ 6] * (-d) + m.v16[14] * (-f);    
    res.v16[15] = m.v16[2] * ( h) + m.v16[ 6] * (-l) + m.v16[10] * ( f);          
    
    return res * (float(1.0)/(m. det_4x4()));
  }
  
  inline float Mat4f::det_3x3 () const
  {
    Mat4f res(*this);
    return res.v16[15] *  (   res.v16[0] * (res.v16[5] * res.v16[10] - res.v16[9] * res.v16[ 6]) + 
				   res.v16[4] * (res.v16[9] * res.v16[ 2] - res.v16[1] * res.v16[10]) + 
				   res.v16[8] * (res.v16[1] * res.v16[ 6] - res.v16[5] * res.v16[ 2])
				   );
  }
  
  inline Mat4f Mat4f::inverse_3x3 () const                          //116)
  {
    const Mat4f &m = *this;
    Mat4f res;
    Mat4f aux;
    
    float a = ( m(2,2) * m(3,3) );       
    float b = ( m(2,0) * m(3,1) - m(2,1) * m(3,0) );
    float c = ( - m(0,2) * m(3,3) );
    float d = ( m(3,0) * m(0,1) - m(0,0) * m(3,1) );
    float f = ( m(0,0) * m(1,1) - m(0,1) * m(1,0) );
    float h = ( m(1,0) * m(2,1) - m(1,1) * m(2,0) );
    float i = ( m(1,2) * m(3,3) );           
    float j = ( m(1,0) * m(3,1) - m(1,1) * m(3,0) );          
    float l = ( m(0,0) * m(2,1) - m(0,1) * m(2,0) );         
    
    res.v16[ 0] = m.v16[5] * ( a) + m.v16[ 9] * (-i) ;    
    res.v16[ 1] = m.v16[1] * (-a) + m.v16[ 9] * (-c) ;    
    res.v16[ 2] = m.v16[1] * ( i) + m.v16[ 5] * ( c) ;    
    res.v16[ 3] = 0;
    
    res.v16[ 4] = m.v16[4] * (-a) + m.v16[ 8] * ( i) ;    
    res.v16[ 5] = m.v16[0] * ( a) + m.v16[ 8] * ( c) ;    
    res.v16[ 6] = m.v16[0] * (-i) + m.v16[ 4] * (-c) ;    
    res.v16[ 7] = 0;
    
    res.v16[ 8] = m.v16[15] * ( h);    
    res.v16[ 9] = m.v16[15] * (-l);    
    res.v16[10] = m.v16[15] * ( f);    
    res.v16[11] = m.v16[3] * (-h) + m.v16[ 7] * ( l) + m.v16[11] * (-f);     

    res.v16[12] = m.v16[6] * (-b) + m.v16[10] * ( j) + m.v16[14] * (-h);    
    res.v16[13] = m.v16[2] * ( b) + m.v16[10] * ( d) + m.v16[14] * ( l);    
    res.v16[14] = m.v16[2] * (-j) + m.v16[ 6] * (-d) + m.v16[14] * (-f);    
    res.v16[15] = m.v16[2] * ( h) + m.v16[ 6] * (-l) + m.v16[10] * ( f);          
    
    return res * (float(1.0)/(m. det_3x3()));
  }
  
  
  inline float Mat4f::det_4x4 () const
  {
    Mat4f res(*this);
    
    float a = res.v16[10] * res.v16[15] - res.v16[14] * res.v16[11];
    float b = res.v16[6 ] * res.v16[15] - res.v16[14] * res.v16[7 ];
    float c = res.v16[6 ] * res.v16[11] - res.v16[10] * res.v16[7 ];
    float d = res.v16[2 ] * res.v16[15] - res.v16[14] * res.v16[3 ];
    float e = res.v16[2 ] * res.v16[11] - res.v16[10] * res.v16[3 ];
    float f = res.v16[2 ] * res.v16[7 ] - res.v16[6 ] * res.v16[3 ];
    
    return(   a * (res.v16[0 ] * res.v16[5 ] - res.v16[4 ] * res.v16[1 ])
	    + b * (res.v16[8 ] * res.v16[1 ] - res.v16[0 ] * res.v16[9 ])
	    + c * (res.v16[0 ] * res.v16[13] - res.v16[12] * res.v16[1 ])
	    + d * (res.v16[4 ] * res.v16[9 ] - res.v16[8 ] * res.v16[5 ])
	    + e * (res.v16[12] * res.v16[5 ] - res.v16[4 ] * res.v16[13])
	    + f * (res.v16[8 ] * res.v16[13] - res.v16[12] * res.v16[9 ])
	  );

  }

  
  inline Mat4f Mat4f::inverse_2 () const                  //(272)
  {
    const Mat4f &m = *this;
    Mat4f res;
    
    res(0,0) = m(1,2)*m(2,3)*m(3,1) - m(1,3)*m(2,2)*m(3,1) + m(1,3)*m(2,1)*m(3,2) - m(1,1)*m(2,3)*m(3,2) - m(1,2)*m(2,1)*m(3,3) + m(1,1)*m(2,2)*m(3,3);    
    res(0,1) = m(0,3)*m(2,2)*m(3,1) - m(0,2)*m(2,3)*m(3,1) - m(0,3)*m(2,1)*m(3,2) + m(0,1)*m(2,3)*m(3,2) + m(0,2)*m(2,1)*m(3,3) - m(0,1)*m(2,2)*m(3,3);    
    res(0,2) = m(0,2)*m(1,3)*m(3,1) - m(0,3)*m(1,2)*m(3,1) + m(0,3)*m(1,1)*m(3,2) - m(0,1)*m(1,3)*m(3,2) - m(0,2)*m(1,1)*m(3,3) + m(0,1)*m(1,2)*m(3,3);    
    res(0,3) = m(0,3)*m(1,2)*m(2,1) - m(0,2)*m(1,3)*m(2,1) - m(0,3)*m(1,1)*m(2,2) + m(0,1)*m(1,3)*m(2,2) + m(0,2)*m(1,1)*m(2,3) - m(0,1)*m(1,2)*m(2,3);    
    res(1,0) = m(1,3)*m(2,2)*m(3,0) - m(1,2)*m(2,3)*m(3,0) - m(1,3)*m(2,0)*m(3,2) + m(1,0)*m(2,3)*m(3,2) + m(1,2)*m(2,0)*m(3,3) - m(1,0)*m(2,2)*m(3,3);    
    res(1,1) = m(0,2)*m(2,3)*m(3,0) - m(0,3)*m(2,2)*m(3,0) + m(0,3)*m(2,0)*m(3,2) - m(0,0)*m(2,3)*m(3,2) - m(0,2)*m(2,0)*m(3,3) + m(0,0)*m(2,2)*m(3,3);    
    res(1,2) = m(0,3)*m(1,2)*m(3,0) - m(0,2)*m(1,3)*m(3,0) - m(0,3)*m(1,0)*m(3,2) + m(0,0)*m(1,3)*m(3,2) + m(0,2)*m(1,0)*m(3,3) - m(0,0)*m(1,2)*m(3,3);    
    res(1,3) = m(0,2)*m(1,3)*m(2,0) - m(0,3)*m(1,2)*m(2,0) + m(0,3)*m(1,0)*m(2,2) - m(0,0)*m(1,3)*m(2,2) - m(0,2)*m(1,0)*m(2,3) + m(0,0)*m(1,2)*m(2,3);    
    res(2,0) = m(1,1)*m(2,3)*m(3,0) - m(1,3)*m(2,1)*m(3,0) + m(1,3)*m(2,0)*m(3,1) - m(1,0)*m(2,3)*m(3,1) - m(1,1)*m(2,0)*m(3,3) + m(1,0)*m(2,1)*m(3,3);    
    res(2,1) = m(0,3)*m(2,1)*m(3,0) - m(0,1)*m(2,3)*m(3,0) - m(0,3)*m(2,0)*m(3,1) + m(0,0)*m(2,3)*m(3,1) + m(0,1)*m(2,0)*m(3,3) - m(0,0)*m(2,1)*m(3,3);    
    res(2,2) = m(0,1)*m(1,3)*m(3,0) - m(0,3)*m(1,1)*m(3,0) + m(0,3)*m(1,0)*m(3,1) - m(0,0)*m(1,3)*m(3,1) - m(0,1)*m(1,0)*m(3,3) + m(0,0)*m(1,1)*m(3,3);    
    res(2,3) = m(0,3)*m(1,1)*m(2,0) - m(0,1)*m(1,3)*m(2,0) - m(0,3)*m(1,0)*m(2,1) + m(0,0)*m(1,3)*m(2,1) + m(0,1)*m(1,0)*m(2,3) - m(0,0)*m(1,1)*m(2,3);    
    res(3,0) = m(1,2)*m(2,1)*m(3,0) - m(1,1)*m(2,2)*m(3,0) - m(1,2)*m(2,0)*m(3,1) + m(1,0)*m(2,2)*m(3,1) + m(1,1)*m(2,0)*m(3,2) - m(1,0)*m(2,1)*m(3,2);    
    res(3,1) = m(0,1)*m(2,2)*m(3,0) - m(0,2)*m(2,1)*m(3,0) + m(0,2)*m(2,0)*m(3,1) - m(0,0)*m(2,2)*m(3,1) - m(0,1)*m(2,0)*m(3,2) + m(0,0)*m(2,1)*m(3,2);    
    res(3,2) = m(0,2)*m(1,1)*m(3,0) - m(0,1)*m(1,2)*m(3,0) - m(0,2)*m(1,0)*m(3,1) + m(0,0)*m(1,2)*m(3,1) + m(0,1)*m(1,0)*m(3,2) - m(0,0)*m(1,1)*m(3,2);    
    res(3,3) = m(0,1)*m(1,2)*m(2,0) - m(0,2)*m(1,1)*m(2,0) + m(0,2)*m(1,0)*m(2,1) - m(0,0)*m(1,2)*m(2,1) - m(0,1)*m(1,0)*m(2,2) + m(0,0)*m(1,1)*m(2,2);    
    
    return res * (float(1.0)/(m.det_4x4()));
  }
  
//satt inn enere på diagonalen i rotasjonsmatrisene (andré har godkjent)
  inline void Mat4f::rotateX(float a)
  {
    Mat4f tmp;
    tmp.setIdentity();
    float cosa=cos(a);
    float sina=sin(a);
    tmp.v16[5]=cosa;
    tmp.v16[6]=sina;
    tmp.v16[9]=-sina;
    tmp.v16[10]=cosa;
    *this*=tmp;
  }
  
  inline void Mat4f::rotateY(float a)
  {
    Mat4f tmp;
    tmp.setIdentity();
    float cosa=cos(a);
    float sina=sin(a);
    tmp.v16[0]=cosa;
    tmp.v16[2]=-sina;
    tmp.v16[8]=sina;
    tmp.v16[10]=cosa;
    *this*=tmp;
  }
  
  inline void Mat4f::rotateZ(float a)
  {
    Mat4f tmp;
    tmp.setIdentity();
    float cosa=cos(a);
    float sina=sin(a);
    tmp.v16[0]=cosa;
    tmp.v16[1]=sina;
    tmp.v16[4]=-sina;
    tmp.v16[5]=cosa;
    *this*=tmp;
  }
  

  inline void Mat4f::translate(float x, float y, float z)
  {
    Mat4f tmp;
    tmp.setIdentity();
    tmp.v16[12]=x;
    tmp.v16[13]=y;
    tmp.v16[14]=z;
    *this*=tmp;
  }
  
  
  inline void Mat4f::translate(const Vec3f &v)
  {
    this->translate(v[0], v[1], v[2]);
  }
  
  inline void Mat4f::setIdentity () 
  {
    v16[0 ] = 1;
    v16[1 ] = 0;
    v16[2 ] = 0;
    v16[3 ] = 0;
    
    v16[4 ] = 0;
    v16[5 ] = 1;
    v16[6 ] = 0;
    v16[7 ] = 0;
    
    v16[8 ] = 0;
    v16[9 ] = 0;
    v16[10] = 1;
    v16[11] = 0;
    
    v16[12] = 0;
    v16[13] = 0;
    v16[14] = 0;
    v16[15] = 1;
  }
  
  inline void Mat4f::setFrustumMatrix(float leftV, float rightV, float bottomV, float topV, float nearV, float farV)
  {
    v16[0]  = (2.0f * nearV) / (rightV - leftV);
    v16[1]  = 0.0f;
    v16[2]  = 0.0f;
    v16[3]  = 0.0f;
     
    v16[4]  = 0.0f;
    v16[5]  = (2.0f * nearV) / (topV - bottomV);
    v16[6]  = 0.0f;
    v16[7]  = 0.0f;
    
    v16[8]  = (rightV + leftV) / (rightV - leftV);
    v16[9]  = (topV + bottomV) / (topV - bottomV);
    v16[10] = -(farV + nearV) / (farV - nearV);
    v16[11] = -1.0f;
    
    v16[12] = 0.0f;
    v16[13] = 0.0f;
    v16[14] = -(2.0f * farV * nearV) / (farV - nearV);
    v16[15] = 0.0f;
  }
  
  inline void Mat4f::setPerspectiveMatrix(float fovy, float aspect, float zNear, float zFar)
  {
    float xMin, xMax, yMin, yMax;
    
    yMax = zNear * float(tan(fovy * M_PI / 360.0f));
    yMin = -yMax;
    xMin = yMin * aspect;
    xMax = yMax * aspect;
    
    setFrustumMatrix(xMin, xMax, yMin, yMax, zNear, zFar);
  }
  
  inline Vec3f Mat4f::rotateVector(const Vec3f &v)
  {
    Vec3f vec;
    vec[0] = v16[0] * v[0] + v16[1] * v[1] + v16[ 2] * v[2];
    vec[1] = v16[4] * v[0] + v16[5] * v[1] + v16[ 6] * v[2];
    vec[2] = v16[8] * v[0] + v16[9] * v[1] + v16[10] * v[2];
    return vec;
  }
  
  /*-----------------------------------------------------------------------*/
  /*    functions c1 c2 c3 c4 r1 r2 r3 r4                                  */
  /*-----------------------------------------------------------------------*/
  
  inline const Vec4f Mat4f::c1(const Mat4f &m) const 
  {        Vec4f tmp(m.v16[0],m.v16[1],m.v16[2],m.v16[3]);
    return tmp;  }
  inline Vec4f Mat4f::c1(const Mat4f &m)  
  {        Vec4f tmp(m.v16[0],m.v16[1],m.v16[2],m.v16[3]);
    return tmp;  }
  
  inline const Vec4f Mat4f::c2(const Mat4f &m) const 
  {        Vec4f tmp(m.v16[4],m.v16[5],m.v16[6],m.v16[7]);
    return tmp;  }
  inline Vec4f Mat4f::c2(const Mat4f &m)  
  {        Vec4f tmp(m.v16[4],m.v16[5],m.v16[6],m.v16[7]);
    return tmp;  }
  
  inline const Vec4f Mat4f::c3(const Mat4f &m) const 
  {        Vec4f tmp(m.v16[8],m.v16[9],m.v16[10],m.v16[11]);
    return tmp;  }
  inline Vec4f Mat4f::c3(const Mat4f &m)  
  {        Vec4f tmp(m.v16[8],m.v16[9],m.v16[10],m.v16[11]);
    return tmp;  }
  
  inline const Vec4f Mat4f::c4(const Mat4f &m) const 
  {        Vec4f tmp(m.v16[12],m.v16[13],m.v16[14],m.v16[15]);
    return tmp;  }
  inline Vec4f Mat4f::c4(const Mat4f &m)  
  {        Vec4f tmp(m.v16[12],m.v16[13],m.v16[14],m.v16[15]);
    return tmp;  }
  
  inline const Vec4f Mat4f::r1(const Mat4f &m) const 
  {        Vec4f tmp(m.v16[0],m.v16[4],m.v16[8],m.v16[12]);
    return tmp;  }
  inline Vec4f Mat4f::r1(const Mat4f &m)  
  {        Vec4f tmp(m.v16[0],m.v16[4],m.v16[8],m.v16[12]);
    return tmp;  }
  
  inline const Vec4f Mat4f::r2(const Mat4f &m) const 
  {        Vec4f tmp(m.v16[1],m.v16[5],m.v16[9],m.v16[13]);
    return tmp;  }
  inline Vec4f Mat4f::r2(const Mat4f &m)  
  {        Vec4f tmp(m.v16[1],m.v16[5],m.v16[9],m.v16[13]);
    return tmp;  }
  
  inline const Vec4f Mat4f::r3(const Mat4f &m) const 
  {        Vec4f tmp(m.v16[2],m.v16[6],m.v16[10],m.v16[14]);
    return tmp;  }
  inline Vec4f Mat4f::r3(const Mat4f &m)  
  {        Vec4f tmp(m.v16[2],m.v16[6],m.v16[10],m.v16[14]);
    return tmp;  }
  
  inline const Vec4f Mat4f::r4(const Mat4f &m) const 
  {        Vec4f tmp(m.v16[3],m.v16[7],m.v16[11],m.v16[15]);
    return tmp;  }
  inline Vec4f Mat4f::r4(const Mat4f &m)  
  {        Vec4f tmp(m.v16[3],m.v16[7],m.v16[11],m.v16[15]);
    return tmp;  }
  /*-----------------------------------------------------------------------*/
  /*    read  writhe                                                       */
  /*-----------------------------------------------------------------------*/

  //by colum
  inline void Mat4f::read(std::istream& is)
  {
    is >> v16[0] >> v16[4] >> v16[8]  >> v16[12]
       >> v16[1] >> v16[5] >> v16[9]  >> v16[13]
       >> v16[2] >> v16[6] >> v16[10] >> v16[14]
       >> v16[3] >> v16[7] >> v16[11] >> v16[15];
  }
  
  inline void Mat4f::write(std::ostream& os) const
  {
    os <<"\n"
       <<v16[0]<<" "<<v16[4]<<" "<<v16[8] <<" "<<v16[12]<<"\n"
       <<v16[1]<<" "<<v16[5]<<" "<<v16[9] <<" "<<v16[13]<<"\n"
       <<v16[2]<<" "<<v16[6]<<" "<<v16[10]<<" "<<v16[14]<<"\n"
       <<v16[3]<<" "<<v16[7]<<" "<<v16[11]<<" "<<v16[15];
  }
  
  /*-----------------------------------------------------------------------*/
  /*    operators + - * /  with friend                                     */
  /*-----------------------------------------------------------------------*/
  
  inline Mat4f operator + (float s, const Mat4f &v)
  {   
    Mat4f res(s);
    res += v;
    return res;
  }
  
  inline Mat4f operator - (float s, const Mat4f &v)
  {   
    Mat4f res(s);
    res -= v;
    return res;
  }
  
  inline Mat4f operator * (float s, const Mat4f &v)
  {   
    Mat4f res;
    res = v*s;
    return res;
  }
  
  inline Vec4f operator * (const Vec4f &v, const Mat4f &m)
  {
    Vec4f res;
    Vec4f aux;

    res[0] = v[0]*m.v16[ 0] + v[1]*m.v16[ 1] + v[2]*m.v16[ 2] + v[3]*m.v16[ 3];  
    res[1] = v[0]*m.v16[ 4] + v[1]*m.v16[ 5] + v[2]*m.v16[ 6] + v[3]*m.v16[ 7]; 
    res[2] = v[0]*m.v16[ 8] + v[1]*m.v16[ 9] + v[2]*m.v16[10] + v[3]*m.v16[11]; 
    res[3] = v[0]*m.v16[12] + v[1]*m.v16[13] + v[2]*m.v16[14] + v[3]*m.v16[15]; 

    return res;
  }
  

  /*-----------------------------------------------------------------------*/
  /*    functions max min tr with friend                                   */
  /*-----------------------------------------------------------------------*/  
  
  //func max/min with friend
  inline Mat4f min_mat (const Mat4f &u , const Mat4f &v) 
  { 
    Mat4f res;  

    for (int i=0; i<16; i++)
      {
        if(u.v16[i]<v.v16[i])
	  res.v16[i]=u.v16[i];
	else
	  res.v16[i]=v.v16[i];
      }

    return res;
  }
  inline Mat4f max_mat (const Mat4f &u , const Mat4f &v) 
  {   
    Mat4f res;  

    for (int i=0; i<16; i++)
      {
        if(u.v16[i]>=v.v16[i])
	  res.v16[i]=u.v16[i];
	else
	  res.v16[i]=v.v16[i];
      }

    return res;
  }
  
  inline Mat4f transpose (const Mat4f &m)
  {
    Mat4f res(m.v16[0], m.v16[4], m.v16[8 ], m.v16[12],
              m.v16[1], m.v16[5], m.v16[9 ], m.v16[13],
              m.v16[2], m.v16[6], m.v16[10], m.v16[14],
              m.v16[3], m.v16[7], m.v16[11], m.v16[15]);
    return res;
  }

  inline float trace (const Mat4f &m) 
  {
    float res;
    res=m.v16[0] + m.v16[5] + m.v16[10] + m.v16[15];    

    return res;
  }


  inline std::istream& operator>>(std::istream& is, Mat4f& v)
  { 
    v.read(is); 
    return is; 
  }
  
  // Stream insertion for Vec4f.
  inline std::ostream& operator<<(std::ostream& os, const Mat4f& v)
  { 
    v.write(os); 
    return os; 
  }  


} //namespace siut

#endif // _SIUT_SIMD_STANDARD_MAT4F_HPP_
