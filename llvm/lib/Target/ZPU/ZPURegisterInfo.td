/// brief: ZPURegisterInfo.td文件用于描述寄存器和寄存器类
///        寄存器类是一组具有相同大小的寄存器集合; 同时也定义
///        寄存器分配的默认先后顺序

/// brief: 定义抽象记录ZPUReg, 便于定义后面的寄存器;
///        第1个参数表示寄存器的编码, 占5bit;
///        第2个参数表示寄存器的名称;
///        第3个参数表示寄存器的别名列表;
///        在LLVM中, 每个寄存器定义都会由TableGen生成唯一的标识符, 定义在ZPUGenRegisterInfo.inc中;
class ZPUReg<bits<5> enc, string name, list<string> alt = []>
    : Register<name, alt> {
  let HWEncoding{4-0} = enc;
  let Namespace = "ZPU";
}

/// 定义寄存器别名选择类型ABIRegAltName
def ABIRegAltName : RegAltNameIndex;

/// 定义X0 ~ X1寄存器
let RegAltNameIndices = [ABIRegAltName] in {
  def X0  : ZPUReg<0,  "x0",  ["zero"]>;
  def X1  : ZPUReg<1,  "x1",  ["ra"]>;
  def X2  : ZPUReg<2,  "x2",  ["sp"]>;
  def X3  : ZPUReg<3,  "x3",  ["gp"]>;
  def X4  : ZPUReg<4,  "x4",  ["tp"]>;
  def X5  : ZPUReg<5,  "x5",  ["t0"]>;
  def X6  : ZPUReg<6,  "x6",  ["t1"]>;
  def X7  : ZPUReg<7,  "x7",  ["t2"]>;
  def X8  : ZPUReg<8,  "x8",  ["s0", "fp"]>;
  def X9  : ZPUReg<9,  "x9",  ["s1"]>;
  def X10 : ZPUReg<10, "x10", ["a0"]>;
  def X11 : ZPUReg<11, "x11", ["a1"]>;
  def X12 : ZPUReg<12, "x12", ["a2"]>;
  def X13 : ZPUReg<13, "x13", ["a3"]>;
  def X14 : ZPUReg<14, "x14", ["a4"]>;
  def X15 : ZPUReg<15, "x15", ["a5"]>;
  def X16 : ZPUReg<16, "x16", ["a6"]>;
  def X17 : ZPUReg<17, "x17", ["a7"]>;
  def X18 : ZPUReg<18, "x18", ["s2"]>;
  def X19 : ZPUReg<19, "x19", ["s3"]>;
  def X20 : ZPUReg<20, "x20", ["s4"]>;
  def X21 : ZPUReg<21, "x21", ["s5"]>;
  def X22 : ZPUReg<22, "x22", ["s6"]>;
  def X23 : ZPUReg<23, "x23", ["s7"]>;
  def X24 : ZPUReg<24, "x24", ["s8"]>;
  def X25 : ZPUReg<25, "x25", ["s9"]>;
  def X26 : ZPUReg<26, "x26", ["s10"]>;
  def X27 : ZPUReg<27, "x27", ["s11"]>;
  def X28 : ZPUReg<28, "x28", ["t3"]>;
  def X29 : ZPUReg<29, "x29", ["t4"]>;
  def X30 : ZPUReg<30, "x30", ["t5"]>;
  def X31 : ZPUReg<31, "x31", ["t6"]>;
}

/// 定义32-bit通用寄存器GPR,
/// 第1个参数表示命名空间
/// 第2个参数表示该寄存器所支持的数据类型
/// 第3个参数表示对齐要求
/// 第4个参数表示包含哪些寄存器和默认的寄存器分配顺序,
/// 规则通常为: 由调用者保存的寄存器 -> 由被调用者保存的寄存器 -> 特殊寄存器
/// 如: 寄存器X10 ~ X17用于存放函数参数, 由调用者保存, 所以放在靠前位置,
/// 同时在寄存器分配时也会被优先分配
def GPR : RegisterClass<"ZPU", [i32], 32, (add
  (sequence "X%u", 10, 17),
  (sequence "X%u",  5,  7),
  (sequence "X%u", 28,  31),
  (sequence "X%u",  8,   9),
  (sequence "X%u", 18,  27),
  (sequence "X%u",  0,   4)
)>;