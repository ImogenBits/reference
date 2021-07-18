#pragma clang diagnostic ignored "-Wreturn-type"

#define SPACERSIZE 200

#define RefTo (long) &

#define REM()
#define PASTE_HELPER(a,b) a ## b
#define PASTE(a,b) PASTE_HELPER(a,b)
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

typedef struct {
    char a[SPACERSIZE];
} bigStruct;

#define by_ref(type, varName) long var){ \
    long newrsp = var - SPACERSIZE; \
    asm( \
        "mov %%rsp, %%r12 \n\t" \
        "mov %0, %%rsp \n\t" \
        "call FUNC" TOSTRING(__LINE__) "\n\t" \
        "mov %%r12, %%rsp" \
        :: "m" (newrsp) \
    ); \
} \
int PASTE(FUNC, __LINE__) (bigStruct FUNCSPACER, type varName) REM(