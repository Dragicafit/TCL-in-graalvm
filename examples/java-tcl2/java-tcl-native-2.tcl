lappend auto_path /opt/tclquadcode
package require tclquadcode

set m [LLVM::Module new abc]
$m debug file [info script]

set thunkBuilder [LLVM::ThunkBuilder new $m]
set t [LLVM::Type func{DOUBLE<-DOUBLE}]
set f [$m function.create abc $t]
$f setAsCurrentDebuggingScope
set fref [$f ref]
set b [$m builder]
$b @end [$f block]
$b @location [dict get [info frame 0] line]
$b ret [$b add(DOUBLE,DOUBLE) [$f param 0] [$f param 0]]
$thunkBuilder thunk abc {
signature {DOUBLE DOUBLE}
argumentDefaults {{x 0 0.0}}
}
set f [$thunkBuilder finalize]
$m optimize
$m verify
llvmtcl PrintValueToString $fref

$m dispose