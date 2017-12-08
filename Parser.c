#include "Tokenizer.c"
#include "FirstFinder.h"
#include "ParserStructs.h"

Token *nextTk;
Node *root;
PotentialSymbol ps;
_Bool symbolTableCreated = 0;
_Bool synataxError = 0;

Node* programFunc();
Node* listOfStatementsFunc();
Node* listOfDeclarationsFunc();
Node* declarationFunc();
Node* variablesFunc();
Node* variableFunc();
Node* typeFunc();
Node* statementFunc();
Node* cinFunc();
Node* listOfVariableAngleFunc();
Node* coutFunc();
Node* listOfExpressionsFunc();
Node* ifFunc();
Node* expFunc();
Node* boplandFunc();
Node* bopborFunc();
Node* bopbandFunc();
Node* equalityFunc();
Node* compareFunc();
Node* plusMinusFunc();
Node* multDivModFunc();
Node* uopFunc();
Node* litFunc();
Node* assignFunc();
Node* whileFunc();
_Bool maintainSymbolTable(Token *token);


void createParseTree(int argc, char *argv[]){
    initTokenizer(argc, argv);
    nextTk = nextToken();
    root = newInnerNode("<program>");
    root->firstChild = programFunc();

    if(synataxError){
        exit(1);
    }
//    printTree(root);
//    return root;
}

Node* programFunc(){
    initPS(ps);

    Node *listOfDecNode = newInnerNode("<listofdeclarations>");

    if(inFirst(listOfDeclarationsRule, nextTk)){
        listOfDecNode->firstChild = listOfDeclarationsFunc();
    }
    symbolTableCreated = 1;

    //Print symbol table and notification that parse tree will be printed. Tree is printed when complete.
//    printTable();
//    printf("Printing depth first search preorder traversal of parse tree. Nodes"
//                   " are listed as either Non-Terminals or Lexemes:\n\n");

    if(inFirst(listOfStatementsRule, nextTk)){
        Node *listOfStateNode = newInnerNode("<listofstatements>");
        listOfStateNode->firstChild = listOfStatementsFunc();
        listOfDecNode->rightSibling = listOfStateNode;
    }
    return listOfDecNode;
}

Node* listOfDeclarationsFunc(){
    Node *decNode = newInnerNode("<declaration>");
    Node *subtreeRoot = decNode;
    while(inFirst(declarationRule, nextTk)){
        decNode->firstChild = declarationFunc();
        if(inFirst(declarationRule, nextTk)){
            Node *sibling = newInnerNode("<declaration>");
            decNode->rightSibling = sibling;
            decNode = sibling;
        }

    }
    if(subtreeRoot->firstChild == NULL){
        return NULL;
    }
    return subtreeRoot;
}

Node* listOfStatementsFunc(){
    Node *stateNode = newInnerNode("<statement>");
    Node *subtreeRoot = stateNode;
    while(inFirst(statementRule, nextTk)){
        stateNode->firstChild = statementFunc();
        if(inFirst(statementRule, nextTk)){
            Node *sibling = newInnerNode("<statement>");
            stateNode->rightSibling = sibling;
            stateNode = sibling;
        }
    }
    if(subtreeRoot->firstChild == NULL){
        return NULL;
    }
    return subtreeRoot;
}

Node* declarationFunc(){
    Node *typeNode = newInnerNode("<type>");
    typeNode->firstChild = typeFunc();

    Node *varsNode = newInnerNode("<variables>");
    varsNode->firstChild = variablesFunc();
    typeNode->rightSibling = varsNode;

    if(nextTk->type != SEMI_COLON){
        printf("Missing ; after declaration statement!\n");
        synataxError = 1;
        return NULL;
    }
    else{
        Node *semiColonNode = newLeafNode(nextTk);
        varsNode->rightSibling = semiColonNode;

        nextTk = nextToken();
    }


    if(typeNode->firstChild == NULL){
        synataxError = 1;
        return NULL;
    }
    return typeNode;
}

