@echo off
echo **********
echo cmake build vs2019 x64
echo **********

set builderDir=%~dp0

if not exist build (
   mkdir build
)


cd ./build


if exist CMakeCache.txt (
    echo "delete CMakeCache.txt"
    rm CMakeCache.txt
)

:: -S: ָ��Դ������·��
:: -B: ָ��������Ŀ����·��
:: -G: ʹ���ĸ�SDK������
:: -A: ָ��ƽ̨
:: -D: ���ݲ�����CMakeLists.txt
:: CMAKE_CONFIGURATION_TYPES: ָ��Release or Debug
@REM cmake -B %builderDir%/build                            ^
@REM       -G "Visual Studio 17 2022"                        ^
@REM       -A x64 -DPLATFORM=Windows                         ^
@REM       -DLLVM_TARGETS_TO_BUILD=ZPU                       ^
@REM       -DCMAKE_CONFIGURATION_TYPES=Debug                 ^
@REM       -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra"  ^
@REM       -DCMAKE_INSTALL_PREFIX=D:/apps/llvm/              ^
@REM       -DLLVM_PARALLEL_COMPILE_JOBS=8                    ^
@REM       -DLLVM_TARGETS_TO_BUILD=ZPU                       ^
@REM       -DLLVM_PARALLEL_LINK_JOBS=8                       ^
@REM       -S %builderDir%/llvm

cmake -B %builderDir%/build                            ^
      -G "Visual Studio 17 2022"                        ^
      -A x64 -DPLATFORM=Windows                         ^
      -DCMAKE_CONFIGURATION_TYPES=Debug                 ^
      -DLLVM_ENABLE_PROJECTS="clang"                    ^
      -DCMAKE_INSTALL_PREFIX=D:/apps/llvm/              ^
      -DLLVM_PARALLEL_COMPILE_JOBS=8                    ^
      -DLLVM_TARGETS_TO_BUILD=ZPU                       ^
      -DLLVM_PARALLEL_LINK_JOBS=8                       ^
      -S %builderDir%/llvm

cmake --build %builderDir%/build

pause