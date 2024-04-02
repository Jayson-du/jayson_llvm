/// brief: Schedule文件主要描述

/// FuncUnit定义(TargetItinerary.td)
//// class FuncUnit;

/// 定义两条管线
def ALU       : FuncUnit;
def IMULDIV   : FuncUnit;

/// InstrItinClass定义
/// class InstrItinClass;

/// ARM与Mips使用"InstrItinClass"表示指令调度类型
/// class InstrItinClass;
def IIAlu     : InstrItinClass;
def II_CLO    : InstrItinClass;
def II_CLZ    : InstrItinClass;