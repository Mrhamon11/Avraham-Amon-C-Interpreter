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
int executeExp(Node *expNode);
int executeBopland(Node *boplandNode);
int executeBopbor(Node *bopborNode);
int executeBopband(Node *bopbandNode);
int executeEquality(Node *equalityNode);
int executeCompare(Node *compareNode);
int executePlusminus(Node *plusminusNode);
int executeMultDivMod(Node *multdivmodNode);
int executeUopNode(Node *uopNode);
void scanToArrays(Node *identNode);

#endif //ASSIGNMENT_7_COMPLETE_INTERPRETER_INTERPRETER_H
