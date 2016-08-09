#ifndef MGL_ATTRIBUTE_H_
#define MGL_ATTRIBUTE_H_

#include "mgl/includes.h"
#include "mgl/program.h"
#include "util/noncopyable.h"

#include <string>


namespace mgl {

class Attribute : private util::NonCopyable {
 public:
  Attribute(const Program& program, const std::string& name);
 protected:
  GLint idx_{0};
};

class VertexAttributeArray : public Attribute {
 public:
  using Attribute::Attribute;

  void Enable();
  void Disable();
  void Pointer(
      GLint size,
      GLenum type,
      GLboolean normalized = GL_FALSE,
      GLsizei stride = 0,
      const GLvoid* ptr = nullptr);

 private:
  bool is_enabled_{false};
};

}  // namespace mgl

#endif   // MGL_ATTRIBUTE_H_
