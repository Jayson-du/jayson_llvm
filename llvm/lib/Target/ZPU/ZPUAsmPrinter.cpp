#include "MCTargetDesc/ZPUMCTargetDesc.h"
#include "TargetInfo/ZPUTargetInfo.h"
#include "ZPUMCInstLower.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

namespace {
class ZPUAsmPrinter : public AsmPrinter {
  /// 指令降阶器
  ZPUMCInstLower MCInstLowering;

public:
  ZPUAsmPrinter(TargetMachine &TM, std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)), MCInstLowering(OutContext, *this) {
  }

  /// @brief: 每个目标后端至少需要覆写基类llvm::AsmPrinter中的
  ///         虚函数emitInstruction()。该函数用于将机器指令的表示形式转换为MCInst
  /// @param MI
  void emitInstruction(const MachineInstr *MI) override;

private:
  /// @brief: 该函数在ZPUGenMCPseudoLowering.inc文件中实现
  /// @param OutSteamer
  /// @param MI
  /// @return true
  /// @return false
  bool emitPseudoExpansionLowering(MCStreamer &OutSteamer,
                                   const MachineInstr *MI);
};
} // end anonymous namespace

#include "ZPUGenMCPseudoLowering.inc"

/// @brief: 每个目标后端至少需要覆写基类llvm::AsmPrinter中的
///         虚函数emitInstruction()。该函数用于将机器指令的表示形式转换为MCInst
/// @param MI
void ZPUAsmPrinter::emitInstruction(const MachineInstr *MI) {
  /// 函数emitPseudoExpansionLowering()由 TableGen
  /// 生成（定义在ZPUGenMCPseudoLowering.inc文件）。该函数用于处理伪指令
  if (emitPseudoExpansionLowering(*OutStreamer, MI)) {
    return;
  }

  MCInst TmpInst;
  MCInstLowering.Lower(MI, TmpInst);
  EmitToStreamer(*OutStreamer, TmpInst);
}

/// @brief: 将汇编打印器注册到LLVM后端
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeZPUAsmPrinter() {
  RegisterAsmPrinter<ZPUAsmPrinter> X(getTheZPU0Target());
}
