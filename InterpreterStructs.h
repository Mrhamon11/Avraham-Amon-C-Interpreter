//
// Created by hamon11 on 12/6/17.
//

#ifndef ASSIGNMENT_7_COMPLETE_INTERPRETER_INTERPRETERSTRUCTS_H
#define ASSIGNMENT_7_COMPLETE_INTERPRETER_INTERPRETERSTRUCTS_H

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_ARRAY_SIZE 50

typedef struct VariableArray VariableArray;

VariableArray* varArrayInit();
void add(VariableArray *varArray, int value);
void doubleArrayIfFull(VariableArray *varArray);
int get(VariableArray *varArray, int index);

typedef struct RuntimeStack RuntimeStack;

struct VariableArray{
    int size;
    int capacity;
    int *data;
};

VariableArray* varArrayInit(){
    int size = 0;
    int capacity = INITIAL_ARRAY_SIZE;

    int *data = malloc(sizeof(int) * capacity);

    VariableArray *varArray = malloc(sizeof(VariableArray));
    varArray->data = data;
    varArray->capacity = capacity;
    varArray->data = data;

    return varArray;
}

void add(VariableArray *varArray, int value){
    doubleArrayIfFull(varArray);

    varArray->data[varArray->size++] = value;
}

void doubleArrayIfFull(VariableArray *varArray){
    if(varArray->size >= varArray->capacity){
        varArray->capacity *= 2;
        varArray->data = realloc(varArray->data, sizeof(int) * varArray->capacity);
    }
}

int get(VariableArray *varArray, int index){
    if(index >= varArray->size || index < 0){
        printf("Index %d out of bounds for vector of size %d\n", index, varArray->size);
        exit(1);
    }

    return varArray->data[index];
}


#endif //ASSIGNMENT_7_COMPLETE_INTERPRETER_INTERPRETERSTRUCTS_H
