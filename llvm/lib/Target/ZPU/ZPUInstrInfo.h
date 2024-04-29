/// @brief: 指令相关信息文件

#ifndef LLVM_LIB_TARGET_ZPU_ZPUINSTRINFO_H
#define LLVM_LIB_TARGET_ZPU_ZPUINSTRINFO_H

#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "ZPUGenInstrInfo.inc"

namespace llvm {

class ZPUSubtarget;

/// ZPUGenInstrInfo是TableGen生成的一种类型, 定义在ZPUGenInstrInfo.inc文件中
class ZPUInstrInfo : public ZPUGenInstrInfo {
  const ZPUSubtarget &STI;

public:
  explicit ZPUInstrInfo(ZPUSubtarget &STI);
};
} // namespace llvm

#endif
