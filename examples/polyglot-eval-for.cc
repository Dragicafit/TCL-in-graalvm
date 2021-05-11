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

int main() {
    int code;

	Tcl_Interp * interp = Tcl_CreateInterp();
	interpreter i(interp, true);

    i.def("polyglot::increment", increment);
    i.def("polyglot::getVal", getVal);

    code = Tcl_EvalFile(interp, POLYGLOT_TCL);
    if (code == TCL_ERROR) {
        Tcl_Channel chan = Tcl_GetStdChannel(TCL_STDERR);
        if (chan) {
            Tcl_WriteObj(chan, Tcl_GetObjResult(interp));
            Tcl_WriteChars(chan, "\n", 1);
        }
    }

    return 0;
}
