
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
	  shaders/earth_vert.glsl
	  shaders/earth_frag.glsl
    shaders/sky_vert.glsl
    shaders/sky_frag.glsl
	  shaders/ground_vert.glsl
    shaders/ground_frag.glsl
    shaders/clouds_vert.glsl
    shaders/clouds_frag.glsl

    textures/earth_8k.jpg
    textures/earth_clouds_8k.jpg
    textures/earth_night_8k.jpg
    textures/earth_ocean_color_8k.jpg
    textures/ocean_mask_8k.png
    textures/starfield.jpg
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
    shaders/earth_vert.glsl
    shaders/earth_frag.glsl
    shaders/sky_vert.glsl
    shaders/sky_frag.glsl
    shaders/ground_vert.glsl
    shaders/ground_frag.glsl
    shaders/clouds_vert.glsl
    shaders/clouds_frag.glsl
)

source_group("Textures" FILES
    textures/earth_8k.jpg
    textures/earth_clouds_8k.jpg
    textures/earth_night_8k.jpg
    textures/earth_ocean_color_8k.jpg
    textures/ocean_mask_8k.png
    textures/starfield.jpg
)

target_link_libraries(pbr glfw ${GLFW_LIBRARIES})
target_link_libraries(pbr glbinding ${GLBINDING_LIBRARIES})
