@echo off

set VS_GEN="Visual Studio 15 2017 Win64"
REM set VS_ARCH="x64"

mkdir deps\source
mkdir deps\build
mkdir deps\install

mkdir deps\build\glfw
mkdir deps\build\glm
mkdir deps\build\glbinding

pushd deps\source
git clone https://github.com/nothings/stb --depth 1 --branch master
git clone https://github.com/g-truc/glm --depth 1 --branch 0.9.9.5
git clone https://github.com/cginternals/glbinding --depth 1 --branch v3.1.0
git clone https://github.com/glfw/glfw --depth 1 --branch 3.3
popd

mkdir deps\install\stb
copy deps/source/stb/*.h deps/install/stb

pushd deps\build

pushd glfw
cmake -G %VS_GEN% %VS_ARCH% ../../source/glfw -DGLFW_BUILD_DOCS:BOOL=OFF -DGLFW_BUILD_EXAMPLES:BOOL=OFF -DGLFW_BUILD_TESTS:BOOL=OFF -DCMAKE_INSTALL_PREFIX=../../install/glfw
cmake --build . --target install --config Release --
popd

pushd glm
cmake -G %VS_GEN% %VS_ARCH% ../../source/glm -DCMAKE_INSTALL_PREFIX=../../install/glm -DGLM_TEST_ENABLE:BOOL=OFF
cmake --build . --target install --config Release --
popd

pushd glbinding
cmake -G %VS_GEN% %VS_ARCH% ../../source/glbinding -DOPTION_BUILD_EXAMPLES:BOOL=OFF -DOPTION_BUILD_TESTS:BOOL=OFF -DBUILD_SHARED_LIBS:BOOL=OFF -DOPTION_BUILD_TOOLS:BOOL=OFF -DCMAKE_INSTALL_PREFIX=../../install/glbinding
cmake --build . --target install --config Debug --
popd

popd