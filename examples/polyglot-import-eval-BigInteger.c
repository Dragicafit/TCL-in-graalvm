#include <tcl.h>

#include <stdio.h>
#include <graalvm/llvm/polyglot.h>
#include <tclTomMath.h>

struct BigInteger {
    struct BigInteger *(*pow)(int);
    char *(*toByteArray)();
    void *(*toString)();
};

struct BigInteger_class {
};

struct PolyglotEvalPutMemberBigInteger {
    struct BigInteger* (*passBigInteger)(struct BigInteger*);
};

POLYGLOT_DECLARE_STRUCT(PolyglotEvalPutMemberBigInteger);
POLYGLOT_DECLARE_STRUCT(BigInteger_class);

struct PolyglotEvalPutMemberBigInteger* polyglotEvalPutMemberBigInteger;
struct BigInteger_class* BigIntegerClass;
void* arrayType;

static int passBigInteger(void *dummy, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]) {
    if (objc != 2) {
        return TCL_ERROR;
    }
    mp_int bigNum;
    Tcl_GetBignumFromObj(interp, objv[1], &bigNum);
    unsigned char buf[100];
    size_t written;
    mp_to_ubin(&bigNum, buf, 100, &written);
    void *array = polyglot_new_instance(arrayType, written);
    for (int i = 0; i<written; i++){
        polyglot_set_array_element(array, i, (char)buf[i]);
    }
    struct BigInteger* in = polyglot_new_instance(BigIntegerClass, array);
    polyglotEvalPutMemberBigInteger->passBigInteger(in);

    Tcl_SetObjResult(interp, Tcl_NewStringObj("//TODO BigInteger", -1));

    return TCL_OK;
}

int main(int argc, char *argv[]) {
    BigIntegerClass = polyglot_as_BigInteger_class(polyglot_java_type("java.math.BigInteger"));
    arrayType = polyglot_java_type("byte[]");
    polyglotEvalPutMemberBigInteger = polyglot_as_PolyglotEvalPutMemberBigInteger(polyglot_import("polyglotEvalPutMemberBigInteger"));

    int code;

    Tcl_FindExecutable(argv[0]);
    Tcl_Interp *interp = Tcl_CreateInterp();
    Tcl_Init(interp);

    Tcl_CreateObjCommand(interp, "polyglot::passBigInteger", passBigInteger, NULL, NULL);
    
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
