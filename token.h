#ifndef TOKEN_H
#define TOKEN_H

/*Token.h: For the person writing the lexer, this file 
**should remain untouched!
*/

#include <iostream>
#include "lexer.h"

enum tokenName {
    tn_error = -1,
    tn_null = 0,

    tn_print,   //print
    tn_input,    //input 
    tn_assign,
    tn_and,
    tn_or,
    
    tn_minus, 
    tn_plus,
    tn_mod,
    tn_mult,
    tn_div,
    tn_lpoint,  //<
    tn_rpoint,  //>
    tn_lshift,  //<<
    tn_rshift,  //>>
    tn_lvalue,  //this
    tn_rvalue
};

enum tokenPriority {
    tp_error = -1,
    tp_null,

    tp_print,
    tp_input,
    tp_assign,
    tp_or,
    tp_and,
    
    tp_minus, 
    tp_plus = tp_minus,
    tp_mod,
    tp_mult,
    tp_div,
    tp_lpoint,
    tp_rpoint = tp_lpoint,
    tp_lshift,
    tp_rshift = tp_lshift,
    tp_lvalue,
    tp_rvalue = tp_lvalue
};

struct Token {
    tokenName name;
    tokenPriority priority;
    int val;

    void setConstVal(int data);
    void setThisVal(int data);
    void print();
    int isValid();
};

enum Side {left, right};

Token *createTokenList(Lexeme* lexlist);
Token convertLexemeToToken(Lexeme);
void printTokenList(Token*);
void destroyTokenList(Token*);

#endif
