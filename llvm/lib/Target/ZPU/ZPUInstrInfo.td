/// brief: ZPUInstrInfo.td文件用于描述指令

/// 定义抽象记录RV32, 用于定义32-bit指令的公共字段或者值;
/// 字段Size表示指令编码占用字节数;
/// 字段Inst表示指令二进制编码
class RV32 : Instruction {
  let Size = 4;
  let Namespace = "ZPU";
  bits<32> Inst;
}

/// 定义SDNode节点ZPURetFlag, 其操作码为枚举值ZPUISD::RET_FLAG,
/// 定义在ZPUISelLowering.h文件中, 在指令选择过程中用到
def ZPURetFlag : SDNode<"ZPUISD::RET_FLAG", SDTNone,
                            [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

/// 定义12bit的有符号立即数, 数据类型为i32
def simm12 : Operand<i32>, ImmLeaf<i32, [{return isInt<12>(Imm);}]>;

/// 定义具体指令ADDI, 用于表示addi指令
/// 字段OutOperandList表示指令的输出, (outs GPR:$rd)表示指令的输出是要给寄存器类GPR中的寄存器,
///                                即用$rd存放addi指令的运算结果,
///                                需要定义同名字段即"bits<5> rd",
///                                "let Inst{11-7} = rd", 表示该寄存器在指令编码中占用低位7~11bit
/// 字段InOperandList表示指令的输入, (ins GPR:$rs1, simm12:$imm12)
///                               表示指令的第1个操作数是寄存器类GPR中的寄存器(用$rs1表示),
///                               第2个操作数是类型为simm12的立即数(用$imm12表示),
///                               需要定义同名字段"bits<5> rs1"
///                               "let Inst{19-15} = rs1"表示该寄存器在指令编码中占用高位15~19bit
/// 字段AsmString表示指令的汇编代码格式, 如"addi $rd, $rs1, $imm12"
/// 字段Pattern表示指令的匹配模式, [(set GPR:$rd, (add GPR:$rs1, simm12:$imm12))]
///                             表示如果SDNode节点位add(对应的操作码位ISD::ADD),
///                             运算结果和第1个操作数都为GPR中的寄存器,
///                             第2个操作数位simm12类型的立即数
/// Inst表示指令编码中, 各个位应该填写的值
def ADDI : RV32 {
  let OutOperandList = (outs GPR:$rd);
  let InOperandList = (ins GPR:$rs1, simm12:$imm12);
  let AsmString = "addi $rd, $rs1, $imm12";
  let Pattern = [(set GPR:$rd, (add GPR:$rs1, simm12:$imm12))];
  bits<5> rd;
  bits<5> rs1;
  bits<12> imm12;
  let Inst{31-20} = imm12;
  let Inst{19-15} = rs1;
  let Inst{14-12} = 0b000;
  let Inst{11-7} = rd;
  let Inst{6-0} = 0b0010011;
}


/// 定义JALR指令
/// 字段"isCall"的值位1表示该指令用于函数调用
def JALR : RV32 {
  let OutOperandList = (outs GPR:$rd);
  let InOperandList = (ins GPR:$rs1, simm12:$imm12);
  let AsmString = "jalr $rd, ${imm12}(${rs1})";
  bits<5> rd;
  bits<5> rs1;
  bits<12> imm12;
  let Inst{31-20} = imm12;
  let Inst{19-15} = rs1;
  let Inst{14-12} = 0b000;
  let Inst{11-7} = rd;
  let Inst{6-0} = 0b1101111;
  let isCall = 1;
}

/// 定义汇编代码的"jalr x0, 0(x1)"的别名为"ret", 并且优先打印该别名
/// 抽象记录InstAlias的第3个参数表示优先级, 默认是1
def : InstAlias<"ret", (JALR X0, X1, 0), 4>;

/// 定义伪指令PseudoRET
/// PseudoInstExpansion<(JALR X0, X1, 0)表示伪指令PseudoRET实际对应的指令为JALR X0, X1, 0
/// let Pattern = [(ZPURetFlag)];表示SDNode节点为ZPURetFlag时会匹配到该伪指令
/// let isPseudo = 1;表示该指令是伪指令。
/// let isReturn = 1;表示该指令会导致从函数返回
/// let isTerminator = 1;表示该指令必须作为基本块的最后一条指令。
def PseudoRET : RV32, PseudoInstExpansion<(JALR X0, X1, 0)> {
  let OutOperandList = (outs);
  let InOperandList = (ins);
  let Pattern = [(ZPURetFlag)];
  let isPseudo = 1;
  let isReturn = 1;
  let isTerminator = 1;
}