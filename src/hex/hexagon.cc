#include "hex/hexagon.h"

namespace hex {

Hexagon::Hexagon(
    float x, float y,
    uint8_t r, uint8_t g, uint8_t b,
    float size) {

  position_vbo_.Bind();
  {
    float h = kHeight/2 * size;
    float w = kWidth/2 * size;
    position_vbo_.Data({
      x, y+h,
      x+w, y+h/2,
      x+w, y-h/2,
      x, y-h,
      x-w, y-h/2,
      x-w, y+h/2
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


}  // namespace hex
