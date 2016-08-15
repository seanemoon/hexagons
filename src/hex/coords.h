// This file provides a few simple data wrappers for hexagonal grid coordinates
// as well as methods to convert between them. This are slightly modified
// versions of the coordinate systems described by Amit Patel from Red Blob
// Games in his article on Hexagonal Grids which can be found at the link
// below:
//
//   http://www.redblobgames.com/grids/hexagons/
//
// One main difference is that the y and z axes for the axial and cube
// coordinates have been swapped. I believe this is more consistent with the
// SDL window coordinate system.
#ifndef HEX_COORDS_H_
#define HEX_COORDS_H_

#include "hex/constants.h"

#include <functional>

namespace hex {

// Forward declarations.
template <typename T>
class CubeCoord;
template<typename T>
class AxialCoord;

template<typename T>
class OffsetCoord {
 public:
  OffsetCoord(T r, T c) : r{r}, c{c} {}
  OffsetCoord(CubeCoord<T> o) : c{o.x}, r{o.y+(o.x+(o.x&1))/2} {}
  OffsetCoord(AxialCoord<T> o) : c{o.x}, r{o.y+(o.x+(o.x&1))/2} {}

  bool operator==(const OffsetCoord other) const {
    return other.r == r && other.c == c;
  }

  T r;
  T c;
};

template<typename T>
class CubeCoord {
 public:
  CubeCoord(T x, T y, T z) : x{x}, y{y}, z{z} {}
  CubeCoord(OffsetCoord<T> o) : x{o.c}, y{o.r-(o.c+(o.c&1))/2}, z{-x-y} {}
  CubeCoord(AxialCoord<T> o) : x{o.x}, y{o.y}, z{-x-y} {}

  bool operator==(const CubeCoord other) const {
    return other.x == x && other.y == y && other.z == z;
  }

  T x;
  T y;
  T z;
};

template<typename T>
class AxialCoord {
 public:
  AxialCoord(T x, T y) : x{x}, y{y} {}
  AxialCoord(OffsetCoord<T> o) : x{o.c}, y{o.r-(o.c+(o.c&1))/2} {}
  AxialCoord(CubeCoord<T> o) : x{o.x}, y{o.y} {}

  AxialCoord& operator+=(AxialCoord o) { x+=o.x; y+=o.y; return *this; }
  AxialCoord operator+(AxialCoord o) {
    return {x+o.x, y+o.y};
  }

  bool operator==(const AxialCoord other) const {
    return other.x == x && other.y == y;
  }

  T x;
  T y;
};

class PixelCoord {
 public:
  PixelCoord(double x, double y) : x{x}, y{y} {}

  template<typename T>
  PixelCoord(CubeCoord<T> o)
    : x{kMinimalDiameter*(o.x+0.5*o.y)},
      y{kVerticalSpacing*o.y} {}

  template<typename T>
  PixelCoord(AxialCoord<T> o)
    : x{kMinimalDiameter*(o.x+0.5*o.y)},
      y{kVerticalSpacing*o.y} {}

  template<typename T>
  PixelCoord(OffsetCoord<T> o)
    : x{kMinimalDiameter*(o.c - 0.5*(o.r&1))},
      y{kVerticalSpacing*o.r} {}

  template<typename S>
  PixelCoord& operator*=(S s) { x*=s; y*=s; }

  template<typename S>
  PixelCoord operator*(S s) { return PixelCoord(x*s, y*s); }

  double x;
  double y;
};

}  // namespace hex


namespace std {

// Hash functions for the integral coordinates.
template<typename T>
struct hash<hex::AxialCoord<T>> {
  size_t operator()(const hex::AxialCoord<T>& c) const {
    size_t h = 17;
    auto fn = std::hash<T>();
    h = (h * 31) + fn(c.x);
    h = (h * 31) + fn(c.y);
    return h;
  }
};

template<typename T>
struct hash<hex::CubeCoord<T>> {
  size_t operator()(const hex::CubeCoord<T>& c) const {
    size_t h = 17;
    auto fn = std::hash<T>();
    h = (h * 31) + fn(c.x);
    h = (h * 31) + fn(c.y);
    return h;
  }
};

template<typename T>
struct hash<hex::OffsetCoord<T>> {
  size_t operator()(const hex::CubeCoord<T>& c) const {
    size_t h = 17;
    auto fn = std::hash<T>();
    h = (h * 31) + fn(c.r);
    h = (h * 31) + fn(c.c);
    return h;
  }
};

}  // namespace std

#endif  // HEX_COORDS_H_
