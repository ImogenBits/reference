#include <reference.h>
#include <stdio.h>

typedef struct {
    int firstVar;
    double secondVar;
} myStruct;

void modifyStructs(myStruct byValue, ByRef(myStruct, byRef))
    byValue.firstVar = 10;
    byValue.secondVar = 10.5;
    byRef.firstVar = 20;
    byRef.secondVar = 20.5;
}

int main() {
    myStruct firstStruct = {1, 2};
    MakeRef(myStruct, secondStruct) = {3, 4};
    printf("firstStruct: {%d, %f}\n", firstStruct.firstVar, firstStruct.secondVar);
    printf("secondStruct: {%d, %f}\n", secondStruct.firstVar, secondStruct.secondVar);

    printf("modifyStructs()\n");
    modifyStructs(firstStruct, PassRef(secondStruct));

    printf("firstStruct: {%d, %f}\n", firstStruct.firstVar, firstStruct.secondVar);
    printf("secondStruct: {%d, %f}\n", secondStruct.firstVar, secondStruct.secondVar);
}