#include "mgl/program.h"

#include "mgl/call.h"

namespace mgl {

Program::Program() : id_{glCreateProgram()} {}

Program::~Program() {
  MGL_CALL(glDeleteProgram(id_));
}

void Program::AttachShader(const Shader& shader) {
  MGL_CALL(glAttachShader(id_, shader.Id()));
}

bool Program::Link() {
  MGL_CALL(glLinkProgram(id_));

  GLint was_successful {GL_FALSE};
  MGL_CALL(glGetProgramiv(id_, GL_LINK_STATUS, &was_successful));
  return was_successful == GL_TRUE;
}

void Program::Use() {
  MGL_CALL(glUseProgram(id_));
}

void Program::StopUsing() {
  MGL_CALL(glUseProgram(0));
}

std::string Program::InfoLog() const {
  int info_log_len {0};
  int info_log_max_len {0};
  MGL_CALL(glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &info_log_max_len));
  char info_log[info_log_max_len];
  MGL_CALL(glGetProgramInfoLog(
        id_, info_log_max_len, &info_log_len, info_log));
  return {info_log, static_cast<size_t>(info_log_len)};
}


}  // namespace mgl