Node* statementFunc(){
    //cin statement:
    if(inFirst(cinRule, nextTk)){
        Node *cinNode = newInnerNode("<cin>");
        cinNode->firstChild = cinFunc();
        return cinNode;
    }

    //cout statement:
    else if(inFirst(coutRule, nextTk)){
        Node *coutNode = newInnerNode("<cout>");
        coutNode->firstChild = coutFunc();
        return coutNode;
    }

    //if statement
    else if(inFirst(ifRule, nextTk)){
        Node *ifNode = newInnerNode("<if>");
        ifNode->firstChild = ifFunc();
        return ifNode;
    }

    //assignment statement
    else if(inFirst(assignRule, nextTk)){
        Node *assignNode = newInnerNode("<assign>");
        assignNode->firstChild = assignFunc();
        return assignNode;
    }

    //while statement
    else if(inFirst(whileRule, nextTk)){
        Node *whileNode = newInnerNode("<while>");
        whileNode->firstChild = whileFunc();
        return whileNode;
    }

    //list of statements
    else if(nextTk->type == OPEN_BRACE){
        Node *openBraceNode = newLeafNode(nextTk);
        nextTk = nextToken();
        Node *listOfStateNode = newInnerNode("<lisofstatements>");
        openBraceNode->rightSibling = listOfStateNode;
        listOfStateNode->firstChild = listOfStatementsFunc();
        if(nextTk->type != CLOSE_BRACE){
            printf("List of statements must be surrounded in curly braces!");
            synataxError = 1;
            return NULL;
        }
        Node *closeBraceNode = newLeafNode(nextTk);
        nextTk = nextToken();
        listOfStateNode->rightSibling = closeBraceNode;
        return openBraceNode;
    }

    //return statement
    else if(nextTk->type == RETURN_KEYWORD){
        Node *returnNode = newLeafNode(nextTk);
        nextTk = nextToken();

//        if(!inFirst(expRule, nextTk) && nextTk->type != SEMI_COLON){
//            printf("%s\n", "return statements must be")
//            return NULL:
//        }
//        if(inFirst(expRule, nextTk)) {
//            Node *exp = newInnerNode("<exp>");
//            returnNode->rightSibling = exp;
//            exp->firstChild = expFunc();
//        }

        if(!nextTk->type == SEMI_COLON){
            printf("%s\n", "return statements must be followed by a semi-colon!");
            synataxError = 1;
            return NULL;
        }
        Node *semiColonNode = newLeafNode(nextTk);
        nextTk = nextToken();
        returnNode->rightSibling = semiColonNode;
        return returnNode;
    }
    else{
        printf("%s\n", "Not a statement!");
        synataxError = 1;
        return NULL;
    }
}

Node *ifFunc(){
    Node *ifNode = newLeafNode(nextTk);
    nextTk = nextToken();

    if(nextTk->type != OPEN_PARENT) {
        printf("%s\n", "Expressions in if statements must be surrounded by parentheses!");
        synataxError = 1;
        return NULL;
    }

    Node *openParentNode = newLeafNode(nextTk);
    nextTk = nextToken();
    Node *exp = newInnerNode("<exp>");

    if(!inFirst(expRule, nextTk)){
        printf("%s\n", "Assignment must have expression on right hand side!");
        synataxError = 1;
        return NULL;
    }

    ifNode->rightSibling = openParentNode;
    openParentNode->rightSibling = exp;
    exp->firstChild = expFunc();

    if(nextTk->type != CLOSE_PARENT){
        printf("%s\n", "Expressions in if statements must be surrounded by parentheses!");
        synataxError = 1;
        return NULL;
    }

    Node *closeParentNode = newLeafNode(nextTk);
    nextTk = nextToken();
    exp->rightSibling = closeParentNode;

    Node *statementNode = newInnerNode("<statement>");
    closeParentNode->rightSibling = statementNode;
    statementNode->firstChild = statementFunc();

    if(nextTk->type == ELSE_KEYWORD){
        Node *elseNode = newLeafNode(nextTk);
        nextTk = nextToken();
        Node *stmtNode = newInnerNode("<statement>");
        elseNode->rightSibling = stmtNode;
        stmtNode->firstChild = statementFunc();
        statementNode->rightSibling = elseNode;
    }

    return ifNode;
}

