namespace eval polyglot {
    proc printFromTCL {} {
        return "Hello from TCL"
    }
}

proc main {} {
    puts [polyglot::printFromTCL]
}

main
