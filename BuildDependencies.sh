#!/bin/bash

mkdir -p deps/source
mkdir -p deps/build
mkdir -p deps/install

mkdir -p deps/build/glfw
mkdir -p deps/build/glm
mkdir -p deps/build/glbinding

pushd deps/source
git clone https://github.com/nothings/stb --depth 1
git clone https://github.com/g-truc/glm --depth 1
git clone https://github.com/cginternals/glbinding --depth 1
git clone https://github.com/glfw/glfw --depth 1
popd

mkdir -p deps/install/stb
cp -v deps/source/stb/*.h deps/install/stb

pushd deps/build

pushd glfw
cmake -G "Unix Makefiles" ../../source/glfw -DGLFW_BUILD_DOCS:BOOL=OFF -DGLFW_BUILD_EXAMPLES:BOOL=OFF -DGLFW_BUILD_TESTS:BOOL=OFF -DCMAKE_INSTALL_PREFIX=../../install/glfw
make -j
make install
popd

pushd glm
cmake -G "Unix Makefiles" ../../source/glm -DCMAKE_INSTALL_PREFIX=../../install/glm
make -j
make install
popd

pushd glbinding
cmake -G "Unix Makefiles" ../../source/glbinding -DOPTION_BUILD_GPU_TESTS:BOOL=OFF -DOPTION_BUILD_TESTS:BOOL=OFF -DOPTION_BUILD_TOOLS:BOOL=OFF -DCMAKE_INSTALL_PREFIX=../../install/glbinding
make -j2
make install
popd

popd

