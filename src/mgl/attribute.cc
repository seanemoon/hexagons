#include "mgl/attribute.h"

#include "mgl/call.h"

#include <iostream>


namespace mgl {

Attribute::Attribute(const Program& program, const std::string& name)
  : idx_{-1} {
  idx_ = MGL_CALL(glGetAttribLocation(program.Id(), name.c_str()));
  if (idx_ == -1) {
    std::cout << "Invalid program attribute name: " << name << std::endl;
  }
}

void VertexAttributeArray::Enable() {
  MGL_CALL(glEnableVertexAttribArray(idx_));
  is_enabled_ = true;
}

void VertexAttributeArray::Disable() {
  MGL_CALL(glDisableVertexAttribArray(idx_));
  is_enabled_ = false;
}

void VertexAttributeArray::Pointer(
    GLint size,
    GLenum type,
    GLboolean normalized,
    GLsizei stride,
    const GLvoid* ptr) {
  MGL_CALL(glVertexAttribPointer(idx_, size, type, normalized, stride, ptr));
}




}  // namespace mgl
