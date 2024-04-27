#ifndef LLVM_LIB_TARGET_ZPU_MCTARGETDESC_ZPUMCASMINFO_H
#define LLVM_LIB_TARGET_ZPU_MCTARGETDESC_ZPUMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {

class Triple;

class ZPUMCAsmInfo : public MCAsmInfoELF {
public:
  explicit ZPUMCAsmInfo(const Triple &TT);
};
} // namespace llvm

#endif