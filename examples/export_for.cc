#include <cpptcl/cpptcl.h>

#include <iostream>
#include <string>

using namespace std;
using namespace Tcl;

static int val = 0;

static void increment() {
    val++;
}

static int getVal() {
    return val;
}

CPPTCL_MODULE(Export_for, i) {
    i.def("polyglot::increment", increment);
    i.def("polyglot::getVal", getVal);
    
    i.pkg_provide(POLYGLOT_C, "1.0");
}
