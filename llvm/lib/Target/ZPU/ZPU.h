#ifndef LLVM_LIB_TARGET_ZPU_H
#define LLVM_LIB_TARGET_ZPU_H

namespace llvm {

class ZPUTargetMachine;
class FunctionPass;

/// @brief 创建目标后端ZPU的指令选择的PASS
/// @param TM
/// @return FunctionPass*
FunctionPass *createZPUISelDag(ZPUTargetMachine &TM);

} // namespace llvm

#endif