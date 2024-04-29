/// TODO

#ifndef LLVM_LIB_TARGET_ZPU_ZPUISELLOWERING_H
#define LLVM_LIB_TARGET_ZPU_ZPUISELLOWERING_H

#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {
class ZPUSubtarget;
class ZPUTargetMachine;

namespace ZPUISD {

/// @brief: 指令ZPU自定义的NodeType(由ISD::NodeType拓展而来)
enum NodeType {
  /// 从ISD::NodeType枚举的最后一个值开始拓展
  FIRST_NUMBER = ISD::BUILTIN_OP_END,

  /// 定义目标后端ZPU特有的操作码(ZPUISD::RET_FLAG), 这意味着,
  /// 在选择机器指令(即pre-isel阶段),
  /// 之前SDNode节点的操作码可以是ZPUISD::RET_FLAG;
  /// 需要注意的是, 这些特定目标的操作码应该大于"ISD::BUILTIN_OP_END"
  RET_FLAG,
};

} // namespace ZPUISD

/// TODO
class ZPUTargetLowering : public TargetLowering {
  const ZPUSubtarget &Subtarget;

public:
  explicit ZPUTargetLowering(ZPUTargetMachine &TM);

  /// @brief: 返回特定于目标的SDNode节点的名称
  /// @param Opcode
  /// @return const char*
  const char *getTargetNodeName(unsigned Opcode) const override;

  /// @brief: 将函数参数转换为何种SDNode节点
  /// @param Chain
  /// @param CallConv
  /// @param IsVarArg
  /// @param Ins
  /// @param DL
  /// @param DAG
  /// @param InVals
  /// @return SDValue
  SDValue LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv,
                               bool IsVarArg,
                               const SmallVectorImpl<ISD::InputArg> &Ins,
                               const SDLoc &DL, SelectionDAG &DAG,
                               SmallVectorImpl<SDValue> &InVals) const override;

  /// @brief: 将函数返回值转换为何种SDNode节点
  /// @param Chain
  /// @param CallConv
  /// @param IsVarArg
  /// @param
  /// @param Ins
  /// @param DL
  /// @param DAG
  /// @param InVals
  /// @return
  virtual SDValue LowerReturn(SDValue Chain, CallingConv::ID CallConv,
                              bool isVarArg,
                              const SmallVectorImpl<ISD::OutputArg> &Outs,
                              const SmallVectorImpl<SDValue> &OutVals,
                              const SDLoc &DL,
                              SelectionDAG &DAG) const override;
};
} // namespace llvm
#endif
