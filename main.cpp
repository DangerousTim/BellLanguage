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

int main(void){	
	char s[100];
	cin.getline(s, 100);
	
	treeNode *root = NULL;
	Lexeme *lexlist = createLexemeList(s);

	Token *toklist = createTokenList(lexlist);
	
	for (int i = 0; toklist[i].name != tn_null; i++)
		root = insertToken(root, toklist[i]);

	
	destroyLexemeList(lexlist);
	destroyTokenList(toklist);

	if (syntax(root) != tn_error){
		cout<<"Output: \n";
		solve(root).print();
		cout<<"Memory: \n";
		memory.printTape(0, 10);
	}
	else cout<<"Error\n";

	deleteTree(root);
}
