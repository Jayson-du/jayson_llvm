add_llvm_component_library(LLVMZPUDesc
  ZPUMCTargetDesc.cpp

  LINK_COMPONENTS
  MC
  Support
  TargetParser
  ZPUInfo

  ADD_TO_COMPONENT
  ZPU
)