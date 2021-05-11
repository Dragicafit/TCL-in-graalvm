lappend auto_path /opt/tclquadcode

package require tclquadcode

proc main {} {
    puts "Hello from TCL"
}
LLVM configure

LLVM optimise main

#puts [LLVM pre]

puts [LLVM post]
