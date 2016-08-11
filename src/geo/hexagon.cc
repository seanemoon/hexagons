#include "geo/hexagon.h"

namespace geo {

Hexagon::Hexagon(
    float x, float y,
    uint8_t r, uint8_t g, uint8_t b,
    float scale) {

  position_vbo_.Bind();
  {
    float a = 0.0f * scale;
    float b = 0.5f * scale;
    float c = 0.86602540378 * scale;  // sqrt(3)/2
    float d = 1.0f * scale;
    position_vbo_.Data({
      x+a, y+d,
      x+c, y+b,
      x+c, y-b,
      x+a, y-d,
      x-c, y-b,
      x-c, y+b
    }, 2);
    position_vbo_.Unbind();
  }

  color_vbo_.Bind();
  color_vbo_.Data({
    r, g, b,
    r, g, b,
    r, g, b,
    r, g, b,
    r, g, b,
    r, g, b
  }, 3);
  color_vbo_.Unbind();

  ibo_.Bind();
  ibo_.Data({
    5, 0, 1,
    5, 1, 4,
    4, 1, 2,
    4, 3, 2,
  }, 1);
  ibo_.Unbind();
}


}  // namespace geo
