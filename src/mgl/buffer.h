#ifndef MGL_BUFFER_H_
#define MGL_BUFFER_H_

#include "mgl/includes.h"
#include "mgl/call.h"
#include "util/noncopyable.h"

#include <string>
#include <vector>
#include <iostream>

namespace mgl {

template<typename T>
class Buffer : private util::NonCopyable {
 public:
  Buffer(GLenum buffer_type)
    : buffer_type_{buffer_type},
      id_{0},
      is_bound_{false} {
    MGL_CALL(glGenBuffers(1, &id_));
  }

  void Bind() {
    if (is_bound_) {
      std::cout << "Trying to bind already bound buffer: "
                << id_ << std::endl;
    }
    MGL_CALL(glBindBuffer(buffer_type_, id_));
    is_bound_ = true;
  }

  void Unbind() {
    if (!is_bound_) {
      std::cout << "Trying to unbind currently unbound buffer: "
                << id_ << std::endl;
      return;
    }
    MGL_CALL(glBindBuffer(buffer_type_, 0));
    is_bound_ = false;
  }

  void Data(const std::vector<T>& data, GLenum usage = GL_STATIC_DRAW) {
    if (!is_bound_) {
      std::cout << "Trying to set data of unbound buffer: " << id_ << std::endl;
      return;
    }
    MGL_CALL(glBufferData(
        buffer_type_, data.size() * sizeof(T), data.data(), usage));
  }

 private:
  GLenum buffer_type_;
  GLuint id_;
  bool is_bound_;
};

}  // namespace mgl

#endif  // MGL_RROGRAM_H_
