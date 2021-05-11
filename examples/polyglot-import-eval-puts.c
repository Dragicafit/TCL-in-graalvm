#include <tcl.h>

#include <stdio.h>
#include <graalvm/llvm/polyglot.h>

struct PolyglotEvalPutMemberPuts {
    char* (*printFromJAVA)();
};

POLYGLOT_DECLARE_STRUCT(PolyglotEvalPutMemberPuts);

static struct PolyglotEvalPutMemberPuts* polyglotEvalPutMemberPuts;

static int printFromTCL(void *dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
    if (objc != 1) {
        Tcl_WrongNumArgs(interp, 1, objv, "");
        return TCL_ERROR;
    }

    char buffer[100];
    polyglot_as_string(polyglotEvalPutMemberPuts->printFromJAVA(), buffer, sizeof(buffer), "ascii");
    printf("%s\n", buffer);
    
    Tcl_SetObjResult(interp, Tcl_NewStringObj("Hello from C called by TCL", -1));

    return TCL_OK;
}

int main(int argc, const char *argv[]) {
    polyglotEvalPutMemberPuts = polyglot_as_PolyglotEvalPutMemberPuts(polyglot_import("polyglotEvalPutMemberPuts"));

    int code;

    Tcl_FindExecutable(argv[0]);
    Tcl_Interp *interp = Tcl_CreateInterp();
    Tcl_Init(interp);

    Tcl_CreateObjCommand(interp, "polyglot::printFromTCL", printFromTCL, NULL, NULL);

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
