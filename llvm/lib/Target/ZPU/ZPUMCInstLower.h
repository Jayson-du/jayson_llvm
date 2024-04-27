/// @file 该文件定义ZPUMCInstLower,
/// 负责将机器指令的表示形式从"MachineInstr"转换为轻量级的"MCInst"

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

  void Lower(const MachineInstr *MI, MCInst &OutMI) const;

private:
  bool LowerOperand(const MachineOperand &MO, MCOperand &MCOp) const;
};
} // namespace llvm

#endif