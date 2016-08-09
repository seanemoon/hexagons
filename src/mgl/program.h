#ifndef MGL_PROGRAM_H_
#define MGL_PROGRAM_H_

#include "mgl/includes.h"
#include "mgl/shader.h"
#include "util/noncopyable.h"

#include <string>

namespace mgl {

class Program : private util::NonCopyable {
 public:
  Program();
  ~Program();
  void AttachShader(const Shader& shader);
  bool Link();

  void Use();
  void StopUsing();
  bool IsInUse();

  GLuint Id() const { return id_; }
  std::string InfoLog() const;

 private:
  bool is_in_use_;
  GLuint id_;
};

}  // namespace mgl

#endif  // MGL_RROGRAM_H_
