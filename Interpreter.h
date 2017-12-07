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
void scanToArrays(Node *identNode);

#endif //ASSIGNMENT_7_COMPLETE_INTERPRETER_INTERPRETER_H
