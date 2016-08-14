#ifndef HEX_HEXAGON_H_
#define HEX_HEXAGON_H_

#include "hex/drawable.h"

#include <array>

namespace hex {

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
};


}  // namespace hex

#endif  // HEX_HEXAGON_H_