Node* assignFunc(){
    Node *variablesNode = newInnerNode("<variables>");
    variablesNode->firstChild = variablesFunc();

    if(nextTk->type != ASSIGN) {
        printf("%s\n", "missing assignment operator!");
        synataxError = 1;
        return NULL;
    }

    Node *assignNode = newLeafNode(nextTk);
    nextTk = nextToken();
    variablesNode->rightSibling = assignNode;

    if(!inFirst(expRule, nextTk)){
        printf("%s\n", "Assignment must have expression on right hand side!");
        synataxError = 1;
        return NULL;
    }

    Node *expNode = newInnerNode("<exp>");
    expNode->firstChild = expFunc();
    assignNode->rightSibling = expNode;

    if(nextTk->type != SEMI_COLON){
        printf("%s\n", "Missing ; in assignment statement!");
        synataxError = 1;
        return NULL;
    }

    Node *semiColonNode = newLeafNode(nextTk);
    nextTk = nextToken();
    expNode->rightSibling = semiColonNode;

    return variablesNode;
}

Node* whileFunc(){
    Node *whileNode = newLeafNode(nextTk);
    nextTk = nextToken();

    if(nextTk->type != OPEN_PARENT) {
        printf("%s\n", "Expressions in while statements must be surrounded by parentheses!");
        synataxError = 1;
        return NULL;
    }

    Node *openParentNode = newLeafNode(nextTk);
    nextTk = nextToken();
    Node *exp = newInnerNode("<exp>");

    if(!inFirst(expRule, nextTk)){
        printf("Missing expression for condition in while loop!\n");
        synataxError = 1;
        return NULL;
    }

    whileNode->rightSibling = openParentNode;
    openParentNode->rightSibling = exp;
    exp->firstChild = expFunc();

    if(nextTk->type != CLOSE_PARENT){
        printf("%s\n", "Expressions in while statements must be surrounded by parentheses!");
        synataxError = 1;
        return NULL;
    }

    Node *closeParentNode = newLeafNode(nextTk);
    nextTk = nextToken();
    exp->rightSibling = closeParentNode;

    Node *statementNode = newInnerNode("<statement>");
    closeParentNode->rightSibling = statementNode;
    statementNode->firstChild = statementFunc();

    return whileNode;
}

Node *cinFunc(){
    Node *cinNode = newLeafNode(nextTk);
    nextTk = nextToken();

    if(nextTk->type != BIT_RIGHT){
        printf("cin missing >> for operands!\n");
        synataxError = 1;
        return NULL;
    }
    Node *bitRightNode = newLeafNode(nextTk);
    cinNode->rightSibling = bitRightNode;

    nextTk = nextToken();
    if(inFirst(listofvariableangleRule, nextTk)){
        Node *lovaNode = newInnerNode("<listofvariableangle>");
        lovaNode->firstChild = listOfVariableAngleFunc();
        bitRightNode->rightSibling = lovaNode;
    }
    else{
        printf("Missing variable on right hand side of cin statement!\n");
        synataxError = 1;
        return NULL;
    }

    if(nextTk->type != SEMI_COLON){
        printf("cin statement must end with semi-colon!\n");
        synataxError = 1;
        return NULL;
    }
    Node *semiColonNode = newLeafNode(nextTk);
    bitRightNode->rightSibling->rightSibling = semiColonNode;
    nextTk = nextToken();

    return cinNode;
}

