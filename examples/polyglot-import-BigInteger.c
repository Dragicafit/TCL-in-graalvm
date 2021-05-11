#include <stdio.h>
#include <graalvm/llvm/polyglot.h>

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

int main() {
    struct BigInteger_class* BigIntegerClass = polyglot_as_BigInteger_class(polyglot_java_type("java.math.BigInteger"));
    struct PolyglotEvalPutMemberBigInteger* polyglotEvalPutMemberBigInteger = polyglot_as_PolyglotEvalPutMemberBigInteger(polyglot_import("polyglotEvalPutMemberBigInteger"));

    void * val = polyglot_from_string("1200000000000000000000000000000000000000000001", "ascii");
    struct BigInteger* in = polyglot_new_instance(BigIntegerClass, val);

    struct BigInteger* out = polyglotEvalPutMemberBigInteger->passBigInteger(in);

    char buffer[100];
    int bytes = polyglot_as_string(out->toString(), buffer, sizeof(buffer), "ascii");

    printf("BigInteger in C: %s\n", buffer);

    return 0;
}
