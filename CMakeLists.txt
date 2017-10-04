
cmake_minimum_required (VERSION 3.0)

project (pbr)

if(UNIX)

	execute_process(COMMAND sh BuildDependencies.sh
				    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

elseif(WINDOWS)

	execute_process(COMMAND BuildDependencies.bat)

endif()

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/deps-install/glfw/lib/cmake/glfw3")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/deps-install/glbinding")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/deps-install/glm/lib/cmake/glm")

find_package(glfw3 3.2 REQUIRED)
find_package(glbinding REQUIRED)
find_package(glm REQUIRED)

include_directories(deps-install/glbinding/include)
include_directories(deps-install/glm/include)
include_directories(deps-install/stb)

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

    # set(CMAKE_OSX_DEPLOYMENT_TARGET "10.12" CACHE STRING "macOS version" FORCE)
endif(APPLE)

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

target_link_libraries(pbr glfw ${GLFW_LIBRARIES})
target_link_libraries(pbr glbinding ${GLBINDING_LIBRARIES})

if (APPLE)
	set_target_properties(pbr PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Pbr")
endif(APPLE)

