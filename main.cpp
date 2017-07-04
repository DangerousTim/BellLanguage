#include <iostream>
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "interpreter.h"

using std::cout;
using std::cin;

extern Memory memory;
extern short programExit;

int main(void){

	while (!programExit){	
		char s[100];
		cout<<"bell$ ";
		cin.getline(s, 100);
	
		Lexeme *lexlist = createLexemeList(s);		//make lexeme list
		Token *toklist = createTokenList(lexlist);	//make token list
		
		//unrecognized token present then toklist[0] has tokErr
		if (toklist[0].name != tn_error){

			treeNode *root = NULL;
			//create parse tree
			for (int i = 0; toklist[i].isValid(); i++)
				root = insertToken(root, toklist[i]);
			
			//check if there's a syntax error
			//if there is, don't execute
			if (syntax(root) != tn_error){
				solve(root).print();	//for debugging purpose
				cout<<'\n';
			}
			else
				cout<<"syntax error\n";	

			deleteTree(root);
		}

		//clean up
		destroyLexemeList(lexlist);
		destroyTokenList(toklist);
	}
	return 0;
}
