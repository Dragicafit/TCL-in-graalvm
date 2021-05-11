#include <tcl.h>

#include <stdio.h>
#include <graalvm/llvm/polyglot.h>

struct PolyglotEvalPutMemberFor {
    void (*increment)();
    int (*getVal)();
};

POLYGLOT_DECLARE_STRUCT(PolyglotEvalPutMemberFor);

static struct PolyglotEvalPutMemberFor* polyglotEvalPutMemberFor;

static int increment(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
    if (objc != 1) {
        Tcl_WrongNumArgs(interp, 1, objv, "");
        return TCL_ERROR;
    }
    polyglotEvalPutMemberFor->increment();

    return TCL_OK;
}

static int getVal(void *dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
    if (objc != 1) {
        Tcl_WrongNumArgs(interp, 1, objv, "");
        return TCL_ERROR;
    }
    Tcl_SetObjResult(interp, Tcl_NewIntObj(polyglotEvalPutMemberFor->getVal()));

    return TCL_OK;
}

int main(int argc, const char *argv[]) {
    polyglotEvalPutMemberFor = polyglot_as_PolyglotEvalPutMemberFor(polyglot_import("polyglotEvalPutMemberFor"));

    int code;

    Tcl_FindExecutable(argv[0]);
    Tcl_Interp *interp = Tcl_CreateInterp();
    Tcl_Init(interp);

    Tcl_CreateObjCommand(interp, "polyglot::increment", increment, NULL, NULL);
    Tcl_CreateObjCommand(interp, "polyglot::getVal", getVal, NULL, NULL);

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
