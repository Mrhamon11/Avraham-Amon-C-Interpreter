#include "Interpreter.h"
#include "ParserStructs.h"

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
    else if(statementNode->data.LHS == "<cout>"){
        executeCout(statementNode->firstChild);
    }
    else if(statementNode->data.LHS == "<if>"){
        executeIf(statementNode->firstChild);
    }
    else if(statementNode->data.LHS == "<assign>"){
        executeAssign(statementNode->firstChild);
    }
    else if(statementNode->data.LHS == "<while>"){
        executeWhile(statementNode->firstChild);
    }
    else if(statementNode->data.token.type == OPEN_BRACE){
        executeListOfStatements(statementNode);
    }
    else if(statementNode->data.token.type == RETURN_KEYWORD){
        executeReturn(statementNode);
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
    Node *lova = cinNode->rightSibling->rightSibling;
    Node *varNode = lova->firstChild;

    Node *identNode = varNode->firstChild;
    scanToArrays(identNode);

    Node *bitRightNode = varNode->rightSibling;
    while (bitRightNode != NULL) {
        scanToArrays(bitRightNode->rightSibling->firstChild);
        bitRightNode = bitRightNode->rightSibling->rightSibling;
    }
}

void executeCout(Node *coutNode){
    Node *loe = coutNode->rightSibling->rightSibling;
    Node *expNode = loe->firstChild;

    int expResult = executeExp(expNode);
    printValue(expResult);

    Node *bitLeftNode = expNode->rightSibling;
    while(bitLeftNode != NULL){
        expResult = executeExp(bitLeftNode->rightSibling);
        printValue(expResult);
        bitLeftNode = bitLeftNode->rightSibling->rightSibling;
    }
}

void executeIf(Node *ifNode){
    Node *expNode = ifNode->rightSibling->rightSibling;
    Node *statementNode = expNode->rightSibling->rightSibling;
    int expResult = executeExp(expNode);
    if(expResult){
        executeStatement(statementNode->firstChild);
    }
    else{
        if(statementNode->rightSibling != NULL){
            executeStatement(statementNode->rightSibling->rightSibling->firstChild);
        }
    }
}

void executeAssign(Node *assignNode){
    Node *expNode = assignNode->rightSibling->rightSibling;
    int expResult = executeExp(expNode);

    Node *var = assignNode->firstChild;
    int index = getSymbolInTable(var->firstChild->data.token.lexeme)->offset;
    set(varArray, index, expResult);
    set(assignArray, index, 1);

    var = var->rightSibling;
    while(var != NULL){
        index = getSymbolInTable(var->rightSibling->firstChild->data.token.lexeme)->offset;
        set(varArray, index, expResult);
        set(assignArray, index, 1);
        var = var->rightSibling->rightSibling;
    }
}

void executeWhile(Node *whileNode){
    Node *expNode = whileNode->rightSibling->rightSibling;
    int expResult = executeExp(expNode);

    while(expResult){
        executeStatement(expNode->rightSibling->rightSibling->firstChild);
        expResult = executeExp(expNode);
    }
}

void executeListOfStatements(Node *openBraceNode){
    Node *statementNode = openBraceNode->rightSibling->firstChild;

    while(statementNode != NULL){
        executeStatement(statementNode->firstChild);
        statementNode = statementNode->rightSibling;
    }
}

void executeReturn(Node *returnNode){
    //since the EBNF only contains rules found inside the body of the function,
    //a return statement essentially means quit. Leaving this function here
    //in case I decide to change the grammar to include subprograms.
    exit(1);
}

int executeExp(Node *expNode){
    Node *boplandNode = expNode->firstChild;
    int bopland = executeBopland(boplandNode);

    while(boplandNode->rightSibling != NULL){
        boplandNode = boplandNode->rightSibling->rightSibling;
        bopland = bopland || executeBopland(boplandNode);
    }
    return bopland;
}

int executeBopland(Node *boplandNode){
    Node *bopborNode = boplandNode->firstChild;
    int bopbor = executeBopbor(bopborNode);

    while(bopborNode->rightSibling != NULL){
        bopborNode = bopborNode->rightSibling->rightSibling;
        bopbor = bopbor && executeBopbor(bopborNode);
    }
    return bopbor;
}

int executeBopbor(Node *bopborNode){
    Node *bopbandNode = bopborNode->firstChild;
    int bopband = executeBopband(bopbandNode);

    while(bopbandNode->rightSibling != NULL){
        bopbandNode = bopbandNode->rightSibling->rightSibling;
        bopband = bopband | executeBopband(bopbandNode);
    }
    return bopband;
}

int executeBopband(Node *bopbandNode){
    Node *equalityNode = bopbandNode->firstChild;
    int equality = executeEquality(equalityNode);

    while(equalityNode->rightSibling != NULL){
        equalityNode = equalityNode->rightSibling->rightSibling;
        equality = equality & executeEquality(equalityNode);
    }
    return equality;
}

