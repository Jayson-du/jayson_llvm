#!/bin/bash
# -*- coding : utf-8 -*-

source ~/script/bash/color_print.sh

path="$(cd $(dirname $0) && pwd)"

blue_log "**** will incremental compilation ****"

pushd $path

cd $path/build

option "Whether re config([y/n]):"
read reconfig
if [ ${reconfig} = 'y' ] || [ ${reconfig} = 'Y' ]; then
  cmake -DCMAKE_BUILD_TYPE=Debug                      \
        -DLLVM_ENABLE_PROJECTS="clang"                \
        -DLLVM_OPTIMIZED_TABLEGEN=On                  \
        -DLLVM_PARALLEL_COMPILE_JOBS=4                \
        -DLLVM_PARALLEL_LINK_JOBS=4                   \
        -DLLVM_TARGETS_TO_BUILD=ZPU                   \
        -DLLVM_CCACHE_BUILD=ON                        \
        -DLLVM_JAYSON_DEBUG=1                         \
        -G "Ninja"                                    \
        -S ${path}/llvm                               \
        -B ${path}/build
fi

time ninja -j 16

popd
