
add_llvm_library(LLVMCpu0Desc
  Cpu0MCAsmInfo.cpp
  Cpu0MCTargetDesc.cpp
  Cpu0ABIInfo.cpp  
  
  LINK_COMPONENTS
  Cpu0AsmPrinter
  
)
