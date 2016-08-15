#ifndef HEX_HEXAGON_H_
#define HEX_HEXAGON_H_

#include "hex/coords.h"
#include "mgl/buffer.h"
#include "mgl/vertex_attribute.h"

#include <array>

namespace hex {


// Responsible for hexagons which are rendered to the screen.
class Hexagon : private util::NonCopyable {
 public:
  // Construct a new hexagon.
  // `coord` a screen coordinate.
  // `size` is the maximal radius (R).
  Hexagon(PixelCoord coord, float size);

  // Set the screen coordinate of the hexagon.
  void SetPixelCoord(PixelCoord coord);

  // Set the color of the hexagon.
  void SetColor(uint8_t r, uint8_t g, uint8_t b);

  // Set the size of the hexagon.
  // `size` is the new maximal radius (R).
  void SetSize(float size);

  // Make OpenGL calls to draw this hexagon to the screen.
  // This will call the UpdateOpenGL* functions before attempting to draw if
  // their associateed buffer is dirty.
  void Render(mgl::VertexAttribute* position, mgl::VertexAttribute* color);

 private:
  // Update the position VBO.
  // This is automatically called by Render if the position VBO is dirty.
  void UpdateOpenGLPositions();

  // Update the color VBO.
  // This is automatically called by Draw if the color VBO is dirty.
  void UpdateOpenGLColors();

  // Update the IBO.
  // This is automatically called by Draw if the IBO is dirty.
  void UpdateOpenGLIndices();

  // Screen coordinate.
  PixelCoord coord_;

  // Equivalent to the maximal radius (R).
  float size_;

  // Red color value in the range [0, 255]
  uint8_t r_;

  // Green color value in the range [0, 255]
  uint8_t g_;

  // Green color value in the range [0, 255]
  uint8_t b_;

  // Position VBO and flag indicating whether it is dirty.
  bool position_is_dirty_;
  mgl::ArrayBuffer<float> position_vbo_;

  // Color VBO and flag indicating whether it is dirty.
  bool color_is_dirty_;
  mgl::ArrayBuffer<uint8_t> color_vbo_;

  // IBO and flag indicating whether it is dirty.
  bool index_is_dirty_;
  mgl::ElementArrayBuffer<uint> ibo_;
};


}  // namespace hex

#endif  // HEX_HEXAGON_H_
