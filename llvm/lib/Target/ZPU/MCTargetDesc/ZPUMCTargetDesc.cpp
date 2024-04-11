#include "ZPUMCTargetDesc.h"
#include "TargetInfo/ZPUTargetInfo.h"

#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCELFStreamer.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MachineLocation.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/TargetParser/Triple.h"

using namespace llvm;

#define GET_REGINFO_MC_DESC
/// #include "ZPUGenRegisterInfo.inc"

/// @brief 注册ZPU寄存器信息的回调函数
/// @param TT
/// @return 含有指定架构的寄存器信息
/// static MCRegisterInfo *createZPURegisterInfo(const Triple &TT) {
///   MCRegisterInfo *X = new MCRegisterInfo();
///   InitZPUMCRegisterInfo(X, ZPU::RA);
///   return X;
/// }

/// @brief 注册ZPU的目标格式信息
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeZPUTargetMC() {
  for (Target *target : {&getTheZPU0Target()}) {
    /// 注册寄存器信息
  }
}