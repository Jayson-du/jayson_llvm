#ifndef LLVM_LIB_TARGET_ZPU_TARGETMACHINE_H
#define LLVM_LIB_TARGET_ZPU_TARGETMACHINE_H

#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Target/TargetMachine.h"
#include <memory>
#include <optional>

namespace llvm {
class ZPUTargetMachine : public LLVMTargetMachine {
public:
  ZPUTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                   StringRef FS, const TargetOptions &Options,
                   std::optional<Reloc::Model> RM,
                   std::optional<CodeModel::Model> CM, CodeGenOpt::Level OL,
                   bool JIT, bool isLittle = true);
  ~ZPUTargetMachine() override;
};
}

#endif