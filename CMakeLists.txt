
cmake_minimum_required (VERSION 3.0)

project (pbr)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_subdirectory(deps/glfw)
add_subdirectory(deps/glbinding)

include_directories(deps/glfw/include)
include_directories(deps/glbinding/source/glbinding/include)
include_directories(deps/glm)
include_directories(deps/stb)

add_executable(pbr
    main.cpp
    Drawables.h
    Drawables.cpp
    Shader.h
    Shader.cpp
    Timer.h
    Timer.cpp
    Camera.h
    Camera.cpp
    Materials.h
    Materials.cpp

    shaders/vertex.glsl
    shaders/fragment.glsl
    shaders/vertex_texture.glsl
    shaders/fragment_texture.glsl
    shaders/phong_pbr_vert.glsl
    shaders/phong_pbr_frag.glsl
    shaders/phong_vert.glsl
    shaders/phong_frag.glsl
    shaders/sky_vert.glsl
    shaders/sky_frag.glsl
	shaders/ground_vert.glsl
    shaders/ground_frag.glsl
    shaders/lines_vert.glsl
	shaders/lines_frag.glsl
    shaders/skybox_vert.glsl
    shaders/skybox_frag.glsl
	shaders/stars_vert.glsl
	shaders/stars_frag.glsl
	shaders/space_vert.glsl
	shaders/space_frag.glsl
)

source_group("Shaders" FILES
    shaders/vertex.glsl
    shaders/fragment.glsl
    shaders/vertex_texture.glsl
    shaders/fragment_texture.glsl
    shaders/phong_pbr_vert.glsl
    shaders/phong_pbr_frag.glsl
    shaders/phong_vert.glsl
    shaders/phong_frag.glsl
    shaders/sky_vert.glsl
    shaders/sky_frag.glsl
    shaders/ground_vert.glsl
    shaders/ground_frag.glsl
    shaders/lines_vert.glsl
	shaders/lines_frag.glsl
    shaders/skybox_vert.glsl
    shaders/skybox_frag.glsl
	shaders/stars_vert.glsl
	shaders/stars_frag.glsl
	shaders/space_vert.glsl
	shaders/space_frag.glsl
)

target_link_libraries(pbr glfw ${GLFW_LIBRARIES})
target_link_libraries(pbr glbinding ${GLBINDING_LIBRARIES})
