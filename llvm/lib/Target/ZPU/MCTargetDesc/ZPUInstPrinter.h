#ifndef LLVM_LIB_TARGET_ZPU_MCTARGETDESC_ZPUINSTPRINTER_H
#define LLVM_LIB_TARGET_ZPU_MCTARGETDESC_ZPUINSTPRINTER_H

#include "llvm/MC/MCInstPrinter.h"

namespace llvm {
class ZPUInstPrinter : public MCInstPrinter {
public:
  ZPUInstPrinter(const MCAsmInfo &MAI, const MCInstrInfo &MII,
                 const MCRegisterInfo &MRI)
      : MCInstPrinter(MAI, MII, MRI) {}

  /// @brief: 每个目标后端至少需要覆写基类llvm::MCInstPrinter中的
  ///         虚函数printInst()。该函数用于打印汇编代码
  /// @param MI
  /// @param Address
  /// @param Annot
  /// @param STI
  /// @param OS
  void printInst(const MCInst *MI, uint64_t Address, StringRef Annot,
                 const MCSubtargetInfo &STI, raw_ostream &OS) override;

private:
  std::pair<const char *, uint64_t> getMnemonic(const MCInst *MI) override;

  /// @brief: 函数由TableGen生成的，其实现位于ZPUGenAsmWriter.inc文件，
  ///         这里需要提供其函数声明
  /// @param MI
  /// @param Address
  /// @param O
  void printInstruction(const MCInst *MI, uint64_t Address, raw_ostream &O);

  /// @brief: 函数由TableGen生成的，其实现位于ZPUGenAsmWriter.inc文件，
  ///         这里需要提供其函数声明
  /// @param MI
  /// @param Address
  /// @param bool
  bool printAliasInstr(const MCInst *MI, uint64_t Address, raw_ostream &O);

  /// @brief Get the Register Name object
  /// @param RegNo
  /// @param AltIdx
  /// @return const char*
  /// @remark: 原始的函数签名是"static const char *getRegisterName(unsigned
  ///                        RegNo, unsigned AltIdx);"
  ///          现在的函数签名改成了"static const char
  ///          *getRegisterName(MCRegister RegNo, unsigned AltIdx);"
  static const char *getRegisterName(MCRegister RegNo, unsigned AltIdx);

  void printCustomAliasOperand(const MCInst *MI, uint64_t Address,
                               unsigned OpIdx, unsigned PrintMethodIdx,
                               raw_ostream &O);

  /// @brief: 打印指令操作数
  /// @param MI
  /// @param OpNo
  /// @param O
  void printOperand(const MCInst *MI, unsigned OpNo, raw_ostream &O);
};

} // namespace llvm

#endif
