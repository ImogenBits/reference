#include <stdio.h>
#include <reference.h>


typedef struct {
    int first;
    double second;
    char third;
} myStruct;


void modifyStruct(by_ref(myStruct, byRef)) {
    byRef.first = 10;
    byRef.second = 3.1415;
    byRef.third = 'y';
}


int main() {
    myStruct firstStruct = {1, 2, 'a'};
    myStruct secondStruct = {3, 4, 'b'};
    printf("firstStruct: {%d, %f, %c}\n", firstStruct.first, firstStruct.second, firstStruct.third);
    printf("secondStruct: {%d, %f, %c}\n", secondStruct.first, secondStruct.second, secondStruct.third);

    printf("modifyStruct()\n");
    modifyStruct(RefTo secondStruct);

    printf("firstStruct: {%d, %f, %c}\n", firstStruct.first, firstStruct.second, firstStruct.third);
    printf("secondStruct: {%d, %f, %c}\n", secondStruct.first, secondStruct.second, secondStruct.third);
}