#!/bin/bash
# -*- coding : utf-8 -*-

source ~/script/bash/color_print.sh

path="$(cd $(dirname $0) && pwd)"

blue_log "**** will incremental compilation ****"

pushd $path

cd $path/build

cmake -DCMAKE_BUILD_TYPE=Debug              \
      -DLLVM_ENABLE_PROJECTS="clang"        \
      -DLLVM_OPTIMIZED_TABLEGEN=On          \
      -DLLVM_PARALLEL_COMPILE_JOBS=4        \
      -DLLVM_PARALLEL_LINK_JOBS=1           \
      -DLLVM_TARGETS_TO_BUILD=ZPU           \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=YES   \
      -DBUILD_SHARED_LIBS=ON                \
      -DLLVM_USE_LINKER=lld                 \
      -DLLVM_CCACHE_BUILD=ON                \
      -G "Ninja"                            \
      -S ${path}/llvm                       \
      -B ${path}/build

time ninja -j 16

popd
