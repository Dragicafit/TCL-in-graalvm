namespace eval polyglot {
    variable val 0
    namespace export increment getVal

    proc increment {} {
        variable val
        incr val
    }

    proc getVal {} {
        variable val
        return $val
    }
}

proc main {} {
    for {set i 0} {$i < NB_ITERATIONS} {incr i} {
        polyglot::increment
    }
    puts [polyglot::getVal]
}

lappend auto_path /opt/tclquadcode
package require tclquadcode

LLVM optimise polyglot::*
LLVM optimise main
main