Node* coutFunc(){
    Node *coutNode = newLeafNode(nextTk);
    nextTk = nextToken();

    if(nextTk->type != BIT_LEFT){
        printf("cout missing << for operands!\n");
        synataxError = 1;
        return NULL;
    }

    Node *bitLeftNode = newLeafNode(nextTk);
    coutNode->rightSibling = bitLeftNode;

    nextTk = nextToken();
    if(inFirst(listOfExpressionsRule, nextTk)){
        Node *loexp = newInnerNode("<listofexpressions>");
        loexp->firstChild = listOfExpressionsFunc();
        bitLeftNode->rightSibling = loexp;
    }
    else{
        printf("Missing expression(s) on right hand side of cout statement!\n");
        synataxError = 1;
        return NULL;
    }

    if(nextTk->type != SEMI_COLON){
        printf("cout statement must end with semi-colon!\n");
        synataxError = 1;
        return NULL;
    }
    Node *semiColonNode = newLeafNode(nextTk);
    bitLeftNode->rightSibling->rightSibling = semiColonNode;
    nextTk = nextToken();

    return coutNode;
}

Node* listOfVariableAngleFunc(){
    Node *varNode = newInnerNode("<variable>");
    varNode->firstChild = variableFunc();
    Node *subtreeRoot = varNode;
    while(nextTk->type == BIT_RIGHT){
        Node *bitRightNode = newLeafNode(nextTk);
        varNode->rightSibling = bitRightNode;
        nextTk = nextToken();
        varNode = variableFunc();
        if(varNode != NULL){
            Node *var = newInnerNode("<variable>");
            var->firstChild = varNode;
            bitRightNode->rightSibling = var;
            varNode = var;
        }
    }
    return subtreeRoot;
}

Node* listOfExpressionsFunc(){
    Node *expNode = newInnerNode("<exp>");
    expNode->firstChild = expFunc();
    Node *subtreeRoot = expNode;
    while(nextTk->type == BIT_LEFT){
        Node *bitLeftNode = newLeafNode(nextTk);
        expNode->rightSibling = bitLeftNode;
        nextTk = nextToken();
        expNode = expFunc();
        if(expNode != NULL){
            Node *exp = newInnerNode("<exp>");
            exp->firstChild = expNode;
            bitLeftNode->rightSibling = exp;
            expNode = exp;
        }
    }
    return subtreeRoot;
}

Node* expFunc(){
    Node *boplandNode = newInnerNode("<bopland>");
    boplandNode->firstChild = boplandFunc();
    Node *subtreeRoot = boplandNode;
    while(nextTk->type == LOG_OR){
        Node *logOrNode = newLeafNode(nextTk);
        boplandNode->rightSibling = logOrNode;
        nextTk = nextToken();
        boplandNode = boplandFunc();
        if(boplandNode != NULL){
            Node *bopland = newInnerNode("<bopland>");
            bopland->firstChild = boplandNode;
            logOrNode->rightSibling = bopland;
            boplandNode = bopland;
        }
    }
    return subtreeRoot;
}

Node* boplandFunc(){
    Node *bopborNode = newInnerNode("<bopbor>");
    bopborNode->firstChild = bopborFunc();
    Node *subtreeRoot = bopborNode;
    while(nextTk->type == LOG_AND){
        Node *logAndNode = newLeafNode(nextTk);
        bopborNode->rightSibling = logAndNode;
        nextTk = nextToken();
        bopborNode = bopborFunc();
        if(bopborNode != NULL){
            Node *bopbor = newInnerNode("<bopbor>");
            bopbor->firstChild = bopborNode;
            logAndNode->rightSibling = bopbor;
            bopborNode = bopbor;
        }
    }
    return subtreeRoot;
}

