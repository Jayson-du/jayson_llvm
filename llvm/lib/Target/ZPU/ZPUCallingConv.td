/// brief: ZPUCallingConv.td文件用于描述程序调用约定

/// 定义具体记录RetCC_ZPU(对应ZPUGenCallingConv.inc文件中的, RetCC_ZPU()函数),
/// 用于描述函数返回值如何返回;
/// CCIfType<[i1, i8, i16, i32], CCAssignToReg<[X10, X11]>>
/// 表示返回值的数据类型为i1, i8, i16, i32, 那么可以保存到寄存器"X10"或者"X11"中;
/// CCIfType<[i32], CCAssignToStack<4, 4>>, 表示返回值需要保存到栈内存中,
/// 存放规则为每个值占4字节, 并以4字节对齐
def RetCC_ZPU : CallingConv<[
  CCIfType<[i1, i8, i16, i32], CCAssignToReg<[X10, X11]>>,
  CCIfType<[i32], CCAssignToStack<4, 4>>,
]>;

/// 定义具体记录CC_ZPU(对应ZPUGenCallingConv.inc文件中的CC_ZPU()函数),
/// 用于描述函数参数如何传递
/// CCIfType<[i1, i8, i16, i32], CCAssignToReg<[X10, X11, X12, X13, X14, X15, X16, X17]>>,
/// 表示如果函数的参数是i1, i8, i16, i32, 那么可以将函数参数保存到寄存器"X10~X17"中;
/// CCIfType<[i32], CCAssignToStack<4, 4>>, 表示函数参数需要保存到栈中时, 存放规则为
/// 每个值占4字节, 并以4字节对齐
def CC_ZPU : CallingConv<[
  CCIfType<[i1, i8, i16, i32], CCAssignToReg<[X10, X11, X12, X13, X14, X15, X16, X17]>>,
  CCIfType<[i32], CCAssignToStack<4, 4>>,
]>;

/// 定义具体记录CC_Save(对应ZPUGenRegisterInfo.inc文件中CC_Save_SaveList[]数组), 用于描述被调用者保存的寄存器, 包括X2, X8, X9和X18 ~ X27;
def CC_Save : CalleeSavedRegs<(add X2, X8, X9, (sequence "X%u", 18, 27))>;