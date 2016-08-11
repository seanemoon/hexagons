#include "geo/drawable.h"

namespace geo {

void Drawable::Draw(mgl::VertexAttribute* position_attr,
                    mgl::VertexAttribute* color_attr) {

  position_vbo_.Bind();
  position_attr->Pointer(position_vbo_);
  position_vbo_.Unbind();

  color_vbo_.Bind();
  color_attr->Pointer(color_vbo_);
  color_vbo_.Unbind();

  ibo_.Bind();
  MGL_CALL(glDrawElements(
        GL_TRIANGLES, ibo_.Size(), ibo_.Type(), nullptr));
  ibo_.Unbind();
}

}  // namespace geo
