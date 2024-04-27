#ifndef LLVM_LIB_TARGET_ZPU_TARGETMACHINE_H
#define LLVM_LIB_TARGET_ZPU_TARGETMACHINE_H

#include "ZPUSubtarget.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class ZPUTargetMachine : public LLVMTargetMachine {
public:
  ZPUTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                   StringRef FS, const TargetOptions &Options,
                   std::optional<Reloc::Model> RM,
                   std::optional<CodeModel::Model> CM, CodeGenOpt::Level OL,
                   bool JIT, bool isLittle = true);
  ~ZPUTargetMachine() override;

  const ZPUSubtarget *getSubtargetImpl(const Function &F) const override {
    return &Subtarget;
  }

  const ZPUSubtarget *getSubtargetImpl() const { return &Subtarget; }

  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
      return TLOF.get();
  }

private:
  ZPUSubtarget Subtarget;

  std::unique_ptr<TargetLoweringObjectFile> TLOF;
};
} // namespace llvm

#endif