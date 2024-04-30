#include "MCTargetDesc/ZPUMCTargetDesc.h"
#include "ZPUISelLowering.h"
#include "ZPUSubtarget.h"
#include "ZPUTargetMachine.h"
#include "llvm/CodeGen/CallingConvLower.h"

using namespace llvm;

#include "ZPUGenCallingConv.inc"

ZPUTargetLowering::ZPUTargetLowering(ZPUTargetMachine &TM)
    : TargetLowering(TM), Subtarget(*TM.getSubtargetImpl()) {
  addRegisterClass(MVT::i32, &ZPU::GPRRegClass);
  computeRegisterProperties(Subtarget.getRegisterInfo());
}

/// @brief: 返回特定于目标的SDNode节点的名称
/// @param Opcode
/// @return const char*
/// @remark tags1: 目前只处理"RET_FLAG"
const char *ZPUTargetLowering::getTargetNodeName(unsigned Opcode) const {
  switch (Opcode) {
  case ZPUISD::RET_FLAG: {
    return "ZPUISD::RET_FLAG";
  }
  default: {
    return nullptr;
  }
  }
}

/// @brief: 将函数参数转换为何种SDNode节点
/// @param Chain
/// @param CallConv
/// @param IsVarArg
/// @param Ins
/// @param DL
/// @param DAG
/// @param InVals
/// @return SDValue
SDValue ZPUTargetLowering::LowerFormalArguments(
    SDValue Chain, CallingConv::ID CallConv, bool IsVarArg,
    const SmallVectorImpl<ISD::InputArg> &Ins, const SDLoc &DL,
    SelectionDAG &DAG, SmallVectorImpl<SDValue> &InVals) const {
  SmallVector<CCValAssign, 16> ArgLocs;

  MachineFunction &MF = DAG.getMachineFunction();

  CCState CCInfo(CallConv, IsVarArg, MF, ArgLocs, *DAG.getContext());

  /// 分析参数值数组, CC_ZPU是一个回调函数, 在"ZPUGenCallingConv.inc"中实现
  CCInfo.AnalyzeFormalArguments(Ins, CC_ZPU);

  for (unsigned i = 0, e = ArgLocs.size(); i < e; ++i) {
    CCValAssign &VA = ArgLocs[i];
  }

  return Chain;
}

/// @brief: 将函数返回值转换为操作码为"ZPU::RET_FLAG"的SDNode节点
/// @param Chain
/// @param CallConv
/// @param IsVarArg
/// @param Outs
/// @param OutVals
/// @param DL
/// @param DAG
/// @return SDValue
SDValue
ZPUTargetLowering::LowerReturn(SDValue Chain, CallingConv::ID CallConv,
                               bool IsVarArg,
                               const SmallVectorImpl<ISD::OutputArg> &Outs,
                               const SmallVectorImpl<SDValue> &OutVals,
                               const SDLoc &DL, SelectionDAG &DAG) const {
  SmallVector<CCValAssign, 16> RVLocs;

  CCState CCInfo(CallConv, IsVarArg, DAG.getMachineFunction(), RVLocs,
                 *DAG.getContext());

  SDValue Glue;
  SmallVector<SDValue, 4> RetOps(1, Chain);

  for (unsigned i = 0, e = RVLocs.size(); i < e; ++i) {
    CCValAssign &VA = RVLocs[i];
    assert(VA.isRegLoc() && "Can only return in registers!");

    Chain = DAG.getCopyToReg(Chain, DL, VA.getLocReg(), OutVals[i], Glue);
    Glue = Chain.getValue(1);
    RetOps.push_back(DAG.getRegister(VA.getLocReg(), VA.getLocVT()));
  }

  /// TODO
  /// 该节点的第1个操作数总是为chain-edge ?
  RetOps[0] = Chain;

  /// TODO
  /// 最后一个操作数可能是glue-edge
  if (Glue.getNode()) {
    RetOps.push_back(Glue);
  }

  return DAG.getNode(ZPUISD::RET_FLAG, DL, MVT::Other, RetOps);
}
