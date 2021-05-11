namespace eval polyglot {
    namespace export printFromTCL

    proc printFromTCL {} {
        return "Hello from TCL"
    }
}

proc main {} {
    puts [polyglot::printFromTCL]
}

lappend auto_path /opt/tclquadcode
package require tclquadcode

LLVM optimise polyglot::*
LLVM optimise main
main
