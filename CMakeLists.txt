cmake_minimum_required (VERSION 3.0)

project (pbr)

if(UNIX)

    add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

	set(CMAKE_CXX_STANDARD 14)

elseif(WIN32)

	execute_process(COMMAND BuildDependencies.bat)

endif()

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/deps/install/glfw/lib/cmake/glfw3")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/deps/install/glbinding")

find_package(glfw3 REQUIRED)
find_package(glbinding REQUIRED)

# include_directories(deps/install/glbinding/include)
# include_directories(deps/install/glm/include)
# include_directories(deps/install/stb)
# include_directories(deps/install/glfw/include)

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

set(CODE_SRC main2.cpp)

if (APPLE)

	add_executable(pbr	
		MACOSX_BUNDLE
		${CODE_SRC}
		${SHADERS_SRC}
		${TEXTURES_SRC}
		${DATA_SRC})

	set_source_files_properties(${SHADERS_SRC} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/shaders")
	set_source_files_properties(${TEXTURES_SRC} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/textures")
	set_source_files_properties(${DATA_SRC} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/data")
	
	set(CMAKE_OSX_DEPLOYMENT_TARGET "10.12")
	set_target_properties(pbr PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Pbr")

elseif(WIN32)

	add_executable(pbr
        .gitignore
		${CODE_SRC}
		${SHADERS_SRC}
		${TEXTURES_SRC}
		${DATA_SRC})

endif()

source_group(
	"shaders" FILES
	${SHADERS_SRC}
)

source_group(
	"data" FILES
	${DATA_SRC}
)

source_group(
	"textures" FILES
	${TEXTURES_SRC}
)

target_link_libraries(
    pbr
	glbinding::glbinding
	glfw
)