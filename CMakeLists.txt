
cmake_minimum_required (VERSION 3.0)

project (pbr)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_subdirectory(deps/glfw)
add_subdirectory(deps/glbinding)

include_directories(deps/glfw/include)
include_directories(deps/glbinding/source/glbinding/include)
include_directories(deps/glm)
include_directories(deps/stb)


file(GLOB TEXTURES_SRC
	textures/*.jpg
	textures/*.png
)

file(GLOB SHADERS_SRC
	shaders/*.glsl
)

set(DATA_SRC
	data/stars.txt
)

add_executable(pbr
	WIN32
	MACOSX_BUNDLE
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

	${SHADERS_SRC}

	${TEXTURES_SRC}

	${DATA_SRC}
)

if (APPLE)
	set_source_files_properties(${SHADERS_SRC} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/shaders")
	set_source_files_properties(${TEXTURES_SRC} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/textures")
	set_source_files_properties(${DATA_SRC} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/data")
endif()

source_group("Shaders" FILES
	shaders/*.glsl
)

source_group("data" FILES
	data/*.*
)

source_group("textures" FILES
	textures/*.jpg
	textures/*.png
)

target_link_libraries(pbr glfw ${GLFW_LIBRARIES})
target_link_libraries(pbr glbinding ${GLBINDING_LIBRARIES})


if (APPLE)
	set_target_properties(pbr PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Pbr")
endif()

