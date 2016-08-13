#ifndef GEO_DRAWABLE_H_
#define GEO_DRAWABLE_H_

#include "mgl/mgl.h"

#include "util/noncopyable.h"

namespace geo {

class Drawable : private util::NonCopyable {
 public:
  Drawable() = default;
  Drawable(Drawable&& other) = default;
  void Draw(mgl::VertexAttribute* position_attr,
            mgl::VertexAttribute* color_attr) ;

 protected:
  mgl::ArrayBuffer<float> position_vbo_;
  mgl::ArrayBuffer<uint8_t> color_vbo_;
  mgl::ElementArrayBuffer<uint> ibo_;
};

}  // namespace geo

#endif  // GEO_DRAWABLE_H_
