lappend auto_path [file dirname [info script]]

package require POLYGLOT_C

proc main {} {
    puts [polyglot::printFromTCL]
}

main
