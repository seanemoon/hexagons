#ifndef MGL_SHADER_H_
#define MGL_SHADER_H_

#include "mgl/includes.h"
#include "util/noncopyable.h"

#include <string>

namespace mgl {

class Shader : private util::NonCopyable {
 public:
  Shader(GLenum shader_type);
  ~Shader();
  void Source(const GLchar* src);
  bool Compile();

  GLuint Id() const { return id_; }
  std::string InfoLog() const;

 private:
  GLenum shader_type_;
  GLuint id_;
};

}  // namespace mgl

#endif  // MGL_SHADER_H_
