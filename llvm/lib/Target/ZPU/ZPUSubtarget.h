#ifndef LLVM_LIB_TARGET_ZPUSUBTARGET_H
#define LLVM_LIB_TARGET_ZPUSUBTARGET_H

#include "ZPUFrameLowering.h"
#include "ZPUISelLowering.h"
#include "ZPUInstrInfo.h"
#include "ZPURegisterInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "ZPUGenSubtargetInfo.inc"

namespace llvm {

class ZPUTargetMachine;
class ZPUSubtarget : public ZPUGenSubtargetInfo {
  ZPUTargetLowering TLInfo;
  ZPUFrameLowering FrameLowering;
  ZPUInstrInfo InstrInfo;
  ZPURegisterInfo RegInfo;

public:
  ZPUSubtarget(const Triple &TT, StringRef CPU, StringRef TuneCPU,
               StringRef FS, ZPUTargetMachine &TM);

  const ZPUTargetLowering *getTargetLowering() const override {
    return &TLInfo;
  }

  const ZPUFrameLowering *getFrameLowering() const override {
    return &FrameLowering;
  }

  const ZPUInstrInfo *getInstrInfo() const override { return &InstrInfo; }

  const ZPURegisterInfo *getRegisterInfo() const override { return &RegInfo; }

private:
  void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);

  /// @brief: 初始化ZPUSubtarget
  /// @param TT
  /// @param CPU
  /// @param FS
  /// @return ZPUSubtarget&
  ZPUSubtarget &initializeSubtargetDependencies(const Triple &TT, StringRef CPU,
                                                StringRef FS);
};

} // namespace llvm

#endif
