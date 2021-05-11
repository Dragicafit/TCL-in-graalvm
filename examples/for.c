#include <stdio.h>

static int val = 0;
    
static void increment() {
        val++;
}

static void getVal() {
    printf("val: %d\n", val);
}

int main() {
    for (int i = 0; i < NB_ITERATIONS; i++) {
        increment();
    }
    getVal();

    return 0;
}
