//
// Created by hamon11 on 12/7/17.
//

#ifndef ASSIGNMENT_7_COMPLETE_INTERPRETER_INTERPRETER_H
#define ASSIGNMENT_7_COMPLETE_INTERPRETER_INTERPRETER_H

#include <stdio.h>
#include "Parser.c"
#include "InterpreterStructs.h"

VariableArray *varArray;
VariableArray *assignArray;

void interpretTree();
void loadVarAndAssignArray();
void executeStatements(Node *listOfStatements);
void executeStatement(Node *statementNode);
void executeCin(Node *cinNode);
void executeCout(Node *coutNode);
void executeIf(Node *ifNode);
void executeAssign(Node *assignNode);
void executeWhile(Node *whileNode);
void executeListOfStatements(Node *openBraceNode);
void executeReturn(Node *returnNode);
int executeExp(Node *expNode, _Bool *isChar);
int executeBopland(Node *boplandNode, _Bool *isChar);
int executeBopbor(Node *bopborNode, _Bool *isChar);
int executeBopband(Node *bopbandNode, _Bool *isChar);
int executeEquality(Node *equalityNode, _Bool *isChar);
int executeCompare(Node *compareNode, _Bool *isChar);
int executePlusminus(Node *plusminusNode, _Bool *isChar);
int executeMultDivMod(Node *multdivmodNode, _Bool *isChar);
int executeUop(Node *uopNode, _Bool *isChar);
int executeLit(Node *litNode, _Bool *isChar);
int executeVar(Node *varNode, _Bool *isChar);
void scanToArrays(Node *identNode);
_Bool varInitialized(Node *identNode);
void printValue(int value, _Bool *isChar);

#endif //ASSIGNMENT_7_COMPLETE_INTERPRETER_INTERPRETER_H
