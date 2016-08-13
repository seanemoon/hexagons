#ifndef MGL_BUFFER_H_
#define MGL_BUFFER_H_

#include "mgl/includes.h"
#include "mgl/call.h"
#include "util/noncopyable.h"

#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

namespace mgl {

template<typename T, GLenum BUFFER_TYPE>
class Buffer : private util::NonCopyable {
 public:
  Buffer()
    : id_{0},
      is_bound_{false},
      size_{0},
      width_{0} {
    MGL_CALL(glGenBuffers(1, &id_));
  }

  Buffer(Buffer&& move) = default;

  void Bind() {
    if (is_bound_) {
      std::cout << "Trying to bind already bound buffer: "
                << id_ << std::endl;
    }
    MGL_CALL(glBindBuffer(BUFFER_TYPE, id_));
    is_bound_ = true;
  }

  void Unbind() {
    if (!is_bound_) {
      std::cout << "Trying to unbind currently unbound buffer: "
                << id_ << std::endl;
      return;
    }
    MGL_CALL(glBindBuffer(BUFFER_TYPE, 0));
    is_bound_ = false;
  }

  void Data(
      const T* data,
      size_t sz,
      size_t width,
      GLenum usage = GL_STATIC_DRAW) {
    MGL_CALL(glBufferData(BUFFER_TYPE, sizeof(T) * sz, data, usage));
    size_ = sz;
    width_ = width;
  }

  void Data(
      const std::vector<T>& data,
      size_t width,
      GLenum usage = GL_STATIC_DRAW) {
    if (!is_bound_) {
      std::cout << "Trying to set data of unbound buffer: " << id_ << std::endl;
      return;
    }
    Data(data.data(), data.size(), width, usage);
  }

  template<size_t N>
  void Data(
      const std::array<T, N>& data,
      size_t width,
      GLenum usage = GL_STATIC_DRAW) {
    if (!is_bound_) {
      std::cout << "Trying to set data of unbound buffer: "
                 << static_cast<uint>(id_) << std::endl;
    }
    Data(data.data(), N, width, usage);
  }

  size_t Size() const { return size_; }

  size_t Width() const { return width_; }

  GLenum Type() const {
    if (std::is_same<T, float>::value) {
      return GL_FLOAT;
    } else if (std::is_same<T, uint8_t>::value) {
      return GL_UNSIGNED_BYTE;
    } else if (std::is_same<T, uint>::value) {
      return GL_UNSIGNED_INT;
    } else {
      // TODO(seanemoon): Get human readable string of typename.
      std::cout << "Type is currently not supported." << std::endl;
      return GL_FALSE;
    }
  }

 private:
  GLuint id_;
  bool is_bound_;
  size_t size_;
  size_t width_;
};

template <typename T>
class ArrayBuffer : public Buffer<T, GL_ARRAY_BUFFER> {};

template <typename T>
class ElementArrayBuffer : public Buffer<T, GL_ELEMENT_ARRAY_BUFFER> {};

}  // namespace mgl

#endif  // MGL_RROGRAM_H_
