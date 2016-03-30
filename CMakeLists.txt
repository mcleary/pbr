
cmake_minimum_required (VERSION 3.0)

project (pbr)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_subdirectory(deps/glfw)
add_subdirectory(deps/glbinding)

include_directories(deps/glfw/include)
include_directories(deps/glbinding/source/glbinding/include)
include_directories(deps/glm)

add_executable(pbr
    main.cpp
    Drawables.h
    Drawables.cpp
    Shader.h
    Shader.cpp
    Timer.h
    Timer.cpp
    shaders/vertex.glsl
    shaders/fragment.glsl
)

target_link_libraries(pbr glfw ${GLFW_LIBRARIES})
target_link_libraries(pbr glbinding ${GLBINDING_LIBRARIES})
