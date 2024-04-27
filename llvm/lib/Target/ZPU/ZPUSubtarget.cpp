#include "ZPUSubtarget.h"
#include "ZPUTargetMachine.h"

using namespace llvm;

#define DEBUG_TYPE "ZPU-subtarget"

/// #define GET_SUBTARGETINFO_MC_DESC
#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR

#include "ZPUGenSubtargetInfo.inc"

ZPUSubtarget::ZPUSubtarget(const Triple &TT, StringRef CPU, StringRef TuneCPU,
                           StringRef FS, ZPUTargetMachine &TM)
    : ZPUGenSubtargetInfo(TT, CPU, TuneCPU, FS), TLInfo(TM),
      FrameLowering(initializeSubtargetDependencies(TT, CPU, FS)),
      InstrInfo(*this), RegInfo(getHwMode()) {}

ZPUSubtarget &ZPUSubtarget::initializeSubtargetDependencies(const Triple &TT,
                                                            StringRef CPU,
                                                            StringRef FS) {
  if (CPU.empty()) {
    assert(TT.isArch32Bit() && "Only ZPU is currently supported!");

    // 设置处理器默认名称为"generic-zpu"
    CPU = "generic-zpu";
  }

  // 这个函数的定义在ZPUGenSubtargetInfo.inc文件中
  ParseSubtargetFeatures(CPU, CPU, FS);

  return *this;
}
