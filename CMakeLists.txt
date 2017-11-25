cmake_minimum_required(VERSION 3.5)
project(humanoide)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(humanoide ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(humanoide ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
