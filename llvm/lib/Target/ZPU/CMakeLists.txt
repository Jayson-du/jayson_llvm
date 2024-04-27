add_llvm_component_group(ZPU HAS_JIT)

set(LLVM_TARGET_DEFINITIONS ZPU.td)

# 生成汇编发射器
tablegen(LLVM ZPUGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM ZPUGenCallingConv.inc -gen-callingconv)
tablegen(LLVM ZPUGenDAGISel.inc -gen-dag-isel)
tablegen(LLVM ZPUGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM ZPUGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM ZPUGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM ZPUGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(ZPUCommonTableGen)

set(sources
  ZPUTargetMachine.cpp
  ZPUISelDAGToDAG.cpp
  ZPUAsmPrinter.cpp
  ZPUSubtarget.cpp
  ZPUISelLowering.cpp
  ZPUFrameLowering.cpp
  ZPUInstrInfo.cpp
  ZPURegisterInfo.cpp
  ZPUMCInstLower.cpp
)

add_llvm_target(ZPUCodeGen ${sources}
  LINK_COMPONENTS
  AsmPrinter
  Core
  CodeGen
  MC
  ZPUDesc
  ZPUInfo
  SelectionDAG
  Support
  Target

  ADD_TO_COMPONENT
  ZPU
)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)