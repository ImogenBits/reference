#include <stdio.h>

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
    "mov %0, %%rbp" \
    ::"m" (__newBase) \
); REM(

typedef struct {
    char memberVar;
    char arr[102];
} BigStruct;

void setArr(int a, int i, long __VARADDR){ \
    volatile BigStruct passedStruct;
    char __FUNCSPACER[FUNCSPACERSIZE];
    nop();
    long __rbp;
    asm(
        "mov %%rbp, %0"
        :"=m" (__rbp)
    ); 
    char *__argStart = (char *) &passedStruct + sizeof(BigStruct);
    long __argSize = __rbp -((long) __argStart);
    long __newBase = __VARADDR + __argSize; 
    printf("%lu\n", __argSize);
    printf("%lu, %lu\n", __rbp, __newBase);
    for (long i = 0; i < __argSize; i++) {
        *(char *)(__VARADDR + i) = *(char *)(__argStart + i); 
        printf("%lu, %lu: %u\n",__argStart + i,  __VARADDR + i, *(char *)(__argStart + i));
    }
    asm( 
        "mov %0, %%rbp" 
        ::"m" (__newBase) 
    ); 
    passedStruct.memberVar = a;
    passedStruct.arr[10] = 20;
}


int main() {
    int a = 0;
    MakeRef(BigStruct, myStruct) = {0};
    int i = 0;

    printf("memberVar:\n");
    a = 10; //scanf("%d", &a);
    printf("index:\n");
    i = 10; // scanf("%d", &i);

    setArr(a, i, PassRef(myStruct));


    printf("memberVar: %d\n", myStruct.memberVar);
    printf("arr[%d]: %d\n", i,  myStruct.arr[i]);
}