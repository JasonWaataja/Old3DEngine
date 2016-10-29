file (GLOB SOURCES "*.cpp")
add_executable (3d ${SOURCES})

find_package (glfw3 3.2 REQUIRED)
target_link_libraries(3d glfw ${GLFW_LIBRARIES})
find_package (OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
#target_include_directories(3d ${OPENGL_INCLUDE_DIR})
target_link_libraries(3d ${OPENGL_gl_LIBRARY})

find_package (GLEW REQUIRED)
include_directories (${GLEW_INCLUDE_DIRS})
target_link_libraries (3d ${GLEW_LIBRARIES})
message (${GLEW_FOUND})