Node* bopborFunc(){
    Node *bopbandNode = newInnerNode("<bopband>");
    bopbandNode->firstChild = bopbandFunc();
    Node *subtreeRoot = bopbandNode;
    while(nextTk->type == BIT_OR){
        Node *bitOrNode = newLeafNode(nextTk);
        bopbandNode->rightSibling = bitOrNode;
        nextTk = nextToken();
        bopbandNode = bopbandFunc();
        if(bopbandNode != NULL){
            Node *bopband = newInnerNode("<bopband>");
            bopband->firstChild = bopbandNode;
            bitOrNode->rightSibling = bopband;
            bopbandNode = bopband;
        }
    }
    return subtreeRoot;
}

Node* bopbandFunc(){
    Node *equality = newInnerNode("<equality>");
    equality->firstChild = equalityFunc();
    Node *subtreeRoot = equality;
    while(nextTk->type == BIT_AND){
        Node *bitAndNode = newLeafNode(nextTk);
        equality->rightSibling = bitAndNode;
        nextTk = nextToken();
        equality = equalityFunc();
        if(equality != NULL){
            Node *eq = newInnerNode("<equality>");
            eq->firstChild = equality;
            bitAndNode->rightSibling = eq;
            equality = eq;
        }
    }
    return subtreeRoot;
}

Node* equalityFunc(){
    Node *compareNode = newInnerNode("<compare>");
    compareNode->firstChild = compareFunc();
    Node *subtreeRoot = compareNode;
    while(nextTk->type == NOT_EQUAL || nextTk->type == EQUAL){
        Node *equalOrNotNode = newLeafNode(nextTk);
        compareNode->rightSibling = equalOrNotNode;
        nextTk = nextToken();
        compareNode = compareFunc();
        if(compareNode != NULL){
            Node *compare = newInnerNode("<compare>");
            compare->firstChild = compareNode;
            equalOrNotNode->rightSibling = compare;
            compareNode = compare;
        }
    }
    return subtreeRoot;
}

Node* compareFunc(){
    Node *plusMinusNode = newInnerNode("<plusminus>");
    plusMinusNode->firstChild = plusMinusFunc();
    Node *subtreeRoot = plusMinusNode;
    while(nextTk->type == GREATER_THAN || nextTk->type == GREATER_THAN_EQUAL
          || nextTk->type == LESS_THAN || nextTk->type == LESS_THAN_EQUAL){
        Node *angleNode = newLeafNode(nextTk);
        plusMinusNode->rightSibling = angleNode;
        nextTk = nextToken();
        plusMinusNode = plusMinusFunc();
        if(plusMinusNode != NULL){
            Node *plusMinus = newInnerNode("<pluseminus>");
            plusMinus->firstChild = plusMinusNode;
            angleNode->rightSibling = plusMinus;
            plusMinusNode = plusMinus;
        }
    }
    return subtreeRoot;
}

Node* plusMinusFunc(){
    Node *multDivModNode = newInnerNode("<multdividemod>");
    multDivModNode->firstChild = multDivModFunc();
    Node *subtreeRoot = multDivModNode;
    while(nextTk->type == ADD_OP || nextTk->type == SUB_OP){
        Node *plusMinusTk = newLeafNode(nextTk);
        multDivModNode->rightSibling = plusMinusTk;
        nextTk = nextToken();
        multDivModNode = multDivModFunc();
        if(multDivModNode != NULL){
            Node *multDivMod = newInnerNode("<multdividemod>");
            multDivMod->firstChild = multDivModNode;
            plusMinusTk->rightSibling = multDivMod;
            multDivModNode = multDivMod;
        }
    }
    return subtreeRoot;
}

Node* multDivModFunc(){
    Node *uopNode = newInnerNode("<uop>");
    uopNode->firstChild = uopFunc();
    Node *subtreeRoot = uopNode;
    while(nextTk->type == MULT_OP || nextTk->type == DIV_OP || nextTk->type == MOD_OP){
        Node *multdivmod = newLeafNode(nextTk);
        uopNode->rightSibling = multdivmod;
        nextTk = nextToken();
        uopNode = uopFunc();
        if(uopNode != NULL){
            Node *uop = newInnerNode("<uop>");
            uop->firstChild = uopNode;
            multdivmod->rightSibling = uop;
            uopNode = uop;
        }
    }
    return subtreeRoot;
}

