#include "Interpreter.h"

int main(int argc, char *argv[]) {
    createParseTree(argc, argv);
    interpretTree();

    return 0;
}

/**
 * Interprets the parse tree obtained from the top down parser, and executes the statements.
 * createParseTree function of parser should be called prior to calling this function so that
 * parse tree and symbol table will be properly built.
 */
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

/**
 * Implements cin statement of language. First child of node containing the <cin> variable
 * of language should be passed in. If it, the list of statements, or any of the variable nodes
 * are NULL, the parser found a syntax error and the program will be executed.
 * @param cinNode Node containing the token for cin keyword, NULL
 *                if there was a syntax error in the cin statement.
 */
void executeCin(Node *cinNode) {
    if (cinNode == NULL) {
        //A syntax error was found when parsing cin function.
        //Syntax error was printed, so exit.
        exit(1);
    }

    Node *lova = cinNode->rightSibling->rightSibling;
    if (lova == NULL) {
        //A syntax error was found when parsing cin function.
        //Syntax error was printed, so exit.
        exit(1);
    }

    Node *varNode = lova->firstChild;
    if (varNode == NULL) {
        //A syntax error was found when parsing cin function.
        //Syntax error was printed, so exit.
        exit(1);
    }

    Node *identNode = varNode->firstChild;
    scanToArrays(identNode);

    Node *bitRightNode = varNode->rightSibling;
    while (bitRightNode != NULL) {
        scanToArrays(bitRightNode->rightSibling->firstChild);
        bitRightNode = bitRightNode->rightSibling->rightSibling;
    }
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
    varArray = varArrayInit();
    assignArray  = varArrayInit();

    int i;
    for(i = 0; i < symbolsInTable; i++){
        add(varArray, NULL);
        add(assignArray, 0);
    }
}

/**
 * Scans a user inputted value into the slot in the variable array that is represented by
 * variable in the file dictated by the token of the node passed in.
 * @param identNode The node containing the token for the variable in which data should
 *                  be scanned into.
 */
void scanToArrays(Node *identNode){
    int var;
    scanf("%d", &var);
    Symbol *symbol = getSymbolInTable(identNode->data.token.lexeme);
    if(symbol == NULL){
        printf("Variable %s was never declared.\n", identNode->data.token.lexeme);
        exit(1);
    }
    set(varArray, symbol->offset, var);
    set(assignArray, symbol->offset, 1);
}

