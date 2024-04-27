#include "ZPUMCAsmInfo.h"
#include "llvm/TargetParser/Triple.h"

using namespace llvm;

ZPUMCAsmInfo::ZPUMCAsmInfo(const Triple &TT) {
  assert(TT.isArch32Bit() && "Only ZPU is currently supported!");
  CodePointerSize = CalleeSaveStackSlotSize = TT.isArch32Bit() ? 4 : 4;
  CommentString = "#";
  Data16bitsDirective = "\t.half\t";
  Data32bitsDirective = "\t.word\t";
}