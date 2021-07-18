#define SPACERSIZE 64
#define FUNCSPACERSIZE 200

#define MakeRef(type, var) \
long long __VARADDR; \
char __SPACER[SPACERSIZE];\
__VARADDR = (long) __SPACER; \
volatile type var

#define PassRef(var) __VARADDR

void nop(void) {}
#define REM()

#define ByRef(type, var) long __VARADDR){ \
volatile type var; \
char __FUNCSPACER[FUNCSPACERSIZE]; \
nop(); \
long __rbp; \
asm( \
    "mov %%rbp, %0" \
    :"=m" (__rbp) \
); \
char *__argStart = (char *) &var + sizeof(type); \
long __argSize = __rbp -((long) __argStart); \
long __newBase = __VARADDR + __argSize; \
for (long i = 0; i < __argSize; i++) \
    *(char *)(__VARADDR + i) = *(char *)(__argStart + i); \
asm( \
    "mov %0, %%rbp" \
    ::"m" (__newBase) \
); REM(