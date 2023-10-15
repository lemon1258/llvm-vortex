//===-- Cpu0TargetMachine.cpp - Define TargetMachine for Cpu0 ---*- C++ -*-===//
//
//                    The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Implements the info about Cpu0 target spec
//
//===----------------------------------------------------------------------===//

#include "Cpu0TargetMachine.h"
#include "Cpu0.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/MC/TargetRegistry.h"
#include <optional>

using namespace llvm;

#define DEBUG_TYPE "cpu0"

extern "C" void LLVMInitializeCpu0Target() {
  RegisterTargetMachine<Cpu0TargetMachine> X(getTheCpu0Target());
}

static std::string computeDataLayout(const Triple &TT, StringRef CPU,
                                     const TargetOptions &Options) {
  std::string Ret = "";
  
  Ret += "e";

  Ret += "-m:m";

  // Pointer size and alignment
  Ret += "-p:32:32";

  // 8 and 16 bits integers only need to have natural alignment, but try to
  // align them to 32 bits. 64 bits integers have natural alignment.
  Ret += "-i8:8:32-i16:16:32-i64:64";

  // 32 bits registers are always available and the stack is at least 64 bits aligned
  Ret += "-n32-s64";

  return Ret;
}


static Reloc::Model getEffectiveRelocModel(bool JIT,
                                           std::optional<Reloc::Model> RM) {
  if (!RM.has_value() || JIT)
    return Reloc::Static;
  return *RM;
}

Cpu0TargetMachine::Cpu0TargetMachine(const Target &T, const Triple &TT,
                                     StringRef CPU, StringRef FS,
                                     const TargetOptions &Options,
                                     std::optional<Reloc::Model> RM, 
                                     std::optional<CodeModel::Model> CM,
                                     CodeGenOpt::Level OL, bool JIT)
                      : LLVMTargetMachine(T, computeDataLayout(TT, CPU, Options), TT,
                        CPU, FS, Options, getEffectiveRelocModel(JIT, RM),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL)
{
    initAsmInfo();
}