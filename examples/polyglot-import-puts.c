#include <stdio.h>
#include <graalvm/llvm/polyglot.h>

struct PolyglotEvalPutMemberPuts {
    char* (*printFromJAVA)();
};

POLYGLOT_DECLARE_STRUCT(PolyglotEvalPutMemberPuts);

int main() {
    struct PolyglotEvalPutMemberPuts* polyglotEvalPutMemberPuts = polyglot_as_PolyglotEvalPutMemberPuts(polyglot_import("polyglotEvalPutMemberPuts"));

    char buffer[100];
    polyglot_as_string(polyglotEvalPutMemberPuts->printFromJAVA(), buffer, sizeof(buffer), "ascii");
    printf("%s\n", buffer);
    
    return 0;
}
