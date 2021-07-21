/*
The trick behind this is to trick the compiler into using the same piece of
memory for the original struct and the copy the function accesses.
Usually the stack would look like this:

|--------------|
|   compiler   | \
|     info     | |
|--------------| |
| firstStruct  |  > stack frame of main()
|--------------| |
| secondStruct | /
|--------------|
|    byRef     | \
|--------------|  > stack frame of modifyStructByRef()
|   compiler   | |
|     info     | /
|--------------|

we can't make the compiler change anything about that, but what we can do is
make it think the bottom of the stack is at a different spot than it actually is.
this helps us because it figues out the position of byRef from that place, so if
we make it think the bottom of the stack is at the bottom of firstStruct it will
think that byRef is at the place where firstStruct actually is. It'd then look
like this:

|--------------|
|   compiler   | \
|     info     | |
|--------------| |
|    byRef     |  > stack frame of main()
|--------------|  |
|   compiler   | /
|     info     |
|--------------|


as you can see not only does byRef overlap firstStruct, now the compiler info
will also overwrite secondStruct. to avoid this we also need to insert a dummy
variable that we won't ever write to and overlaps variables in main() that
follow the passed argument.

Then the compiler will think the stack looks like this:

|--------------|
|   compiler   | \
|     info     | |
|--------------| |
| firstStruct  |  > stack frame of main()
|--------------| |
| secondStruct | /
|--------------|
|    byRef     | \
|--------------| |
|              | |
|              | |
|              | |
|              | |
|    spacer    | |
|   variable   | |
|              |  > stack frame of modifyStructByRef()
|              | |
|              | |
|              | |
|              | |
|--------------| |
|   compiler   | |
|     info     | /
|--------------|

when it really looks like this:

|--------------|
|   compiler   |   \
|     info     |   |
|--------------|   |
| firstStruct  | \ |
|     and      | | |
|    byRef     | |  > stack frame of main()
|--------------| | |
| secondStruct | | |
|     and      | | |
|    spacer    | | /
|--------------| |
|              | |
|    spacer    | |
|   variable   | |
|              |  > stack frame of modifyStructByRef()
|              | |
|              | |
|              | |
|--------------| |
|   compiler   | |
|     info     | /
|--------------|

so now we know the idea behind this we need to figure out how to make clang
actually do this in a way that still looks like a normal C program. luckily C
lets us put assembly right into our code, so we are free to do things no one
should ever do, like make the computer think the bottom of the stack is at a
different place!
so we need to add some code that will get executed before the function we want
to modify. but in order to make this look as close to normal passing by reference
syntax as possible we can only make a macro around the variable in the function
head, so we can't just add some code to the start of the function. the way the
code will look is something like this:

void someFunc( OUR_MACRO(argType, argName)) {
    functionBody;
}

the trick is to now make our macro expand to some code that first closes the
function head, then has its own function body, and then a new function head that
will get the original function body as its body. like this:

void someFunc(               //this is in the original code

    ARG_LIST_FROM_MACRO) {   //this gets expanded from the macro
        NEW_FUNCTION_BODY
    }
    FUNCTION_HEAD(ARG_LIST
    
) {                          //here the original code starts again
    functionBody;
}

in the new function we add the code that messes with the stack and then call
the original function. that way we effectively added our code to the start
without needing to add code inside the function body.
*/




// you really shouldn't call a function from a place you haven
#pragma clang diagnostic ignored "-Wreturn-type"


#include <string.h>

#define SPACERSIZE 200

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
int PASTE(FUNC, __LINE__) (bigStruct FUNCSPACER, type varName




#include <stdio.h>
#include <reference.h>


typedef struct {
    int first;
    double second;
    char third;
} myStruct;

void modifyStructByVal(myStruct byVal) {
    byVal.first = 10;
    byVal.second = 3.1415;
    byVal.third = 'y';
}

void modifyStructByRef(by_ref(myStruct, byRef)) {
    byRef.first = 10;
    byRef.second = 3.1415;
    byRef.third = 'y';
}

int main() {
    myStruct firstStruct = {1, 2, 'a'};
    myStruct secondStruct = {3, 4, 'b'};
    printf("firstStruct: {%d, %f, %c}\n", firstStruct.first, firstStruct.second, firstStruct.third);
    printf("secondStruct: {%d, %f, %c}\n", secondStruct.first, secondStruct.second, secondStruct.third);

    printf("modify structs\n");
    modifyStructByRef(firstStruct);
    modifyStructByVal(secondStruct);

    printf("firstStruct: {%d, %f, %c}\n", firstStruct.first, firstStruct.second, firstStruct.third);
    printf("secondStruct: {%d, %f, %c}\n", secondStruct.first, secondStruct.second, secondStruct.third);
}