int executeEquality(Node *equalityNode){
    Node *compareNode = equalityNode->firstChild;
    int compare = executeCompare(compareNode);

    while(compareNode->rightSibling != NULL){
        compareNode = compareNode->rightSibling;
        if(compareNode->data.token.type == NOT_EQUAL){
            compare = compare != executeCompare(compareNode->rightSibling);
        }
        else if(compareNode->data.token.type == EQUAL){
            compare = compare == executeCompare(compareNode->rightSibling);
        }
        compareNode = compareNode->rightSibling;
    }
    return compare;
}

int executeCompare(Node *compareNode){
    Node *plusminusNode = compareNode->firstChild;
    int plusminus = executePlusminus(plusminusNode);

    while(plusminusNode->rightSibling != NULL){
        plusminusNode = plusminusNode->rightSibling;
        if(plusminusNode->data.token.type == GREATER_THAN){
            plusminus = plusminus > executePlusminus(plusminusNode->rightSibling);
        }
        else if(plusminusNode->data.token.type == GREATER_THAN_EQUAL){
            plusminus = plusminus >= executePlusminus(plusminusNode->rightSibling);
        }
        else if(plusminusNode->data.token.type == LESS_THAN){
            plusminus = plusminus < executePlusminus(plusminusNode->rightSibling);
        }
        else if(plusminusNode->data.token.type <= LESS_THAN_EQUAL){
            plusminus = plusminus <= executePlusminus(plusminusNode->rightSibling);
        }
        plusminusNode = plusminusNode->rightSibling;
    }
    return plusminus;
}

int executePlusminus(Node *plusminusNode){
    Node *multdivmodNode = plusminusNode->firstChild;
    int multdivmod = executeMultDivMod(multdivmodNode);

    while(multdivmodNode->rightSibling != NULL){
        multdivmodNode = multdivmodNode->rightSibling;
        if(multdivmodNode->data.token.type == ADD_OP){
            multdivmod = multdivmod + executeMultDivMod(multdivmodNode->rightSibling);
        }
        else if(multdivmodNode->data.token.type == SUB_OP){
            multdivmod = multdivmod - executeMultDivMod(multdivmodNode->rightSibling);
        }
        multdivmodNode = multdivmodNode->rightSibling;
    }
    return multdivmod;
}

int executeMultDivMod(Node *multdivmodNode){
    Node *uopNode = multdivmodNode->firstChild;
    int uop = executeUop(uopNode);

    while(uopNode->rightSibling != NULL){
        uopNode = uopNode->rightSibling;
        if(uopNode->data.token.type == MULT_OP){
            uop = uop * executeUop(uopNode->rightSibling);
        }
        else if(uopNode->data.token.type == DIV_OP){
            uop = uop / executeUop(uopNode->rightSibling);
        }
        else if(uopNode->data.token.type == MOD_OP){
            uop = uop % executeUop(uopNode->rightSibling);
        }
        uopNode = uopNode->rightSibling;
    }
    return uop;
}

int executeUop(Node *uopNode){
    Node *nextUopNode = uopNode->firstChild;
    int uop;
    if(nextUopNode->data.LHS == "<lit>"){
        uop = executeLit(nextUopNode);
    }
    else{
        if(nextUopNode->data.token.type == LOG_NOT){
            uop = !executeUop(nextUopNode->rightSibling);
        }
        else if(nextUopNode->data.token.type == SUB_OP){
            uop = -executeUop(nextUopNode->rightSibling);
        }
        else {
            uop = ~executeUop(nextUopNode->rightSibling);
        }
    }
    return uop;
}

int executeLit(Node *litNode){
    Node *litChild = litNode->firstChild;
    int lit;
    if(litChild->data.LHS == "<variable>"){
        lit = executeVar(litChild);
    }
    else if(litChild->data.token.type == INTEGER_CONSTANT ||
            litChild->data.token.type == CHAR_CONSTANT){
        lit = atoi(litChild->data.token.lexeme);
    }
    //It must be ( <exp> )
    else{
        lit = (executeExp(litChild->rightSibling));
    }

    return lit;
}

int executeVar(Node *varNode){
    Node *identNode = varNode->firstChild;
    if(!varInitialized(identNode)){
        printf("Variable %s was not assigned a value!\n", identNode->data.token.lexeme);
        exit(1);
    }
    int index = getSymbolInTable(identNode->data.token.lexeme)->offset;
    return get(varArray, index);
}

/**
 * Ensures variable array has enough room for all symbols declared in file.
 * Initializes assignment array to keep track of which variables have been
 * assigned values.
 * Initial value in each slot of variable array will be set to 0 until a
 * statement assigns a value to a variable.
 * Initial value in each slot of assignment array will be set to zero until
 * a statement assigns it a value.
 */
void loadVarAndAssignArray(){
    varArray = varArrayInit();
    assignArray  = varArrayInit();

    int i;
    for(i = 0; i < symbolsInTable; i++){
        add(varArray, 0);
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

void printValue(int value){
    printf("%d\n", value);
}

_Bool varInitialized(Node *identNode){
    Symbol *symbol = getSymbolInTable(identNode->data.token.lexeme);
    int index = symbol->offset;
    if(get(assignArray, index)){
        return 1;
    }
    return 0;
}

