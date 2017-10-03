#!/bin/bash

mkdir -p deps-build/glfw
mkdir -p deps-build/glm
mkdir -p deps-build/glbinding

mkdir -p deps-install/stb
cp -rfv deps/stb deps-install

pushd deps-build

pushd glfw
cmake -G "Unix Makefiles" ../../deps/glfw -DGLFW_BUILD_DOCS:BOOL=OFF -DGLFW_BUILD_EXAMPLES:BOOL=OFF -DGLFW_BUILD_TESTS:BOOL=OFF -DCMAKE_INSTALL_PREFIX=../../deps-install/glfw
make -j2
make install
popd

pushd glm
cmake -G "Unix Makefiles" ../../deps/glm -DCMAKE_INSTALL_PREFIX=../../deps-install/glm
make -j2
make install
popd

pushd glbinding
cmake -G "Unix Makefiles" ../../deps/glbinding -DBUILD_SHARED_LIBS:BOOL=OFF -DOPTION_BUILD_GPU_TESTS:BOOL=OFF -DOPTION_BUILD_TESTS:BOOL=OFF -DOPTION_BUILD_TOOLS:BOOL=OFF -DCMAKE_INSTALL_PREFIX=../../deps-install/glbinding
make -j2
make install
popd

popd

