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