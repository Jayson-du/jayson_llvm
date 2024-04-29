#include "ZPUFrameLowering.h"
#include "llvm/CodeGen/MachineFunction.h"

using namespace llvm;

/// @brief: 分配内存
/// @param MF
/// @param MBB
/// @remark tag1: 空实现
void ZPUFrameLowering::emitPrologue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {}
/// @brief: 回收栈内存
/// @param MF
/// @param MBB
/// @remark tag1: 空实现
void ZPUFrameLowering::emitEpilogue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {}
/// @brief: 返回MF中是否应该有帧指针寄存器
/// @param MF
/// @return true
/// @return false
/// @remark tag1: 空实现
bool ZPUFrameLowering::hasFP(const MachineFunction &MF) const { return false; }
