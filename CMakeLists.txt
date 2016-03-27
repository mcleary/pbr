
cmake_minimum_required (VERSION 3.0)

project (pbr)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_subdirectory(deps/glfw)
add_subdirectory(deps/glbinding)

include_directories(deps/glfw/include)
include_directories(deps/glbinding/source/glbinding/include)

add_executable(pbr main.cpp)

target_link_libraries(pbr glfw ${GLFW_LIBRARIES})
target_link_libraries(pbr glbinding ${GLBINDING_LIBRARIES})
