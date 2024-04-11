set(LLVM_TARGET_DEFINITIONS ZPU.td)

tablegen(LLVM ZPUGenAsmMatcher.inc)

add_llvm_component_group(ZPU HAS_JIT)

add_public_tablegen_target(ZPUCommonTableGen)

add_llvm_target(ZPUCodeGen
  ZPUTargetMachine.cpp
  ZPUSubtarget.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  Core
  MC
  Support
  Target
  TargetParser
  GlobalISel
  SelectionDAG
  ZPUInfo
  ZPUDesc

  ADD_TO_COMPONENT
  ZPU
)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)