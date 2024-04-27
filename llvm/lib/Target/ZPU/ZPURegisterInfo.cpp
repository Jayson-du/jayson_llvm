#include "MCTargetDesc/ZPUMCTargetDesc.h"
#include "ZPUFrameLowering.h"
#include "ZPURegisterInfo.h"
#include "ZPUSubtarget.h"

#define GET_REGINFO_TARGET_DESC
#include "ZPUGenRegisterInfo.inc"

using namespace llvm;

ZPURegisterInfo::ZPURegisterInfo(unsigned HwMode)
    : ZPUGenRegisterInfo(ZPU::X1, /**/ 0, /*EHFlavor*/ 0,
                         /*PC*/ 0, HwMode) {}

const MCPhysReg *
ZPURegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return CC_Save_SaveList;
}

BitVector ZPURegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  Reserved.set(ZPU::X0);
  Reserved.set(ZPU::X2);
  Reserved.set(ZPU::X3);
  Reserved.set(ZPU::X4);
  return Reserved;
}

bool ZPURegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator MI,
                                          int SPAdj, unsigned FIOPerandNum,
                                          RegScavenger *RS) const {
  return false;
}

Register ZPURegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return ZPU::X8;
}
