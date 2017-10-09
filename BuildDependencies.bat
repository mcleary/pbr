@echo off

set VS_GEN="Visual Studio 14 2015 Win64"

mkdir deps\source
mkdir deps\build
mkdir deps\install

mkdir deps\build\glfw
mkdir deps\build\glm
mkdir deps\build\glbinding

pushd deps\source
git clone https://github.com/nothings/stb --depth 1
git clone https://github.com/g-truc/glm --depth 1
git clone https://github.com/cginternals/glbinding --depth 1
git clone https://github.com/glfw/glfw --depth 1
popd

mkdir deps\install\stb
copy -v deps/source/stb/*.h deps/install/stb

pushd deps\build

pushd glfw
cmake -G %VS_GEN% ../../source/glfw -DGLFW_BUILD_DOCS:BOOL=OFF -DGLFW_BUILD_EXAMPLES:BOOL=OFF -DGLFW_BUILD_TESTS:BOOL=OFF -DCMAKE_INSTALL_PREFIX=../../install/glfw
cmake --build . --target install --config Release --
popd

pushd glm
cmake -G %VS_GEN% ../../source/glm -DCMAKE_INSTALL_PREFIX=../../install/glm
cmake --build . --target install --config Release --
popd

pushd glbinding
cmake -G %VS_GEN% ../../source/glbinding -DOPTION_BUILD_GPU_TESTS:BOOL=OFF -DOPTION_BUILD_TESTS:BOOL=OFF -DOPTION_BUILD_TOOLS:BOOL=OFF -DCMAKE_INSTALL_PREFIX=../../install/glbinding
cmake --build . --target install --config Release --
popd

popd