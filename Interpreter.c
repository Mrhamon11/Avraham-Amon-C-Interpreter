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

    _Bool isChar = 0;
    _Bool *isCharPrt = &isChar;

    int expResult = executeExp(expNode, isCharPrt);
    printValue(expResult, isCharPrt);

    Node *bitLeftNode = expNode->rightSibling;
    while(bitLeftNode != NULL){
        *isCharPrt = 0;
        expResult = executeExp(bitLeftNode->rightSibling, isCharPrt);
        printValue(expResult, isCharPrt);
        bitLeftNode = bitLeftNode->rightSibling->rightSibling;
    }
}

void executeIf(Node *ifNode){
    Node *expNode = ifNode->rightSibling->rightSibling;
    Node *statementNode = expNode->rightSibling->rightSibling;

    _Bool isChar = 0;
    _Bool *isCharPrt = &isChar;

    int expResult = executeExp(expNode, isCharPrt);
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

    _Bool isChar = 0;
    _Bool *isCharPrt = &isChar;

    int expResult = executeExp(expNode, isCharPrt);

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

    _Bool isChar = 0;
    _Bool *isCharPrt = &isChar;

    int expResult = executeExp(expNode, isCharPrt);

    while(expResult){
        *isCharPrt = 0;
        executeStatement(expNode->rightSibling->rightSibling->firstChild);
        expResult = executeExp(expNode, isCharPrt);
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

int executeExp(Node *expNode, _Bool *isChar){
    Node *boplandNode = expNode->firstChild;
    int bopland = executeBopland(boplandNode, isChar);

    while(boplandNode->rightSibling != NULL){
        *isChar = 0;
        boplandNode = boplandNode->rightSibling->rightSibling;
        bopland = bopland || executeBopland(boplandNode, isChar);
    }
    return bopland;
}

int executeBopland(Node *boplandNode, _Bool *isChar){
    Node *bopborNode = boplandNode->firstChild;
    int bopbor = executeBopbor(bopborNode, isChar);

    while(bopborNode->rightSibling != NULL){
        *isChar = 0;
        bopborNode = bopborNode->rightSibling->rightSibling;
        bopbor = bopbor && executeBopbor(bopborNode, isChar);
    }
    return bopbor;
}

int executeBopbor(Node *bopborNode, _Bool *isChar){
    Node *bopbandNode = bopborNode->firstChild;
    int bopband = executeBopband(bopbandNode, isChar);

    while(bopbandNode->rightSibling != NULL){
        *isChar = 0;
        bopbandNode = bopbandNode->rightSibling->rightSibling;
        bopband = bopband | executeBopband(bopbandNode, isChar);
    }
    return bopband;
}

int executeBopband(Node *bopbandNode, _Bool *isChar){
    Node *equalityNode = bopbandNode->firstChild;
    int equality = executeEquality(equalityNode, isChar);

    while(equalityNode->rightSibling != NULL){
        *isChar = 0;
        equalityNode = equalityNode->rightSibling->rightSibling;
        equality = equality & executeEquality(equalityNode, isChar);
    }
    return equality;
}

int executeEquality(Node *equalityNode, _Bool *isChar){
    Node *compareNode = equalityNode->firstChild;
    int compare = executeCompare(compareNode, isChar);

    while(compareNode->rightSibling != NULL){
        compareNode = compareNode->rightSibling;
        if(compareNode->data.token.type == NOT_EQUAL){
            compare = compare != executeCompare(compareNode->rightSibling, isChar);
        }
        else if(compareNode->data.token.type == EQUAL){
            compare = compare == executeCompare(compareNode->rightSibling, isChar);
        }
        compareNode = compareNode->rightSibling;
    }
    return compare;
}

int executeCompare(Node *compareNode, _Bool *isChar){
    Node *plusminusNode = compareNode->firstChild;
    int plusminus = executePlusminus(plusminusNode, isChar);

    while(plusminusNode->rightSibling != NULL){
        plusminusNode = plusminusNode->rightSibling;
        if(plusminusNode->data.token.type == GREATER_THAN){
            plusminus = plusminus > executePlusminus(plusminusNode->rightSibling, isChar);
        }
        else if(plusminusNode->data.token.type == GREATER_THAN_EQUAL){
            plusminus = plusminus >= executePlusminus(plusminusNode->rightSibling, isChar);
        }
        else if(plusminusNode->data.token.type == LESS_THAN){
            plusminus = plusminus < executePlusminus(plusminusNode->rightSibling, isChar);
        }
        else if(plusminusNode->data.token.type <= LESS_THAN_EQUAL){
            plusminus = plusminus <= executePlusminus(plusminusNode->rightSibling, isChar);
        }
        plusminusNode = plusminusNode->rightSibling;
    }
    return plusminus;
}

int executePlusminus(Node *plusminusNode, _Bool *isChar){
    Node *multdivmodNode = plusminusNode->firstChild;
    int multdivmod = executeMultDivMod(multdivmodNode, isChar);

    while(multdivmodNode->rightSibling != NULL){
        multdivmodNode = multdivmodNode->rightSibling;
        if(multdivmodNode->data.token.type == ADD_OP){
            multdivmod = multdivmod + executeMultDivMod(multdivmodNode->rightSibling, isChar);
        }
        else if(multdivmodNode->data.token.type == SUB_OP){
            multdivmod = multdivmod - executeMultDivMod(multdivmodNode->rightSibling, isChar);
        }
        multdivmodNode = multdivmodNode->rightSibling;
    }
    return multdivmod;
}

int executeMultDivMod(Node *multdivmodNode, _Bool *isChar){
    Node *uopNode = multdivmodNode->firstChild;
    int uop = executeUop(uopNode, isChar);

    while(uopNode->rightSibling != NULL){
        uopNode = uopNode->rightSibling;
        if(uopNode->data.token.type == MULT_OP){
            uop = uop * executeUop(uopNode->rightSibling, isChar);
        }
        else if(uopNode->data.token.type == DIV_OP){
            uop = uop / executeUop(uopNode->rightSibling, isChar);
        }
        else if(uopNode->data.token.type == MOD_OP){
            uop = uop % executeUop(uopNode->rightSibling, isChar);
        }
        uopNode = uopNode->rightSibling;
    }
    return uop;
}

int executeUop(Node *uopNode, _Bool *isChar){
    Node *nextUopNode = uopNode->firstChild;
    int uop;
    if(nextUopNode->data.LHS == "<lit>"){
        uop = executeLit(nextUopNode, isChar);
    }
    else{
        if(nextUopNode->data.token.type == LOG_NOT){
            uop = !executeUop(nextUopNode->rightSibling, isChar);
        }
        else if(nextUopNode->data.token.type == SUB_OP){
            uop = -executeUop(nextUopNode->rightSibling, isChar);
        }
        else {
            uop = ~executeUop(nextUopNode->rightSibling, isChar);
        }
    }
    return uop;
}

int executeLit(Node *litNode, _Bool *isChar){
    Node *litChild = litNode->firstChild;
    int lit;
    if(litChild->data.LHS == "<variable>"){
        lit = executeVar(litChild, isChar);
    }
    else if(litChild->data.token.type == INTEGER_CONSTANT ||
            litChild->data.token.type == CHAR_CONSTANT){
        if(litChild->data.token.type == CHAR_CONSTANT){
            *isChar = 1;
            char c = litChild->data.token.lexeme[1];
            lit = (int) c;
        }
        else{
            lit = atoi(litChild->data.token.lexeme);
        }
    }
    //It must be ( <exp> )
    else{
        lit = (executeExp(litChild->rightSibling, isChar));
    }

    return lit;
}

int executeVar(Node *varNode, _Bool *isChar){
    Node *identNode = varNode->firstChild;
    if(!varInitialized(identNode)){
        printf("Variable %s was not assigned a value!\n", identNode->data.token.lexeme);
        exit(1);
    }
    Symbol *symbol = getSymbolInTable(identNode->data.token.lexeme);
    if(symbol != NULL && symbol->type == CHAR_TYPE){
        *isChar = 1;
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
    char charVar;
    Symbol *symbol = getSymbolInTable(identNode->data.token.lexeme);
    if(symbol == NULL){
        printf("Variable %s was never declared.\n", identNode->data.token.lexeme);
        exit(1);
    }
    if(symbol->type == CHAR_TYPE){
        scanf("%c", &charVar);
        set(varArray, symbol->offset, (int) charVar);
    }
    else{
        scanf("%d", &var);
        set(varArray, symbol->offset, var);
    }

    set(assignArray, symbol->offset, 1);
}

void printValue(int value, _Bool *isChar){
    if(*isChar){
        printf("%c\n", (char) value);
    }
    else{
        printf("%d\n", value);
    }
}

_Bool varInitialized(Node *identNode){
    Symbol *symbol = getSymbolInTable(identNode->data.token.lexeme);
    int index = symbol->offset;
    if(get(assignArray, index)){
        return 1;
    }
    return 0;
}

