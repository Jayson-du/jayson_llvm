/// brief: ZPU.td文件用于描述目标属性, 如支持的指令集, 处理器等,
///        同时也作为主文件包含其他td文件

/// 包含InstrInfo, Target等官方提供的抽象记录
include "llvm/Target/Target.td"

/// 包含自定义的寄存器描述
include "ZPURegisterInfo.td"

/// 包含自定义的指令描述
include "ZPUInstrInfo.td"

/// 包含自定义的调用约定
include "ZPUCallingConv.td"

/// 定义支持的处理器类型,
/// 第1个参数表示处理器名称
/// 第2个参数表示处理的调度模型
def : PRoecessorModel<"generic-zpu", NoSchedModel, []>;

/// 定义指令的全局属性, 每个目标后端都必须实例化抽象记录InstrInfo
def ZPUInstrInfo : InstrInfo;

/// 定义目标全局属性, 每个目标后端都必须实例化抽象记录Target
def ZPU : Target {
  let InstructionSet = ZPUInstrInfo;
}