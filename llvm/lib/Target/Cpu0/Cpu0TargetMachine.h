//===-- Cpu0TargetMachine.h - Define TargetMachine for Cpu0 -----*- C++ -*-===//
//
//                    The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===
//
// This file declares the Cpu0 specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===

#ifndef LLVM_LIB_TARGET_CPU0_CPU0TARGETMACHINE_H
#define LLVM_LIB_TARGET_CPU0_CPU0TARGETMACHINE_H

#include "Cpu0Subtarget.h"
#include "llvm/CodeGen/Passes.h"
#include "MCTargetDesc/Cpu0ABIInfo.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/Target/TargetMachine.h"

#include <optional>

namespace llvm {

class Cpu0TargetMachine : public LLVMTargetMachine {
public:
  Cpu0TargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                    StringRef FS, const TargetOptions &Options,
                    std::optional<Reloc::Model> RM, std::optional<CodeModel::Model> CM,
                    CodeGenOpt::Level OL, bool JIT);


  const Cpu0ABIInfo &getABI() const { return ABI; }

  const Cpu0Subtarget *getSubtargetImpl() const {
    return &DefaultSubtarget;
  }
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
private:
  Cpu0ABIInfo ABI;
  Cpu0Subtarget DefaultSubtarget;
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
};
}
#endif