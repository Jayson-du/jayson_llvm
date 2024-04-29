/// @file 该文件定义ZPUMCInstLower,
///       负责将机器指令的表示形式从"MachineInstr"转换为轻量级的"MCInst"

#ifndef LLVM_LIB_TARGET_ZPU_ZPUMCINSTLOWER_H
#define LLVM_LIB_TARGET_ZPU_ZPUMCINSTLOWER_H

namespace llvm {

class MCContext;
class AsmPrinter;
class MachineInstr;
class MachineOperand;
class MCInst;
class MCOperand;

class ZPUMCInstLower {
  MCContext &Ctx;
  AsmPrinter &Printer;

public:
  ZPUMCInstLower(MCContext &Ctx, AsmPrinter &Printer);

  /// @brief: 将机器指令的表示形式从MachineInstr转换为轻量级的MCInst
  /// @param MI
  /// @param OutMI
  void Lower(const MachineInstr *MI, MCInst &OutMI) const;

private:
  /// @brief: 指令操作数降阶, 将MachineOperand降阶为MCOperand
  /// @param MO
  /// @param MCOp
  /// @return true
  /// @return false
  /// @remark tag1: 支持操作数为寄存器与立即数的降阶
  bool LowerOperand(const MachineOperand &MO, MCOperand &MCOp) const;
};
} // namespace llvm

#endif
