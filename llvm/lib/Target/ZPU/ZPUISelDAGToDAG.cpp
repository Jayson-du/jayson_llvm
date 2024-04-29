/// @brief: DAG选择PASS, 继承关系为:
///         PASS <- FunctionPass <- MachineFunctionPass <- SelectionDAGISel
///         <- ZPUDAGToDAGISel

#include "MCTargetDesc/ZPUMCTargetDesc.h"
#include "ZPU.h"
#include "ZPUTargetMachine.h"
#include "llvm/CodeGen/SelectionDAGISel.h"

using namespace llvm;

namespace {

class ZPUDAGToDAGISel : public SelectionDAGISel {
public:
  /// TODO
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
  /// TODO:ISD值得是什么, 操作数或者指令？
  /// 特殊处理ISD::Constant类型的Node, 将数替换为寄存器
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

/// @brief: 在ZPUTargetMachine.cpp文件中使用,
///         用于将ZPU特定的DAG选择PASS注册到PassManager中
/// @param TM
/// @return FunctionPass*
FunctionPass *llvm::createZPUISelDag(ZPUTargetMachine &TM) {
  return new ZPUDAGToDAGISel(TM);
}
