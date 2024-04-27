#ifndef LLVM_LIB_TARGET_ZPU_MCTARGETDESC_H
#define LLVM_LIB_TARGET_ZPU_MCTARGETDESC_H

/// 在此处获取ZPU寄存器枚举符号
#define GET_REGINFO_ENUM
#include "ZPUGenRegisterInfo.inc"

#define GET_INSTRINFO_ENUM
#include "ZPUGenInstrInfo.inc"

#define GET_SUBTARGETiNFO_ENUM
#include "ZPUGenSubtargetInfo.inc"

#endif