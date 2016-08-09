CMAKE_MINIMUM_REQUIRED(VERSION 3.5.1)

SET(CMAKE_CXX_STANDARD 11)

FILE(GLOB src_mgl_glob src/mgl/*.cc)
FILE(GLOB src_glob src/*.cc)
FILE(GLOB src_util_glob src/*.cc)
ADD_EXECUTABLE(main ${src_glob} ${src_mgl_glob} ${src_util_glob})

INCLUDE_DIRECTORIES(src/)
INCLUDE_DIRECTORIES(src/mgl)
INCLUDE_DIRECTORIES(src/util)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(main ${SDL2_LIBRARIES})

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(main ${GLEW_LIBRARIES})
endif()

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIR})
  target_link_libraries(main ${OPENGL_LIBRARIES})
endif()
