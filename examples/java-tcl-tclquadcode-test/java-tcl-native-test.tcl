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
    for {set i 0} {$i < 1000000} {incr i} {
        polyglot::increment
    }
    puts [polyglot::getVal]
}

lappend auto_path /opt/tclquadcode
package require tclquadcode

puts "BEFORE COMPILATION, using Tcl [package require Tcl]"
puts [time {main} 1]

LLVM optimise polyglot::* main

puts "AFTER COMPILATION"
puts [time {main} 1]
