/**********************************************************************
 * 
 *  File: 
 * 
 *  Created:
 *
 *  $Rev: 802 $ 
 *  $Id: Tuple.hpp 802 2008-07-31 06:46:39Z jami $
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

#ifndef _SIUT_SIMD_STANDARD_TUPLE_HPP_
#define _SIUT_SIMD_STANDARD_TUPLE_HPP_

#include <iostream>

namespace siut
{

template <class T, int N>
class Tuple 
{
  
public:
  Tuple();
  Tuple(const Tuple<T, N> &t);
  Tuple(const T *t);

  T& operator [] (int i);
  const T& operator [] (int i) const;

  inline Tuple<T, N> operator + (const Tuple<T, N> &t) const;
  inline Tuple<T, N> operator + (const float s) const;
  inline Tuple<T, N> operator - (const Tuple<T, N> &t) const;
  inline Tuple<T, N> operator - (const float s) const;
  inline Tuple<T, N> operator * (const Tuple<T, N> &t) const;
  inline Tuple<T, N> operator * (const float s) const;
  inline Tuple<T, N> operator / (const Tuple<T, N> &t) const;
  inline Tuple<T, N> operator / (const float s) const;

  inline Tuple<T, N>& operator += (const Tuple<T, N> &t);
  inline Tuple<T, N>& operator += (const float s);
  inline Tuple<T, N>& operator -= (const Tuple<T, N> &t);
  inline Tuple<T, N>& operator -= (const float s);
  inline Tuple<T, N>& operator *= (const Tuple<T, N> &t);
  inline Tuple<T, N>& operator *= (const float s);
  inline Tuple<T, N>& operator /= (const Tuple<T, N> &t);
  inline Tuple<T, N>& operator /= (const float s);

  friend inline Tuple<T, N> operator + (float s, const Tuple<T, N> &t); 
  friend inline Tuple<T, N> operator - (float s, const Tuple<T, N> &t); 
  friend inline Tuple<T, N> operator * (float s, const Tuple<T, N> &t); 
  friend inline Tuple<T, N> operator / (float s, const Tuple<T, N> &t); 

  void read(std::istream& is);
  void write(std::ostream& os) const;

private:

  T elem_[N];
};

// constructors
template <class T, int N>
inline
Tuple<T, N>::Tuple()
{
  for(int i=0; i<N; i++) elem_[i] = T();
}

template <class T, int N>
inline
Tuple<T, N>::Tuple(const Tuple<T, N> &t)
{
  for(int i=0; i<N; i++) elem_[i] = t.elem_[i];
}

template <class T, int N>
inline
Tuple<T, N>::Tuple(const T *t)
{
  for(int i=0; i<N; i++) elem_[i] = t[i];
}


template <class T, int N>
inline
T& Tuple<T, N>::operator [] (int i)
{
	return elem_[i];
}

template <class T, int N>
inline
const T& Tuple<T, N>::operator [] (int i) const
{
	return elem_[i];
}

template <class T, int N>
inline
Tuple<T, N> Tuple<T, N>::operator + (const Tuple<T, N> &t) const
{     
  Tuple<T, N> res(*this);
  res += t;
  return res;
}

template <class T, int N>
inline
Tuple<T, N> Tuple<T, N>::operator + (const float s) const
{   
  Tuple<T, N> res(*this);
  res += s;
  return res;
}

template <class T, int N>
inline
Tuple<T, N> Tuple<T, N>::operator - (const Tuple<T, N> &t) const
{   
  Tuple<T, N> res(*this);
  res -= t;
  return res;
}

template <class T, int N>
inline
Tuple<T, N> Tuple<T, N>::operator - (const float s) const
{   
  Tuple<T, N> res(*this);
  res -= s;
  return res;
}

template <class T, int N>
inline
Tuple<T, N> Tuple<T, N>::operator * (const Tuple<T, N> &t) const
{   
  Tuple<T, N> res(*this);
  res *= t;
  return res;
}

template <class T, int N>
inline
Tuple<T, N> Tuple<T, N>::operator * (const float s) const
{   
  Tuple<T, N> res(*this);
  res *= s;
  return res;
}

template <class T, int N>
inline
Tuple<T, N> Tuple<T, N>::operator / (const Tuple<T, N> &t) const
{   
  Tuple<T, N> res(*this);
  res /= t;
  return res;
}

template <class T, int N>
inline
Tuple<T, N> Tuple<T, N>::operator / (const float s) const
{   
  Tuple<T, N> res(*this);
  res /= s;
  return res;
}

template <class T, int N>
inline
Tuple<T, N>& Tuple<T, N>::operator += (const Tuple<T, N> &t)
{
  for (int i=0; i<N; i++)
  {
    elem_[i] += t.elem_[i];
  }
  return *this;
}
  
template <class T, int N>
inline
Tuple<T, N>& Tuple<T, N>::operator += (const float s)
{
  for (int i=0; i<N; i++)
  {
    elem_[i] += s;
  }
  return *this;
}

template <class T, int N>
inline
Tuple<T, N>& Tuple<T, N>::operator -= (const Tuple<T, N> &t)
{
  for (int i=0; i<N; i++)
  {
    elem_[i] -= t.elem_[i];
  }
  return *this;
}

template <class T, int N>
inline
Tuple<T, N>& Tuple<T, N>::operator -= (const float s)
{
  for (int i=0; i<N; i++)
  {
    elem_[i] -= s;
  }
  return *this;
}

template <class T, int N>
inline
Tuple<T, N>& Tuple<T, N>::operator *= (const Tuple<T, N> &t)
{
  for (int i=0; i<N; i++)
  {
    elem_[i] *= t.elem_[i];
  }
  return *this;
}

template <class T, int N>
inline
Tuple<T, N>& Tuple<T, N>::operator *= (const float s)
{
  for (int i=0; i<N; i++)
  {
    elem_[i] *= s;
  }
  return *this;
}

template <class T, int N>
inline
Tuple<T, N>& Tuple<T, N>::operator /= (const Tuple<T, N> &t)
{
  for (int i=0; i<N; i++)
  {
    elem_[i] /= t.elem_[i];
  }
  return *this;
}

template <class T, int N>
inline
Tuple<T, N>& Tuple<T, N>::operator /= (const float s)
{
  for (int i=0; i<N; i++)
  {
    elem_[i] /= s;
  }
  return *this;
}

template <class T, int N>
void Tuple<T, N>::read(std::istream& is)
{
  for(int i=0; i<N; i++)
  {
    is >> elem_[i];
  }
}

template <class T, int N>
void Tuple<T, N>::write(std::ostream& os) const
{
  for(int i=0; i<N; i++)
  {
    os << elem_[i] << " ";
  }
}


// global operators
template <class T, int N>
std::istream& operator>>(std::istream& is, Tuple<T, N>& t)
{ 
  t.read(is); 
  return is; 
}

template <class T, int N>
std::ostream& operator<<(std::ostream& os, const Tuple<T, N>& t)
{ 
  t.write(os); 
  return os; 
}

} // end namespace siut

#endif // _SIUT_SIMD_STANDARD_TUPLE_HPP_

