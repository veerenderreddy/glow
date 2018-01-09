// Copyright 2017 Facebook Inc.  All Rights Reserved.

#include "JIT.h"

#include "glow/Graph/Graph.h"
#include "glow/Graph/Nodes.h"
#include "glow/IR/Instrs.h"
#include "glow/Optimizer/Optimizer.h"

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/SourceMgr.h"

using namespace glow;
using llvm::isa;

JITBackend::~JITBackend() { clear(); }

void JITBackend::clear() { M_->clear(); }

void JITBackend::init() {
  llvm::SMDiagnostic Err;
  // Load the jit library as a new module.
  llmodule_ = llvm::parseIRFile("libjit.bc", Err, ctx_);
  GLOW_ASSERT(llmodule_.get() && "Unable to load the JIT library.");

  // Create the 'main' function into the LLVM module.
  llvm::Type *void_type = llvm::Type::getVoidTy(ctx_);
  llvm::FunctionType *jit_func_type =
      llvm::FunctionType::get(void_type, {}, false);
  func_ = llvm::Function::Create(jit_func_type, llvm::Function::ExternalLinkage,
                                 "main", llmodule_.get());

  // Setup the entry basic block and initialize the IR builder.
  llvm::BasicBlock *entry_bb = llvm::BasicBlock::Create(ctx_, "entry", func_);
  llvm::IRBuilder<> builder(entry_bb);
}

void JITBackend::doForwardPass(bool isTrain) {
  llvm_unreachable("Unimplemented.");
}
void JITBackend::registerGraphTensor(const Value *v, Tensor *t) {
  llvm_unreachable("Unimplemented.");
}
