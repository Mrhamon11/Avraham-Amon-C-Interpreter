//
// Created by Avi on 11/15/2017.
//

#ifndef ASSIGNMENT_6_TOP_DOWN_PARSER_FIRSTFINDER_H
#define ASSIGNMENT_6_TOP_DOWN_PARSER_FIRSTFINDER_H

int stringArrayLength(char *array[]);
_Bool inFirst(char *firstArray[], Token *token);


char *whileRule[] = {"while", NULL};
char *listOfVariableCommaRule[] = {"IDENTIFIER", NULL};
char *assignRule[] = {"IDENTIFIER", NULL};
char *litRule[] = {"INTEGER_CONSTANT", "CHAR_CONSTANT", "IDENTIFIER", "(", NULL};
char *uopRule[] = {"INTEGER_CONSTANT", "IDENTIFIER", "CHAR_CONSTANT", "(", "!", "-", "~", NULL};
char *multDivModRule[] = {"INTEGER_CONSTANT", "IDENTIFIER", "CHAR_CONSTANT", "(", "!", "-", "~", NULL};
char *plusMinusRule[] = {"INTEGER_CONSTANT", "IDENTIFIER", "CHAR_CONSTANT", "(", "!", "-", "~", NULL};
char *compareRule[] = {"INTEGER_CONSTANT", "IDENTIFIER", "CHAR_CONSTANT", "(", "!", "-", "~", NULL};
char *equalityRule[] = {"INTEGER_CONSTANT", "IDENTIFIER", "CHAR_CONSTANT", "(", "!", "-", "~", NULL};
char *bopbandRule[] = {"INTEGER_CONSTANT", "IDENTIFIER", "CHAR_CONSTANT", "(", "!", "-", "~", NULL};
char *bopborRule[] = {"INTEGER_CONSTANT", "IDENTIFIER", "CHAR_CONSTANT", "(", "!", "-", "~", NULL};
char *boplandRule[] = {"INTEGER_CONSTANT", "IDENTIFIER", "CHAR_CONSTANT", "(", "!", "-", "~", NULL};
char *expRule[] = {"INTEGER_CONSTANT", "IDENTIFIER", "CHAR_CONSTANT", "(", "!", "-", "~", NULL};
char *ifRule[] = {"if", NULL};
char *listOfExpressionsRule[] = {"INTEGER_CONSTANT", "IDENTIFIER", "CHAR_CONSTANT", "(", "!", "-", "~", NULL};
char *coutRule[] = {"cout", NULL};
char *listofvariableangleRule[] = {"IDENTIFIER", NULL};
char *cinRule[] = {"cin", NULL};
char *statementRule[] = {"cin", "cout", "if", "IDENTIFIER", "while", "{", "return", NULL};
char *typeRule[] = {"int", "char", NULL};
char *variableRule[] = {"IDENTIFIER", NULL};
char *variablesRule[] = {"IDENTIFIER", NULL};
char *declarationRule[] = {"int", "char", NULL};
char *listOfDeclarationsRule[] = {"int", "char", "", NULL};
char *listOfStatementsRule[] = {"cin", "cout", "if", "IDENTIFIER", "while", "{", "return", "", NULL};
char *programRule[] = {"int", "char", "cin", "cout", "if", "IDENTIFIER", "while", "{", "return", "", NULL};

_Bool inFirst(char *firstArray[], Token *token){
    int i;
    int length = stringArrayLength(firstArray);
    for(i = 0; i < length; i++){
        if(strcmp(firstArray[i], token->lexeme) == 0 || strcmp(firstArray[i], strEnums[token->type]) == 0) {
            return 1;
        }
    }
    return 0;
}

int stringArrayLength(char *array[]){
    int length = 0;
    int i;
    for(i = 0; array[i] != NULL; i++){
        length++;
    }
    return length;
}



#endif //ASSIGNMENT_6_TOP_DOWN_PARSER_FIRSTFINDER_H
