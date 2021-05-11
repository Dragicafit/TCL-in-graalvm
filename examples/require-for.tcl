lappend auto_path [file dirname [info script]]

package require POLYGLOT_C

proc main {} {
    for {set i 0} {$i < NB_ITERATIONS} {incr i} {
        polyglot::increment
    }
    puts [polyglot::getVal]
}

main
