#include <stdio.h>
#include <graalvm/llvm/polyglot.h>

struct PolyglotEvalPutMemberFor {
    void (*increment)();
    int (*getVal)();
};

POLYGLOT_DECLARE_STRUCT(PolyglotEvalPutMemberFor);

int main() {
    struct PolyglotEvalPutMemberFor* polyglotEvalPutMemberFor = polyglot_as_PolyglotEvalPutMemberFor(polyglot_import("polyglotEvalPutMemberFor"));

    for (int i = 0; i < NB_ITERATIONS; i++) {
        polyglotEvalPutMemberFor->increment();
    }
    printf("val: %d\n", polyglotEvalPutMemberFor->getVal());
    
    return 0;
}
