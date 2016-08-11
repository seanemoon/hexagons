#ifndef GEO_HEXAGON_H_
#define GEO_HEXAGON_H_

#include "geo/drawable.h"

#include <array>

namespace geo {

class Hexagon : public Drawable {
 public:
  Hexagon(
      float x, float y,
      uint8_t r, uint8_t g, uint8_t b,
      float scale = 1.0f);

 private:
  static const uint kNumVertices = 7;

  // These arrays hold vertex attributes for the hexagon.
  // The diagram below shows which index corresponds to which index.
  //            _0_
  //         _-  |  -_
  //      _-     |     -_
  //    5        |        1
  //    | -_     |     _- |
  //    |    -_  |  _-    |
  //    |       -6-       |
  //    |    _-  |  -_    |
  //    | _-     |     -_ |
  //    4        |        2
  //      -_     |     _-
  //         -_  |  _-
  //            -3-
  std::array<float, kNumVertices> positions_;
  std::array<uint8_t, kNumVertices> colors_;
};


}  // namespace geo

#endif  // GEO_HEXAGON_H_
