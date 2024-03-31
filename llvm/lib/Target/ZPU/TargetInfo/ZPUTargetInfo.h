#ifndef LLVM_LIB_TARGET_ZPU_TARGETINFO_H
#define LLVM_LIB_TARGET_ZPU_TARGETINFO_H

namespace llvm {
class Target;

Target &getTheZPU0Target();
}


#endif