#include "ZPUTargetMachine.h"

#include "TargetInfo/ZPUTargetInfo.h"

#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/BasicTTIImpl.h"
#include "llvm/CodeGen/GlobalISel/CSEInfo.h"
#include "llvm/CodeGen/GlobalISel/IRTranslator.h"
#include "llvm/CodeGen/GlobalISel/InstructionSelect.h"
#include "llvm/CodeGen/GlobalISel/Legalizer.h"
#include "llvm/CodeGen/GlobalISel/RegBankSelect.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/Function.h"
#include "llvm/InitializePasses.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetOptions.h"

#include <iostream>
#include <optional>
#include <string>

using namespace llvm;

/// @brief 注册ZPU的目标架构
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeZPUTarget() {
  // Register the target.
  RegisterTargetMachine<ZPUTargetMachine> X((getTheZPU0Target()));
}

static std::string computeDataLayout(const Triple &TT, StringRef CPU,
                                     const TargetOptions &Options,
                                     bool isLittle) {
  std::string Ret = "e";

  return Ret;
}

static Reloc::Model getEffectiveRelocModel(bool JIT,
                                           std::optional<Reloc::Model> RM) {
  if (!RM || JIT) {
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
    : LLVMTargetMachine(T, computeDataLayout(TT, CPU, Options, isLittle), TT,
                        CPU, FS, Options, getEffectiveRelocModel(JIT, RM),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL) {
  std::cout << "****" << std::endl;
  std::cout << "This is a llvm backend create by dute" << std::endl;
  std::cout << "ZPU (32-bit big endian)" << std::endl;
  std::cout << "****" << std::endl;
}


ZPUTargetMachine::~ZPUTargetMachine() = default;