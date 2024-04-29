add_llvm_component_group(ZPU HAS_JIT)

set(LLVM_TARGET_DEFINITIONS ZPU.td)

# 生成汇编发射器
tablegen(LLVM ZPUGenAsmWriter.inc -gen-asm-writer)

# 生成调用约定
tablegen(LLVM ZPUGenCallingConv.inc -gen-callingconv)

# 生成自动指令选择相关描述
tablegen(LLVM ZPUGenDAGISel.inc -gen-dag-isel)

# 生成目标指令描述
tablegen(LLVM ZPUGenInstrInfo.inc -gen-instr-info)

# 生成伪指令下降实现
tablegen(LLVM ZPUGenMCPseudoLowering.inc -gen-pseudo-lowering)

# 生成目标寄存器和寄存器组描述
tablegen(LLVM ZPUGenRegisterInfo.inc -gen-register-info)

# 生成子目标相关信息
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