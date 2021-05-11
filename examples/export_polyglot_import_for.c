#include <tcl.h>

#include <stdio.h>
#include <graalvm/llvm/polyglot.h>

struct PolyglotEvalPutMemberFor {
    void (*increment)();
    int (*getVal)();
};

POLYGLOT_DECLARE_STRUCT(PolyglotEvalPutMemberFor);

static struct PolyglotEvalPutMemberFor* polyglotEvalPutMemberFor;

static int increment(void *dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
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

DLLEXPORT int Export_polyglot_import_for_Init(Tcl_Interp *interp)	{
    polyglotEvalPutMemberFor = polyglot_as_PolyglotEvalPutMemberFor(polyglot_import("polyglotEvalPutMemberFor"));

    int code;

    Tcl_Init(interp);

    Tcl_CreateObjCommand(interp, "polyglot::increment", increment, NULL, NULL);
    Tcl_CreateObjCommand(interp, "polyglot::getVal", getVal, NULL, NULL);
    
    return Tcl_PkgProvide(interp, POLYGLOT_C, "1.0");
}
