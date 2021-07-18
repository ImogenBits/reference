//#include <stdio.h>

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
#define PASTE_HELPER(a,b) a ## b
#define PASTE(a,b) PASTE_HELPER(a,b)
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define Ref(type, var) long __VARADDR){ \
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
        "mov %0, %%rbp \n\t" \
        "call FUNC" TOSTRING(__LINE__) \
        ::"m" (__newBase) \
    ); \
} \
int PASTE(FUNC, __LINE__) (type var) REM(




typedef struct {
    int firstVar;
    double secondVar;
    char thirdVar;
} myStruct;

void modifyStruct(long __VARADDR){ \
    volatile myStruct byRef; \
    char __FUNCSPACER[FUNCSPACERSIZE]; \
    nop(); \
    long __rbp; \
    asm( \
        "mov %%rbp, %0" \
        :"=m" (__rbp) \
    ); \
    char *__argStart = (char *) &byRef + sizeof(myStruct); \
    long __argSize = __rbp -((long) __argStart); \
    long __newBase = __VARADDR + __argSize; \
    for (long i = 0; i < __argSize; i++) \
        *(char *)(__VARADDR + i) = *(char *)(__argStart + i); \
    asm( \
        "mov %0, %%rbp" \
        ::"m" (__newBase) \
    ); \
    for (long i = 0; i > -16; i--) \
        *(char *)(__VARADDR + SPACERSIZE + i) = *(char *)(__argStart + i); \
     \
    asm( \
        "call FUNC" TOSTRING(__LINE__) \
    ); \
} \
int PASTE(FUNC, __LINE__) (myStruct byRef) REM() {
    byRef.firstVar = 20;
    byRef.secondVar = 20.5;
    byRef.thirdVar = 'y';
}



int main() {
    myStruct firstStruct = {1, 2, 'a'};
    MakeRef(myStruct, secondStruct) = {3, 4, 'b'};
    //printf("firstStruct: {%d, %f}\n", firstStruct.firstVar, firstStruct.secondVar);
    //printf("secondStruct: {%d, %f}\n", secondStruct.firstVar, secondStruct.secondVar);

    //printf("modifyStructs()\n");
    modifyStruct(PassRef(secondStruct));


    //printf("firstStruct: {%d, %f, %s}\n", firstStruct.firstVar, firstStruct.secondVar, firstStruct.thirdVar);
    //printf("secondStruct: {%d, %f, %s}\n", secondStruct.firstVar, secondStruct.secondVar, firstStruct.thirdVar);
}