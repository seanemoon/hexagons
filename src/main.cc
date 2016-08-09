#include "SDL2/SDL.h"

#include <functional>
#include <memory>
#include <iostream>

#include "mgl/mgl.h"
#include "util/managed.h"

int main(int /* unused */, char** /* unused */) {
  //////////////////////////////////////////////////////////////////////////////
  // INITIALIZATION
  //////////////////////////////////////////////////////////////////////////////
  SDL_Init(SDL_INIT_VIDEO);

  // Forward-compatible OpenGL 3.2 context.
  MGL_CALL(SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE));
  MGL_CALL(SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_MAJOR_VERSION, 3));
  MGL_CALL(SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_MINOR_VERSION, 2));

  util::Managed<SDL_Window*> window(
      SDL_CreateWindow(
          "OpenGL",
          SDL_WINDOWPOS_UNDEFINED,
          SDL_WINDOWPOS_UNDEFINED,
          640,
          640,
          SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN),
      SDL_DestroyWindow);

  MGL_CALL(util::Managed<SDL_GLContext> context(
    SDL_GL_CreateContext(window.get()),
    SDL_GL_DeleteContext));

  // For some reason glewInit() sets an GL_INVALID_ENUM error. This is a
  // common error and is documented here:
  //   https://www.opengl.org/wiki/OpenGL_Loading_Library
  // Upgrading to GLEW 2.0.0+ or using gl3w should fix this issue.
  //
  // TODO(seanemoon): Upgrade to GLEW 2.0.0+. This was released July 2016
  // and will probably be standard on ubuntu soon.
  glewExperimental = GL_TRUE;
  MGL_CALL_UNSAFE(GLenum glewError = glewInit());
  if (glewError != GLEW_OK) {
    std::cout << "Error inimtializing GLEW!" << std::endl;
  }

  // Version information.
  SDL_version compiled;
  SDL_VERSION(&compiled);
  std::cout
    << "SDL version (compiled): "
    << static_cast<uint>(compiled.major) << "."
    << static_cast<uint>(compiled.minor) << "."
    << static_cast<uint>(compiled.patch) << std::endl;

  SDL_version linked;
  SDL_GetVersion(&linked);
  std::cout
    << "SDL version (linked): "
    << static_cast<uint>(linked.major) << "."
    << static_cast<uint>(linked.minor) << "."
    << static_cast<uint>(linked.patch) << std::endl;

  std::cout << "GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;
  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;


  // Our shader program.
  mgl::Program program;

  // Compile and attach vertex shader to our shader program.
  mgl::Shader vertex_shader(GL_VERTEX_SHADER);
  vertex_shader.Source(
    "#version 330\n"
    "layout(location = 0) in vec2 position;\n"
    "void main() {\n"
    "  gl_Position = vec4(position, 0.0, 1.0);\n"
    "}"
  );
  if (!vertex_shader.Compile()) {
    std::cout << "Error compiling vertex shader: "
              << vertex_shader.InfoLog()
              << std::endl;
    return false;
  }
  program.AttachShader(vertex_shader);

  // Compile and attach fragment shader to our shader program.
  mgl::Shader fragment_shader(GL_FRAGMENT_SHADER);
  fragment_shader.Source(
    "#version 330\n"
    "layout(location = 0) out vec4 outColor;\n"
    "void main() {\n"
    "  outColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}"
  );
  if (!fragment_shader.Compile()) {
    std::cout << "Error compiling fragment shader: "
              << fragment_shader.InfoLog()
              << std::endl;
    return false;
  }
  program.AttachShader(fragment_shader);

  // TODO(seanemoon): I think this will be needed once we have more than one
  // color output. Figure this out when that time comes.
  // MGL_CALL(glBindFragDataLocation(program.Id(), 0, "outColor"));

  // Link the shader program.
  if (!program.Link()) {
    std::cout << "Error linking program: "
              << program.InfoLog()
              << std::endl;
    return false;
  }

  // TODO(seanemoon): Wrap this after learning a bit more about it.
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Vertex attribute array for the vertex shader.
  mgl::VertexAttributeArray position(program, "position");

  // Vertex buffer object (VBO);
  mgl::Buffer<float> vbo(GL_ARRAY_BUFFER);
  vbo.Bind();
  {
    float scale = 0.7f;
    float a = 0.0f * scale;
    float b = 0.5f * scale;
    float c = 0.86602540378 * scale;  // sqrt(3)/2
    float d = 1.0f * scale;
    vbo.Data({
       a,  d,
       c,  b,
       c, -b,
       a, -d,
      -c, -b,
      -c,  b
    });
  }
  vbo.Unbind();

  // Index buffer object (IBO);
  mgl::Buffer<uint> ibo(GL_ELEMENT_ARRAY_BUFFER);
  ibo.Bind();
  ibo.Data({
    5, 1, 4,
    4, 1, 2,
    4, 2, 3,
    5, 0, 1
  });
  ibo.Unbind();

  // Set the clear color.
  MGL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

  //////////////////////////////////////////////////////////////////////////////
  // Main Loop
  //////////////////////////////////////////////////////////////////////////////
  SDL_Event e;
  bool quit = false;
  while (!quit) {
    if (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_KEYDOWN:
        switch (e.key.keysym.sym) {
        case SDLK_q:
        case SDLK_ESCAPE:
          quit = true;
          break;
        }
      }
    }

    // Render baby's first hexagon.
    MGL_CALL(glClear(GL_COLOR_BUFFER_BIT));
    program.Use();
    vbo.Bind();
    ibo.Bind();
    position.Enable();
    position.Pointer(2, GL_FLOAT);
    MGL_CALL(glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr));
    position.Disable();
    vbo.Unbind();
    ibo.Unbind();
    program.StopUsing();
    MGL_CALL(SDL_GL_SwapWindow(window.get()));
  }

  SDL_Quit();

  return 0;
}
