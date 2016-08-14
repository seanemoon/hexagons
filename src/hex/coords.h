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

namespace hex {

template<typename T>
class OffsetCoord;
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

  template<typename S>
  OffsetCoord& operator*=(S s) { r*=s; c*=s; }

  template<typename S>
  OffsetCoord operator*(S s) { return OffsetCoord(r*s, c*s); }

  T r;
  T c;
};

template<typename T>
class CubeCoord {
 public:
  CubeCoord(T x, T y, T z) : x{x}, y{y}, z{z} {}
  CubeCoord(OffsetCoord<T> o) : x{o.c}, y{o.r-(o.c+(o.c&1))/2}, z{-x-y} {}
  CubeCoord(AxialCoord<T> o) : x{o.x}, y{o.y}, z{-x-y} {}

  template<typename S>
  CubeCoord& operator*=(S s) { x*=s; y*=s; z*=s; }

  template<typename S>
  CubeCoord operator*(S s) { return CubeCoord(x*s, y*s, z*s); }

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

  template<typename S>
  AxialCoord& operator*=(S s) { x*=s; y*=s; }

  template<typename S>
  AxialCoord operator*(S s) { return AxialCoord(x*s, y*s); }

  T x;
  T y;
};

class PixelCoord {
 public:
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

#endif  // HEX_COORDS_H_
