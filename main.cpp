#include <iostream>
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "interpreter.h"

using std::cout;
using std::cin;

void postOrder(treeNode *leaf){
	if (leaf != NULL){
		postOrder(leaf->left);
		postOrder(leaf->right);
		leaf->token.print();
	}
}

extern Memory memory;

/*
>, < only returns rvalue
>>, << returns current val, in lvalue format
= does solve lhs, store mem index, solve rhs, input at stored mem index
this>>3>>3 should work but not this>3>>4 but yes this>>3>4
*/
int main(void){
	treeNode *root = NULL;
	
	char s[100];
	cin.getline(s, 100);
	
	Lexeme *lexlist = createLexemeList(s);
	Token *toklist = createTokenList(lexlist);
	destroyLexemeList(lexlist);
	destroyTokenList(toklist);


	//postOrder(root);
	deleteTree(root);
}
