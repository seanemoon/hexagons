#ifndef MGL_VERTEX_ATTRIBUTE_H_
#define MGL_VERTEX_ATTRIBUTE_H_

#include "mgl/includes.h"
#include "mgl/program.h"
#include "mgl/buffer.h"
#include "mgl/call.h"
#include "util/noncopyable.h"

#include <string>
#include <vector>
#include <iostream>

namespace mgl {

class VertexAttribute : private util::NonCopyable {
 public:
  VertexAttribute(const Program& program, const std::string& name)
    : location_{-1} {
    location_= MGL_CALL(glGetAttribLocation(program.Id(), name.c_str()));
    if (location_ == -1) {
      std::cout << "Invalid program attribute name: " << name << std::endl;
    }
  }

  void Enable() { MGL_CALL(glEnableVertexAttribArray(location_)); }

  void Disable() { MGL_CALL(glDisableVertexAttribArray(location_)); }

  void Pointer(
      GLint size,
      GLenum type,
      GLboolean normalized = GL_FALSE,
      GLsizei stride = 0,
      const GLvoid* ptr = nullptr) {
    MGL_CALL(glVertexAttribPointer(
          location_, size, type, normalized, stride, ptr));
  }

  template <typename T>
  void Pointer(
      const ArrayBuffer<T>& vbo,
      GLboolean normalized = GL_FALSE,
      GLsizei stride = 0,
      const GLvoid* ptr = nullptr) {
    Pointer(vbo.Width(), vbo.Type(), normalized, stride, ptr);
  }

 private:
  GLint location_{0};
};

};


#endif  // MGL_VERTEX_ATTRIBUTE_H_