Node* uopFunc(){
    if(nextTk->type == LOG_NOT || nextTk->type == SUB_OP|| nextTk->type == BIT_NOT){
        Node *uopOp = newLeafNode(nextTk);
        nextTk = nextToken();
        Node *uop = newInnerNode("<uop>");
        uopOp->rightSibling = uop;
        uop->firstChild = uopFunc();
        return uopOp;
    }
    if(inFirst(litRule, nextTk)){
        Node *lit = newInnerNode("<lit>");
        lit->firstChild = litFunc();
        return lit;
    }
    printf("Only '!', '-' and '~' are allowed as unary operators!\n");
    synataxError = 1;
    return NULL;
}

Node* litFunc(){
    if(nextTk->type == OPEN_PARENT){
        Node *leftParent = newLeafNode(nextTk);
        nextTk = nextToken();
        Node *expNode = newInnerNode("<exp>");
        leftParent->rightSibling = expNode;
        expNode->firstChild = expFunc();
        if(nextTk->type != CLOSE_PARENT){
            printf("Missing closing parentheses for expression literal!\n");
            synataxError = 1;
            return NULL;
        }
        Node *rightParent = newLeafNode(nextTk);
        expNode->rightSibling = rightParent;
        nextTk = nextToken();
        return leftParent;
    }
    else if(inFirst(variableRule, nextTk)){
        Node *varNode = newInnerNode("<variable>");
        varNode->firstChild = variableFunc();
        return varNode;
    }
    else if(nextTk->type == INTEGER_CONSTANT || nextTk->type == CHAR_CONSTANT){
        Node *constNode = newLeafNode(nextTk);
        nextTk = nextToken();
        return constNode;
    }
    else{
        return NULL;
    }
}

Node* typeFunc(){
    if(inFirst(typeRule, nextTk)){
        Node *intOrCharNode = newLeafNode(nextTk);
        ps.type = nextTk->type;
        nextTk = nextToken();
        return intOrCharNode;
    }
    printf("Declaration without type!\n");
    synataxError = 1;
    return NULL;
}

Node* variablesFunc(){
    Node *varNode = newInnerNode("<variable>");
    varNode->firstChild = variableFunc();
    Node *subtreeRoot = varNode;
    while(nextTk->type == COMMA){
        Node *commaNode = newLeafNode(nextTk);
        varNode->rightSibling = commaNode;
        nextTk = nextToken();
        varNode = variableFunc();
        if(varNode != NULL){
            Node *var = newInnerNode("<variable>");
            var->firstChild = varNode;
            commaNode->rightSibling = var;
        }
    }
    return subtreeRoot;
}

Node* variableFunc(){
    if(inFirst(variableRule, nextTk)){
        Node *identNode = newLeafNode(nextTk);
        _Bool b = maintainSymbolTable(nextTk);
        ps.name = "";
        if(!b){
            nextTk = nextToken();
            return NULL;
        }
        nextTk = nextToken();
        return identNode;
    }
    printf("Variable required!");
    synataxError = 1;
    return NULL;
}

_Bool maintainSymbolTable(Token *token){
    if(symbolTableCreated){
        if(varDeclared(token)){
            return 1;
        }
        else{
            printf("Variable %s was never declared!\n", token->lexeme);
            synataxError = 1;
            return 0;
        }
    }
    else{
        ps.name = token->lexeme;
        Symbol *symbol = newSymbol(ps);
        if(symbolInTable(symbol)){
            printf("Variable %s was already declared!\n", token->lexeme);
            synataxError = 1;
            revertOffset(symbol);
            return 0;
        }
        else{
            addSymbolToTable(symbol);
            return 1;
        }
    }
}


