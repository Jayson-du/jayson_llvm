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

  cmake -DCMAKE_BUILD_TYPE=Debug                      \
        -DLLVM_ENABLE_PROJECTS="clang"                \
        -DLLVM_OPTIMIZED_TABLEGEN=On                  \
        -DLLVM_PARALLEL_COMPILE_JOBS=4                \
        -DLLVM_PARALLEL_LINK_JOBS=1                   \
        -DLLVM_CCACHE_BUILD=ON                        \
        -DLLVM_JAYSON_DEBUG=1                         \
        -G "Ninja"                                    \
        -S ${path}/llvm                               \
        -B ${path}/build

  time ninja

  popd

else
  blue_log "**** will incremental compilation ****"

  pushd $path

  if [ -d "build" ]; then
    option "Whether need to delete origin build/CMakeCache.txt([y/n]):"
    read del_origin_cmakecache

    if [ ${del_origin_cmakecache} = 'y' ] || [ ${del_origin_cmakecache} = 'Y' ]; then
      blue_log "**** will delete origin CMakeCache.txt ****"
      rm -f ./CMakeCache.txt
    else
      blue_log "**** not delete origin CMakeCache.txt ****"
    fi
  fi

  cd $path/build


  cmake -DCMAKE_BUILD_TYPE=Debug                      \
      -DLLVM_ENABLE_PROJECTS="clang"                  \
      -DLLVM_OPTIMIZED_TABLEGEN=On                    \
      -DLLVM_PARALLEL_COMPILE_JOBS=4                  \
      -DLLVM_PARALLEL_LINK_JOBS=1                     \
      -DLLVM_TARGETS_TO_BUILD=ZPU                     \
      -DLLVM_CCACHE_BUILD=ON                          \
      -DLLVM_JAYSON_DEBUG=1                           \
      -G "Ninja"                                      \
      -S ${path}/llvm                                 \
      -B ${path}/build

  time ninja -j 16

  popd
fi
