#!/bin/bash
# -*- coding : utf-8 -*-

source ~/script/bash/color_print.sh

path="$(cd $(dirname $0) && pwd)"

if [ -d "$path/build" ]; then
  option "Whether full compilation is required([y/n]):"
  read compile_op
else
  compile_op='n'
fi

if [ ${compile_op} = 'y' ] || [ ${compile_op} = 'Y' ]; then
  blue_log "**** will full compilation ****"

  pushd $path

  if [ -d "build" ]; then
    cd $path/build
    rm -f ./CMakeCache.txt
    rm -rf ./bin
  fi

  cmake -DCMAKE_BUILD_TYPE=Debug              \
        -DLLVM_ENABLE_PROJECTS="clang"        \
        -DLLVM_OPTIMIZED_TABLEGEN=On          \
        -DLLVM_PARALLEL_COMPILE_JOBS=4        \
        -DLLVM_PARALLEL_LINK_JOBS=1           \
        -G "Ninja"                            \
        -S ${path}/llvm                       \
        -B ${path}/build

  time ninja

  popd

elif [ ${compile_op} = 'n' ] || [ ${compile_op} = 'N' ]; then
  blue_log "**** will incremental compilation ****"

  pushd $path

  if [ -d "build" ]; then
    cd $path/build
    rm -f ./CMakeCache.txt
  fi

  cmake -DCMAKE_BUILD_TYPE=Debug            \
      -DLLVM_ENABLE_PROJECTS="clang"        \
      -DLLVM_OPTIMIZED_TABLEGEN=On          \
      -DLLVM_PARALLEL_COMPILE_JOBS=4        \
      -DLLVM_PARALLEL_LINK_JOBS=1           \
      -G "Ninja"                            \
      -S ${path}/llvm                       \
      -B ${path}/build

  time ninja -j 16

  popd

else
  fatal_log "**** error, unhandled character ****"
fi