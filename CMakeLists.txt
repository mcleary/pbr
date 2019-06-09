cmake_minimum_required (VERSION 3.0)

project (pbr)

set(CMAKE_CXX_STANDARD 14)

if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    conan_basic_setup()
endif()

find_package(glfw3 REQUIRED)
find_package(glbinding REQUIRED)
find_package(glm REQUIRED)

add_definitions(-DGLFW_INCLUDE_NONE)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

file(
	GLOB TEXTURES_SRC
	textures/*.jpg
	textures/*.png
)

file(
	GLOB SHADERS_SRC
	shaders/*.glsl
)

set(
	DATA_SRC
	data/stars.txt
)

set(
	CODE_SRC
	pbr/main.cpp
	pbr/Axis.h
	pbr/Axis.cpp
	pbr/Geometry.h
	pbr/Transform.h
	pbr/Transform.cpp
	pbr/Drawable.h
	pbr/Drawable.cpp
	pbr/Animator.h
	pbr/Animator.cpp
	pbr/Scene.h
	pbr/Scene.cpp
	pbr/Light.h
	pbr/Light.cpp
	pbr/LinesGeometry.h
	pbr/LinesGeometry.cpp
	pbr/Mesh.h
	pbr/Mesh.cpp
	pbr/SphereMesh.h
	pbr/SphereMesh.cpp
	pbr/Sphere.h
	pbr/Sphere.cpp
	pbr/Shader.h
	pbr/Shader.cpp
	pbr/Material.h
	pbr/Material.cpp
	pbr/MaterialParams.h
	pbr/PhongMaterial.h
	pbr/PhongMaterial.cpp
	pbr/LinesMaterial.h
	pbr/LinesMaterial.cpp	
	pbr/Timer.h
	pbr/Timer.cpp
	pbr/Camera.h
	pbr/Camera.cpp
	pbr/Earth.h
	pbr/Earth.cpp
	pbr/Moon.h
 	pbr/Moon.cpp
)

add_executable(pbr
    .gitignore
	${CODE_SRC}
	${SHADERS_SRC}
	${TEXTURES_SRC}
	${DATA_SRC}
    ${SCRIPTS_SRC})

source_group(
	"Assets\\Shaders" 
    FILES ${SHADERS_SRC}
)

source_group(
	"Assets\\Data" 
    FILES ${DATA_SRC}
)

source_group(
	"Assets\\Textures" 
    FILES ${TEXTURES_SRC}
)

target_link_libraries(
    pbr
    PUBLIC 
	glbinding::glbinding
	glbinding::glbinding-aux
	glfw	
)

target_include_directories(pbr PRIVATE ${GLM_INCLUDE_DIRS})