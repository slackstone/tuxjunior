//  $Id: vector.hpp 4059 2006-07-21 11:45:14Z matzebraun $
//
//  SuperTux
//  Copyright (C) 2006 Matthias Braun <matze@braunis.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef SUPERTUX_VECTOR_H
#define SUPERTUX_VECTOR_H

/** Simple two dimensional vector. */
class Vector
{
public:
  Vector(float nx, float ny)
      : x(nx), y(ny)
  { }
  Vector(const Vector& other)
      : x(other.x), y(other.y)
  { }
  Vector()
      : x(0), y(0)
  { }

  bool operator ==(const Vector& other) const
    {
      return x == other.x && y == other.y;
    }

  bool operator !=(const Vector& other) const
    {
      return !(x == other.x && y == other.y);
    }

  const Vector& operator=(const Vector& other)
  {
    x = other.x;
    y = other.y;
    return *this;
  }

  Vector operator+(const Vector& other) const
    {
      return Vector(x + other.x, y + other.y);
    }

  Vector operator-(const Vector& other) const
    {
      return Vector(x - other.x, y - other.y);
    }

  Vector operator*(float s) const
    {
      return Vector(x * s, y * s);
    }

  Vector operator/(float s) const
    {
      return Vector(x / s, y / s);
    }

  Vector operator-() const
    {
      return Vector(-x, -y);
    }

  const Vector& operator +=(const Vector& other)
  {
    x += other.x;
    y += other.y;
    return *this;
  }

  const Vector& operator -=(const Vector& other)
  {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  const Vector& operator *=(float val)
  {
    x *= val;
    y *= val;
    return *this;
  }

  const Vector& operator /=(float val)
  {
    x /= val;
    y /= val;
    return *this;
  }

  /// Scalar product of 2 vectors
  float operator*(const Vector& other) const
    {
      return x*other.x + y*other.y;
    }

  float norm() const;
  Vector unit() const;

  // ... add the other operators as needed, I'm too lazy now ...

  float x, y; // leave this public, get/set methods just give me headaches
  // for such simple stuff :)
};

#endif
