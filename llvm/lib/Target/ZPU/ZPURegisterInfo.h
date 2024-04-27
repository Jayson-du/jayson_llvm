#ifndef LLVM_LIB_TARGET_ZPU_ZPUREGISTERINFO_H
#define LLVM_LIB_TARGET_ZPU_ZPUREGISTERINFO_H

#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "ZPUGenRegisterInfo.inc"

namespace llvm {
class ZPURegisterInfo : public ZPUGenRegisterInfo {
public:
  explicit ZPURegisterInfo(unsigned HwMode);

  /// @brief: 用于返回被调用者保存的所有寄存器
  /// @param MF
  /// @return const MCPhysReg*
  const MCPhysReg *getCalleeSavedRegs(const MachineFunction *MF) const override;

  /// @brief: 用于返回保留的寄存器; 这些保留的寄存器是不能被分配的
  /// @param MF
  /// @return BitVector
  BitVector getReservedRegs(const MachineFunction &MF) const override;

  bool eliminateFrameIndex(MachineBasicBlock::iterator MI, int SPAdj,
                           unsigned FIOperandNum,
                           RegScavenger *RS = nullptr) const override;

  /// @brief: 用于返回保存帧指针的寄存器
  /// @param MF
  /// @return Register
  Register getFrameRegister(const MachineFunction &MF) const override;
};

} // namespace llvm

#endif
