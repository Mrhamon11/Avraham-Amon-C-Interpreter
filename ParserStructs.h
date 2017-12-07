//
// Created by hamon11 on 12/3/17.
//

#ifndef ASSIGNMENT_6_TOP_DOWN_PARSER_PARSER_DATASTRUCTS_H
#define ASSIGNMENT_6_TOP_DOWN_PARSER_PARSER_DATASTRUCTS_H

#include "TokenizerStructs.h"



typedef struct Node Node;

typedef enum NodeType NodeType;
typedef struct PotentialSymbol PotentialSymbol;
typedef struct Symbol Symbol;

Symbol* newSymbol(PotentialSymbol ps);
_Bool symbolInTable(Symbol *symbol);
_Bool varDeclared(Token *token);
void addSymbolToTable(Symbol *symbol);
void printTable();

int offset = 0;
int symbolsInTable = 0;
//SymbolTable *table = initSymbolTable();

enum NodeType{
    INNER,
    LEAF
};

struct Node{
    NodeType kind;
    union{
        char *LHS;
        Token token;
    } data;

    Node *firstChild;
    Node *rightSibling;
};

Node* newInnerNode(char *LHS){
    Node *newNode = malloc(sizeof(Node));
    newNode->data.LHS = LHS;
    newNode->kind = INNER;
    newNode->firstChild = NULL;
    newNode->rightSibling= NULL;
}

Node* newLeafNode(Token *token){
    Node *newNode = malloc(sizeof(Node));
    char *copy;
    copy = malloc(sizeof(char) * strlen(token->lexeme));
    strcpy(copy, token->lexeme);
    Token newTk = *tokenInit(copy, token->type);
    newNode->data.token = newTk;
    newNode->kind = LEAF;
    newNode->firstChild = NULL;
    newNode->rightSibling= NULL;
}

void printNodeData(Node *node){
    if(node->kind == INNER){
        printf("Non-Terminal: %s\n", node->data.LHS);
    }
    else{
        printf("Lexeme: %s\n", node->data.token.lexeme);
    }
}

void printTree(Node *root){
    printNodeData(root);
    if(root->firstChild != NULL){
        printTree(root->firstChild);
    }
    if(root->rightSibling != NULL){
        printTree(root->rightSibling);
    }
}

struct PotentialSymbol{
    Type type;
    char *name;
};

void initPS(PotentialSymbol ps){
    ps.type = NULL_TYPE;
    ps.name = "";
};

struct Symbol{
    Type type;
    char *name;
    int offset;
};

Symbol table[1000];

Symbol* newSymbol(PotentialSymbol ps){
    Symbol *symbol = malloc(sizeof(Symbol));

    char *copy;
    copy = malloc(sizeof(char) * strlen(ps.name));
    strcpy(copy, ps.name);

    symbol->type = ps.type;
    symbol->name = copy;
    symbol->offset = offset;

    if(symbol->type == INT_KEYWORD) {
        symbol->type = INT_TYPE;
    }
    else if(symbol->type == CHAR_KEYWORD){
        symbol->type = CHAR_TYPE;
    }
    else{
        //bad symbol
        return NULL;
    }
    offset++;

    return symbol;
}

void revertOffset(Symbol *symbol){
    offset -= symbol->offset;
}

Symbol* getSymbolInTable(char *varName){
    int i;
    for(i = 0; i < symbolsInTable; i++){
        if(strcmp(table[i].name, varName) == 0){
            return &table[i];
        }
    }
    return NULL;
}

_Bool symbolInTable(Symbol *symbol){
    int i;
    for(i = 0; i < symbolsInTable; i++){
        if(strcmp(table[i].name, symbol->name) == 0){
            return 1;
        }
    }
    return 0;
}

_Bool varDeclared(Token *token){
    int i;
    for(i = 0; i < symbolsInTable; i++){
        if(strcmp(table[i].name, token->lexeme) == 0){
            return 1;
        }
    }
    return 0;
}

void addSymbolToTable(Symbol *symbol){
    table[symbolsInTable] = *symbol;
    symbolsInTable++;
}


void printTable(){
    printf("Printing contents of Symbol Table:\n\n");
    int i;
    for(i = 0; i < symbolsInTable; i++){
        printf("Type: %s - Name: %s - Offset: %d\n", strEnums[table[i].type], table[i].name, table[i].offset);
    }
    printf("\n");
}




#endif //ASSIGNMENT_6_TOP_DOWN_PARSER_PARSER_DATASTRUCTS_H
