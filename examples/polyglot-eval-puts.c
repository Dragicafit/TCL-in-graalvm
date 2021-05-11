#include <tcl.h>

#include <stdio.h>

int main(int argc, const char *argv[]) {
    int code;

    Tcl_FindExecutable(argv[0]);
	Tcl_Interp * interp = Tcl_CreateInterp();
    Tcl_Init(interp);

    code = Tcl_EvalFile(interp, POLYGLOT_TCL);
    if (code == TCL_ERROR) {
        Tcl_Channel chan = Tcl_GetStdChannel(TCL_STDERR);
        if (chan) {
            Tcl_WriteObj(chan, Tcl_GetObjResult(interp));
            Tcl_WriteChars(chan, "\n", 1);
        }
    }

    Tcl_DeleteInterp(interp);

    return 0;
}
