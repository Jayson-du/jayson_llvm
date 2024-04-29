#include "ZPUMCTargetDesc.h"
#include "TargetInfo/ZPUTargetInfo.h"
#include "ZPUInstPrinter.h"
#include "ZPUMCAsmInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "ZPUGenInstrInfo.inc"

#define GET_REGINFO_MC_DESC
#include "ZPUGenRegisterInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "ZPUGenSubtargetInfo.inc"

using namespace llvm;

namespace {

MCInstrInfo *createZPUMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitZPUMCInstrInfo(X);
  return X;
}

MCRegisterInfo *createZPUMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitZPUMCRegisterInfo(X, ZPU::X1);
  return X;
}

MCAsmInfo *createZPUMCAsmInfo(const MCRegisterInfo &MRI, const Triple &TT,
                              const MCTargetOptions &Options) {
  return new ZPUMCAsmInfo(TT);
}

MCSubtargetInfo *createZPUMCSubtargetInfo(const Triple &TT, StringRef CPU,
                                          StringRef FS) {
  if (CPU.empty()) {
    assert(TT.isArch32Bit() && "Only RV32 is currently "
                               "supported!");
    /// 因为在ZPU.td中定义的处理请名称是"generic-zpu",
    /// 所以在cpp文件中处理器的名称必须匹配,
    /// 否则在"MCSubtargetInfo::getSchedModelForCPU"函数中会有错误信息提示
    CPU = "generic-zpu";
  }

  return createZPUMCSubtargetInfoImpl(TT, CPU, CPU, FS);
}

MCInstPrinter *createZPUMCInstPrinter(const Triple &T, unsigned SyntaxVariant,
                                      const MCAsmInfo &MAI,
                                      const MCInstrInfo &MII,
                                      const MCRegisterInfo &MRI) {
  return new ZPUInstPrinter(MAI, MII, MRI);
}

} // end anonymous namespace

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeZPUTargetMC() {
  Target &ZPU = getTheZPU0Target();
  TargetRegistry::RegisterMCAsmInfo(ZPU, createZPUMCAsmInfo);
  TargetRegistry::RegisterMCInstrInfo(ZPU, createZPUMCInstrInfo);
  TargetRegistry::RegisterMCRegInfo(ZPU, createZPUMCRegisterInfo);
  TargetRegistry::RegisterMCSubtargetInfo(ZPU, createZPUMCSubtargetInfo);
  TargetRegistry::RegisterMCInstPrinter(ZPU, createZPUMCInstPrinter);
}
