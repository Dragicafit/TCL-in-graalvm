proc main {} {
    for {set i 0} {$i < NB_ITERATIONS} {incr i} {
        polyglot::increment
    }
    puts [polyglot::getVal]
}

lappend auto_path /opt/tclquadcode
package require tclquadcode

puts "BEFORE COMPILATION, using Tcl [package require Tcl]"
puts [list main]\040=\040[main]
main

set t [time {LLVM optimise main}]
puts "COMPILATION TOOK [lrange $t 0 1]"

puts "AFTER COMPILATION"
puts [list main]\040=\040[main]
main
