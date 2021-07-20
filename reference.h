#pragma clang diagnostic ignored "-Wreturn-type"

#include <string.h>

#define SPACERSIZE 200

#define REM()
#define PASTE_HELPER(a,b) a ## b
#define PASTE(a,b) PASTE_HELPER(a,b)
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

typedef struct {
    char a[SPACERSIZE];
} bigStruct;

#define by_ref(type, varName) type var){ \
    long addr = 0; \
    for (int i = 1; i < SPACERSIZE; i++) { \
        if (!memcmp(&var, (char *) &var + i, sizeof(type))) {\
            addr = (long) &var + i; \
        } \
    } \
    if (!addr) \
        return; \
    long rsp; \
    addr -= SPACERSIZE; \
    asm( \
        "mov %%rsp, %0 \n\t" \
        "mov %1, %%rsp \n\t" \
        "call FUNC" TOSTRING(__LINE__) "\n\t" \
        "mov %0, %%rsp" \
        :"=m" (rsp) \
        : "m" (addr) \
    ); \
} \
int PASTE(FUNC, __LINE__) (bigStruct FUNCSPACER, type varName) REM(