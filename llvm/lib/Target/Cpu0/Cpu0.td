//===-- Cpu0.td - Describe the Cpu0 Target Machine ----*- tablegen -*-===//
//
//                  The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.

//
//===----------------------------------------------------------------------===//
// This is the top level entry point for the Cpu0 target.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Target-dependent interfaces
//===----------------------------------------------------------------------===//

// Register Infomation
include "Cpu0RegisterInfo.td"

// Calling Conversion
include "Cpu0Schedule.td"

// Instruction Description
include "Cpu0InstrInfo.td"

def Cpu0InstrInfo : InstrInfo;

// Whill generate Cpu0GenAsmWrite.inc included by Cpu0InstPrinter.cpp, contents
// as follows,
// void Cpu0InstPrinter::printInstruction(const MCInst *MI, raw_ostream &O) {...}
// const char* Cpu0InstPrinter::getRegisterName(unsigned RegNo) {...}
def Cpu0 : Target {
  // def Cpu0InstrInfo : InstrInfo as before.
  let InstructionSet = Cpu0InstrInfo;
}

def GenericMachineModel : SchedMachineModel{
  let MicroOpBufferSize = 0;  // The Cortex-A55 is an in-order processor
  let IssueWidth = 2;         // It dual-issues under most circumstances
  let LoadLatency = 4;        // Cycles for loads to access the cache. The
                              // optimisation guide shows that most loads have
                              // a latency of 3, but some have a latency of 4
                              // or 5. Setting it 4 looked to be good trade-off.
  let MispredictPenalty = 8;  // A branch direction mispredict.
  let PostRAScheduler = 1;    // Enable PostRA scheduler pass.
  let CompleteModel = 0;      // Covers instructions applicable to Cortex-A55.

  let FullInstRWOverlapCheck = 0;
}

def : ProcessorModel<"generic", GenericMachineModel, []>;