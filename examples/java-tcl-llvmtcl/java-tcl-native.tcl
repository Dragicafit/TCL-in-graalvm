package require llvmtcl
package require graalvm/llvm/polyglot

oo::class create PrintFromJAVA {
    method printFromJAVA {} {
    }
}

proc polyglot_as_PrintFromJAVA {a} {
}

proc polyglot_import {a} {
}

# POLYGLOT_DECLARE_STRUCT(PrintFromJAVA)

proc main {} {
    puts "Hello from TCL"

    #set printFromJAVA [polyglot_as_PrintFromJAVA [polyglot_import "printFromJAVA"]]
    #$printFromJAVA printFromJAVA

    return 0
}

puts [tcl::unsupported::disassemble proc "main"]

llvmtcl LinkInMCJIT
llvmtcl InitializeNativeTarget
set m [llvmtcl ModuleCreateWithName "test.tcl"]

set f [llvmtcl Tcl2LLVM $m "main"]
lassign [llvmtcl VerifyModule $m LLVMReturnStatusAction] rt msg
if {$rt} { error $msg }

llvmtcl Optimize $m [list $f]

#declare !dbg !13 dso_local i8* @polyglot_import(i8*) local_unnamed_addr #1
set ft [llvmtcl FunctionType [llvmtcl PointerType [llvmtcl Int8Type] 0] [list [llvmtcl PointerType [llvmtcl Int8Type] 0]] 0]
llvmtcl AddFunction $m "polyglot_import" $ft

#declare !dbg !20 dso_local i8* @polyglot_as_typed(i8*, %struct.__polyglot_typeid*) local_unnamed_addr #1
set ft [llvmtcl FunctionType [llvmtcl PointerType [llvmtcl Int8Type] 0] [list [llvmtcl PointerType [llvmtcl Int8Type] 0]] 0]
llvmtcl AddFunction $m "polyglot_as_typed" $ft

#declare dso_local %struct.__polyglot_typeid* @__polyglot_as_typeid(i8*) local_unnamed_addr #1
set ft [llvmtcl StructType [list [llvmtcl Int8Type]] 0]
llvmtcl AddFunction $m "__polyglot_typeid" $ft

#declare void @llvm.dbg.value(metadata, metadata, metadata) #2
set ft [llvmtcl FunctionType [llvmtcl VoidType] [list [llvmtcl Int8Type]] 0]
llvmtcl AddFunction $m "llvm.dbg.value" $ft

#declare i32 @puts(i8* nocapture readonly)
set ft [llvmtcl FunctionType [llvmtcl Int32Type] [list [llvmtcl PointerType [llvmtcl Int8Type] 0]] 0]
llvmtcl AddFunction $m "puts" $ft




puts [llvmtcl DumpModule $m]

llvmtcl DisposeModule $m