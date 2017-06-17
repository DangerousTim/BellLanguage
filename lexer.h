#ifndef LEXER_H                     //Header guard
#define LEXER_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include "error.h"

struct Lexeme{
    char text[1024];	//Does it have to be soo big?
    int length;
};

//No need to declare extern here... Only where it is used

Lexeme *createLexemeList(char*);
void destroyLexemeList(Lexeme*);
void printLexemeList(Lexeme*);

int lex_init(char buffer[]);        //initialises lexer. Lexer is to be called through this function.
int lex_makelexeme(Lexeme &lex);    //Makes Lexemes. Lex_calls this.
int check(Lexeme & lex);

#endif // LEXER_H                   //header guard end
