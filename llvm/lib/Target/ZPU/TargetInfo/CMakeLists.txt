add_llvm_component_library(LLVMZPUInfo
  ZPUTargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support

  ADD_TO_COMPONENT
  ZPU
)