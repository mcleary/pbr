cmake_minimum_required (VERSION 3.0)

project (pbr)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/deps/install/glfw/lib/cmake/glfw3")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/deps/install/glbinding")

find_package(glfw3 REQUIRED)
find_package(glbinding REQUIRED)
find_package(glm REQUIRED)

include_directories(deps/install/stb)

add_definitions(-DGLFW_INCLUDE_NONE)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

if(WIN32)	
	list(APPEND CMAKE_CXX_FLAGS "/MP")	
endif()

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
    pbr/Grid.h
    pbr/Grid.cpp
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

set(
    SCRIPTS_SRC
    BuildDependencies.bat
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

source_group(
    "Scripts" 
    FILES ${SCRIPTS_SRC}
)

target_link_libraries(
    pbr
	glbinding::glbinding
	glbinding::glbinding-aux
	glfw
	glm
)