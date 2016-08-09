#include "mgl/shader.h"

#include "mgl/call.h"

namespace mgl {

Shader::Shader(GLenum shader_type) :
  shader_type_{shader_type},
  id_{0} {
  MGL_CALL(id_ = glCreateShader(shader_type));
}

Shader::~Shader() {
  MGL_CALL(glDeleteShader(id_));
}

void Shader::Source(const GLchar* src) {
  const GLchar* src_arr[] {src};
  MGL_CALL(glShaderSource(id_, 1, src_arr, nullptr));
}

bool Shader::Compile() {
  MGL_CALL(glCompileShader(id_));
  GLint was_successful {GL_FALSE};
  MGL_CALL(glGetShaderiv(id_, GL_COMPILE_STATUS, &was_successful));
  return was_successful == GL_TRUE;
}

std::string Shader::InfoLog() const {
  int info_log_len {0};
  int info_log_max_len {0};
  MGL_CALL(glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &info_log_max_len));
  char info_log[info_log_max_len];
  MGL_CALL(glGetShaderInfoLog(id_, info_log_max_len, &info_log_len, info_log));
  return {info_log, static_cast<size_t>(info_log_len)};
}

}   // namespace mgl
