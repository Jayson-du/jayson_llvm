#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
struct Thedawn : public FunctionPass {
  static char ID;
  Thedawn() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
    errs() << "Hello The dawn";
    errs().write_escaped(F.getName()) << '\n';
    return false;
  }
}; // end of struct Thedawn
} // end of anonymous namespace

char Thedawn::ID = 0;

static RegisterPass<Thedawn> X("thedawn", "hello the dawn pass",
                               false /* Only looks at CFG */,
                               false /* Analysis Pass */);
