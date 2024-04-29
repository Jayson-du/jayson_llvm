/// @brief: 用于声明继承自llvm::TargetFrameLowering的派生类ZPUFrameLowering
///         主要设置堆栈指针

#ifndef LLVM_LIB_TARGET_ZPU_ZPUTFRAMELOWERING_H
#define LLVM_LIB_TARGET_ZPU_ZPUTFRAMELOWERING_H

#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {

class ZPUSubtarget;

/// @brief: ZPU处理器的堆栈处理
class ZPUFrameLowering : public TargetFrameLowering {
  const ZPUSubtarget &STI;

public:
  explicit ZPUFrameLowering(const ZPUSubtarget &STI)
      : TargetFrameLowering(StackGrowsDown,
                            /*StackAlignment=*/Align(16),
                            /*LocalAreaOffset=*/0),
        STI(STI) {}

  /// @brief: 分配内存
  /// @param MF
  /// @param MBB
  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;

  /// @brief: 回收栈内存
  /// @param MF
  /// @param MBB
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;

  /// @brief: 返回MF中是否应该有帧指针寄存器
  /// @param MF
  /// @return true
  /// @return false
  bool hasFP(const MachineFunction &MF) const override;
};
} // namespace llvm

#endif
