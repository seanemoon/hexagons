#include "hex/hexagon.h"
#include "hex/constants.h"

namespace hex {


Hexagon::Hexagon(PixelCoord coord, float size)
  : coord_{coord},
    size_{size},
    r_{0x00},
    g_{0x00},
    b_{0x00},
    position_is_dirty_{true},
    position_vbo_{},
    color_is_dirty_{true},
    color_vbo_{},
    index_is_dirty_{true},
    ibo_{} {
}

void Hexagon::SetPixelCoord(PixelCoord coord) {
  coord_ = coord;
  position_is_dirty_ = true;
}

void Hexagon::SetColor(uint8_t r, uint8_t g, uint8_t b) {
  r_ = r; g_ = g; b_ = b;
  color_is_dirty_ = true;
}

void Hexagon::SetSize(float size) {
  size_ = size;
  position_is_dirty_ = true;
}

void Hexagon::UpdateOpenGLColors() {
  color_vbo_.Bind();
  color_vbo_.Data({
    r_, g_, b_,
    r_, g_, b_,
    r_, g_, b_,
    r_, g_, b_,
    r_, g_, b_,
    r_, g_, b_
  }, 3);
  color_vbo_.Unbind();
  color_is_dirty_ = false;
}

void Hexagon::UpdateOpenGLPositions() {
  position_vbo_.Bind();
  float R = kMaximalRadius * size_;
  float r = kMinimalRadius * size_;
  float t = kSideLength * size_;
  float x = coord_.x;
  float y = coord_.y;
  position_vbo_.Data({
    x, y+R,
    x+r, y+t/2,
    x+r, y-t/2,
    x, y-R,
    x-r, y-t/2,
    x-r, y+t/2
  }, 2);
  position_vbo_.Unbind();
  position_is_dirty_ = false;
}

void Hexagon::UpdateOpenGLIndices() {
  ibo_.Bind();
  ibo_.Data({
    5, 0, 1,
    5, 1, 4,
    4, 1, 2,
    4, 3, 2,
  }, 1);
  ibo_.Unbind();
  index_is_dirty_ = false;
}

void Hexagon::Render(
    mgl::VertexAttribute* position, mgl::VertexAttribute* color) {
  if (position_is_dirty_) UpdateOpenGLPositions();
  if (color_is_dirty_) UpdateOpenGLColors();
  if (index_is_dirty_) UpdateOpenGLIndices();

  position_vbo_.Bind();
  position->Pointer(position_vbo_);
  position_vbo_.Unbind();

  color_vbo_.Bind();
  color->Pointer(color_vbo_, GL_TRUE);
  color_vbo_.Unbind();

  ibo_.Bind();
  MGL_CALL(glDrawElements(GL_TRIANGLES, ibo_.Size(), ibo_.Type(), nullptr));
  ibo_.Unbind();
}


}  // namespace hex
