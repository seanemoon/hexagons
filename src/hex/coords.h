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

  T r;
  T c;
};

template<typename T>
class CubeCoord {
 public:
  CubeCoord(T x, T y, T z) : x{x}, y{y}, z{z} {}
  CubeCoord(OffsetCoord<T> o) : x{o.c}, y{o.r-(o.c+(o.c&1))/2}, z{-x-y} {}
  CubeCoord(AxialCoord<T> o) : x{o.x}, y{o.y}, z{-x-y} {}

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

  double x;
  double y;
};

}  // namespace hex

#endif  // HEX_COORDS_H_
