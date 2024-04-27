#include "MCTargetDesc/ZPUMCTargetDesc.h"
#include "ZPUInstPrinter.h"

#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCRegister.h"
#include "llvm/Support/FormattedStream.h"

using namespace llvm;

#define PRINT_ALIAS_INSTR
#include "ZPUGenAsmWriter.inc"

void ZPUInstPrinter::printInst(const MCInst *MI, uint64_t Address,
                               StringRef Annot, const MCSubtargetInfo &STI,
                               raw_ostream &OS) {

  /// 优先打印指令的别名，如果失败，则根据汇编格式打印指令
  if (!printAliasInstr(MI, Address, OS)) {
    printInstruction(MI, Address, OS);
  }
}

void ZPUInstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
                                  raw_ostream &OS) {
  /// 目前仅支持打印指令的操作数为寄存器、立即数或表达式的情形
  const MCOperand &MO = MI->getOperand(OpNo);

  if (MO.isReg()) {
    OS << getRegisterName(MCRegister(MO.getReg()), ZPU::ABIRegAltName);
    return;
  }

  if (MO.isImm()) {
    OS << MO.getImm();
    return;
  }

  assert(MO.isExpr() && "Unknown operand kind in printOperand!");
  MO.getExpr()->print(OS, &MAI);
}
