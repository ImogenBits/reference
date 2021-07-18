#include <stdio.h>
#include <reference.h>


typedef struct {
    int firstVar;
    double secondVar;
    char thirdVar;
} myStruct;


void modifyStruct(by_ref(myStruct, byRef)) {
    byRef.firstVar = 10;
    byRef.secondVar = 3.1415;
    byRef.thirdVar = 'y';
}


int main() {
    myStruct firstStruct = {1, 2, 'a'};
    myStruct secondStruct = {3, 4, 'b'};
    printf("firstStruct: {%d, %f, %c}\n", firstStruct.firstVar, firstStruct.secondVar, firstStruct.thirdVar);
    printf("secondStruct: {%d, %f, %c}\n", secondStruct.firstVar, secondStruct.secondVar, secondStruct.thirdVar);

    printf("modifyStruct()\n");
    modifyStruct(RefTo secondStruct);

    printf("firstStruct: {%d, %f, %c}\n", firstStruct.firstVar, firstStruct.secondVar, firstStruct.thirdVar);
    printf("secondStruct: {%d, %f, %c}\n", secondStruct.firstVar, secondStruct.secondVar, secondStruct.thirdVar);
}