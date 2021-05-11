namespace eval polyglot {
    set val 0

    proc increment {} {
        incr polyglot::val
    }

    proc getVal {} {
        return $polyglot::val
    }
}

proc main {} {
    for {set i 0} {$i < NB_ITERATIONS} {incr i} {
        polyglot::increment
    }
    puts [polyglot::getVal]
}

main
