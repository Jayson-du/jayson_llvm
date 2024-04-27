add_llvm_component_library(LLVMZPUDesc
  ZPUMCTargetDesc.cpp
  ZPUMCAsmInfo.cpp
  ZPUInstPrinter.cpp

  LINK_COMPONENTS
  MC
  ZPUInfo
  Support
  TargetParser

  ADD_TO_COMPONENT
  ZPU
)