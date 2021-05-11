namespace eval polyglot {
    namespace export printFromTCL

    proc printFromTCL {} {
        return "Hello from TCL"
    }
}

proc main {} {
    puts [polyglot::printFromTCL]
}

main
