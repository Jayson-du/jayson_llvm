#include "MCTargetDesc/ZPUMCTargetDesc.h"
#include "ZPUInstrInfo.h"
#include "ZPUSubtarget.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "ZPUGenInstrInfo.inc"

ZPUInstrInfo::ZPUInstrInfo(ZPUSubtarget &STI) : ZPUGenInstrInfo(), STI(STI) {}