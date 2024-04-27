#include "ZPUFrameLowering.h"
#include "llvm/CodeGen/MachineFunction.h"

using namespace llvm;

void ZPUFrameLowering::emitPrologue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {}

void ZPUFrameLowering::emitEpilogue(MachineFunction &MF,
                                    MachineBasicBlock &MBB) const {}

bool ZPUFrameLowering::hasFP(const MachineFunction &MF) const { return false; }