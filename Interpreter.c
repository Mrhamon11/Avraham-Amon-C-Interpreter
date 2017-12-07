#include <stdio.h>
#include "Parser.c"
#include "InterpreterStructs.h"
#include "ParserStructs.h"

VariableArray *varArray;
VariableArray *assignArray;

void interpretTree();
void loadVarAndAssignArray();
void executeStatements(Node *listOfStatements);
void executeStatement(Node *statementNode);
void executeCin(Node *cinNode);

int main(int argc, char *argv[]) {
//    int x = 1;
//    int y = 2;
//    int z = 6;
//    char c = 'w';
//
//    VariableArray *a = varArrayInit();
//    add(a, x);
//    add(a, y);
//    add(a, z);
//    add(a, c);
//
//    int i;
//    for(i = 0; i < 4; i++){
//        printf("%d\t", get(a, i));
//    }
//
//    for(i = 0; i < 4; i++){
//        if(i == 3){
//            printf("%c\t", get(a, i));
//        }
//        else{
//            printf("%d\t", get(a, i));
//        }
//    }
    createParseTree(argc, argv);
    varArray = varArrayInit();
    assignArray  = varArrayInit();
    interpretTree();

    return 0;
}

void interpretTree(){
    //creates memory locations for all variables declared.
    loadVarAndAssignArray();

    Node *listOfStatements = root->firstChild->rightSibling;

    if(listOfStatements == NULL)
        return;
    else
        executeStatements(listOfStatements);
}

void executeStatements(Node *listOfStatements){
    Node *nextStatement = listOfStatements->firstChild;

    while(nextStatement != NULL){
        if(nextStatement->data.LHS == "<cin>"){
            executeCin(nextStatement);
        }

        nextStatement = nextStatement->rightSibling;
    }
}

void executeStatement(Node *statementNode){

}

void executeCin(Node *cinNode){

}

/**
 * Ensures variable array has enough room for all symbols declared in file.
 * Initializes assignment array to keep track of which variables have been
 * assigned values.
 * Initial value in each slot of variable array will be set to NULL until a
 * statement assigns a value to a variable.
 * Initial value in each slot of assignment array will be set to zero until
 * a statement assigns it a value.
 */
void loadVarAndAssignArray(){
    int i;
    for(i = 0; i < symbolsInTable; i++){
        add(varArray, NULL);
        add(assignArray, 0);
    }
}

