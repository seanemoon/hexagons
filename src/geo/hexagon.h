#ifndef GEO_HEXAGON_H_
#define GEO_HEXAGON_H_

#include "geo/drawable.h"

#include <array>

namespace geo {

class Hexagon : public Drawable {
 public:
  static constexpr const double kHeight = 2.0;
  static constexpr const double kWidth = 1.73205080757;
  static constexpr const double kVerticalSpacing = kHeight * 0.75;
  static constexpr const double kHorizontalSpacing = kWidth;

  Hexagon(
      float x, float y,
      uint8_t r, uint8_t g, uint8_t b,
      float size = 1.0f);

  Hexagon(Hexagon&& move) = default;

 private:
  static const uint kNumVertices = 7;

  //            _0_          ---      ---
  //         _-  |  -_        |        |
  //      _-     |     -_     |        |
  //    5        |        1   | size   |
  //    | -_     |     _- |   |        |
  //    |    -_  |  _-    |   |        |
  //    |       -6-       |  ---       | height
  //    |    _-  |  -_    |            |
  //    | _-     |     -_ |            |
  //    4        |        2            |
  //      -_     |     _-              |
  //         -_  |  _-                 |
  //            -3-                   ---
  //
  //    |-----------------|
  //           width
  //
};


}  // namespace geo

#endif  // GEO_HEXAGON_H_
