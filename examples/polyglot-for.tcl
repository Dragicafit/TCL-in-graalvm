proc main {} {
    for {set i 0} {$i < NB_ITERATIONS} {incr i} {
        polyglot::increment
    }
    puts [polyglot::getVal]
}

main
