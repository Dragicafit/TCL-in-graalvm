#include <tcl.h>

#include <stdio.h>

static int printFromTCL(void *dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
    if (objc != 1) {
        Tcl_WrongNumArgs(interp, 1, objv, "");
        return TCL_ERROR;
    }
    printf("Hello from TCL\n");
    Tcl_SetObjResult(interp, Tcl_NewStringObj("Hello from C called by TCL", -1));

    return TCL_OK;
}

DLLEXPORT int Export_puts_Init(Tcl_Interp *interp)	{
    int code;

    Tcl_Init(interp);

    Tcl_CreateObjCommand(interp, "polyglot::printFromTCL", printFromTCL, NULL, NULL);

    return Tcl_PkgProvide(interp, POLYGLOT_C, "1.0");
}
