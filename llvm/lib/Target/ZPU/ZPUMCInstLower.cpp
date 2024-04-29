#include "ZPUMCInstLower.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineOperand.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"

using namespace llvm;

ZPUMCInstLower::ZPUMCInstLower(MCContext &Ctx, AsmPrinter &Printer)
    : Ctx(Ctx), Printer(Printer) {}

/// @brief: 将机器指令的表示形式从MachineInstr转换为轻量级的MCInst
/// @param MI
/// @param OutMI
void ZPUMCInstLower::Lower(const MachineInstr *MI, MCInst &OutMI) const {
  /// 设置MCInst的opcode
  OutMI.setOpcode(MI->getOpcode());

  /// 设置MCInst的操作数
  for (const MachineOperand &MO : MI->operands()) {
    MCOperand MCOp;
    if (LowerOperand(MO, MCOp)) {
      OutMI.addOperand(MCOp);
    }
  }
}

/// @brief: 指令操作数降阶, 将MachineOperand降阶为MCOperand
/// @param MO
/// @param MCOp
/// @return true
/// @return false
/// @remark tag1: 支持操作数为寄存器与立即数的降阶
bool ZPUMCInstLower::LowerOperand(const MachineOperand &MO,
                                  MCOperand &MCOp) const {
  switch (MO.getType()) {
  case MachineOperand::MO_Register: {
    /// 判断操作数是否是隐式的def, 如果是隐式Reg操作数
    if (MO.isImplicit()) {
      return false;
    }
    MCOp = MCOperand::createReg(MO.getReg());
    break;
  }
  case MachineOperand::MO_Immediate: {
    MCOp = MCOperand::createImm(MO.getImm());
    break;
  }
  default: {
    llvm_unreachable("Unknown operand type!");
  }
  }

  return true;
}
