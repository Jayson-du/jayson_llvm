@echo off
echo **********
echo cmake build vs2019 x64
echo **********


if not exist build (
   mkdir build
)


cd ./build


if exist CMakeCache.txt (
    echo "delete CMakeCache.txt"
    rm CMakeCache.txt
)


set builderDir=%~dp0

:: -S: 指定源码所在路径
:: -B: 指定生成项目所在路径
:: -G: 使用哪个SDK生成器
:: -A: 指定平台
:: -D: 传递参数给CMakeLists.txt
:: CMAKE_CONFIGURATION_TYPES: 指定Release or Debug
cmake -B %builderDir%/build                            ^
      -G "Visual Studio 17 2022"                        ^
      -A x64 -DPLATFORM=Windows                         ^
      -DCMAKE_CONFIGURATION_TYPES=Debug                 ^
      -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra"  ^
      -DCMAKE_INSTALL_PREFIX=D:/apps/llvm/              ^
      -DLLVM_PARALLEL_COMPILE_JOBS=8                    ^
      -DLLVM_PARALLEL_LINK_JOBS=8                       ^
      -S %builderDir%/llvm

cmake --build %builderDir%/build

pause