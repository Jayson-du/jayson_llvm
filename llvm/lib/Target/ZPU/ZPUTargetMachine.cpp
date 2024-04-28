#include "ZPUTargetMachine.h"
#include "TargetInfo/ZPUTargetInfo.h"
#include "ZPU.h"

#include "llvm/ADT/Optional.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

namespace {

/// brief: 用于定制代码生成流水线中的各种Pass
class ZPUPassConfig : public TargetPassConfig {
public:
  ZPUPassConfig(ZPUTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  /// @brief: 用于安装目标后端的指令选择Pass
  /// @return true
  /// @return false
  bool addInstSelector() override {
    addPass(createZPUISelDag(getZPUTargetMachine()));
    return false;
  }

private:
  ZPUTargetMachine &getZPUTargetMachine() const {
    return getTM<ZPUTargetMachine>();
  }
};
} // namespace

StringRef computeDataLayout(const Triple &TT) {
  assert(TT.isArch32Bit() && "Only ZPU32 is currently support!");
  return "e-m:e-p:32:32-i64:64-n32-s128";
}

Reloc::Model getEffectiveRelocModel(bool JIT, Optional<Reloc::Model> RM) {
  if (!RM.has_value() || JIT) {
    return Reloc::Static;
  }
  return *RM;
}

ZPUTargetMachine::ZPUTargetMachine(const Target &T, const Triple &TT,
                                   StringRef CPU, StringRef FS,
                                   const TargetOptions &Options,
                                   std::optional<Reloc::Model> RM,
                                   std::optional<CodeModel::Model> CM,
                                   CodeGenOpt::Level OL, bool JIT,
                                   bool isLittle)
    : LLVMTargetMachine(T, computeDataLayout(TT), TT, CPU, FS, Options,
                        getEffectiveRelocModel(JIT, RM),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      Subtarget(TT, CPU, CPU, FS, *this),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()) {
  initAsmInfo();
}

ZPUTargetMachine::~ZPUTargetMachine() = default;

TargetPassConfig *ZPUTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new ZPUPassConfig(*this, PM);
}

/// @brief 注册ZPU的目标架构
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeZPUTarget() {
  // Register the target.
  RegisterTargetMachine<ZPUTargetMachine> X((getTheZPU0Target()));
}
