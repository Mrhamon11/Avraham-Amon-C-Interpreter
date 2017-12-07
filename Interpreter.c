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
        executeStatement(nextStatement->firstChild);
        nextStatement = nextStatement->rightSibling;
    }
}

void executeStatement(Node *statementNode){
    if(statementNode->data.LHS == "<cin>"){
        executeCin(statementNode->firstChild);
    }
}

void executeCin(Node *cinNode){
    if(cinNode == NULL){
        //A syntax error was found when parsing cin function.
        //Syntax error was printed, so exit.
        exit(1);
    }

    Node *lova = cinNode->rightSibling->rightSibling;


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

