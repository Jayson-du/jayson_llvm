#include "MCTargetDesc/ZPUMCTargetDesc.h"
#include "ZPU.h"
#include "ZPUTargetMachine.h"
#include "llvm/CodeGen/SelectionDAGISel.h"

using namespace llvm;

namespace {

class ZPUDAGToDAGISel : public SelectionDAGISel {
public:
  static char ID;

  explicit ZPUDAGToDAGISel(ZPUTargetMachine &TM,
                           CodeGenOpt::Level OL = CodeGenOpt::Default)
      : SelectionDAGISel(ID, TM, OL) {}

  StringRef getPassName() const override {
    return "ZPU DAG->DAG Pattern Instruction Selection";
  }

  void Select(SDNode *N) override;

private:
#include "ZPUGenDAGISel.inc"
};

} // end anonymous namespace

char ZPUDAGToDAGISel::ID = 0;

/// @brief
void ZPUDAGToDAGISel::Select(SDNode *N) {
  SDLoc DL(N);
  switch (N->getOpcode()) {
  case ISD::Constant: {
    int64_t Imm = cast<ConstantSDNode>(N)->getSExtValue();
    if (-2048 <= Imm && Imm <= 2047) {
      SDValue SDImm = CurDAG->getTargetConstant(Imm, DL, MVT::i32);
      SDValue SrcReg = CurDAG->getRegister(ZPU::X0, MVT::i32);
      SDNode *Result =
          CurDAG->getMachineNode(ZPU::ADDI, DL, MVT::i32, SrcReg, SDImm);
      ReplaceNode(N, Result);
    }
  }
  }

  /// SelectCode函数是由TableGen根据td文件生成的
  SelectCode(N);
}

FunctionPass *llvm::createZPUISelDag(ZPUTargetMachine &TM) {
  return new ZPUDAGToDAGISel(TM);
}
