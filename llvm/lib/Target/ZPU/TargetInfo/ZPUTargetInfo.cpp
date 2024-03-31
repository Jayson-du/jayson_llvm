#include "ZPUTargetInfo.h"

#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheZPU0Target() {
  static Target TheZPU0Target;
  return TheZPU0Target;
}

/// @brief 注册ZPU的目标信息
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeZPUTargetInfo() {
  RegisterTarget<Triple::zpu,
                 /*HasJIT*/ true>
      X(getTheZPU0Target(), "ZPU", "ZPU (32-bit big endian)", "ZPU");
}