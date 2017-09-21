#include <iostream>
#include <fstream>
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "interpreter.h"

using namespace std;

extern Memory memory;
extern short programExit;

int executeLine(char s[]){	

	Lexeme *lexlist = createLexemeList(s);		//make lexeme list
	Token *toklist = createTokenList(lexlist);	//make token list

	//unrecognized token present then toklist[0] has tokErr
	if (toklist[0].name != tn_error){

		treeNode *root = NULL;
		//create parse tree
		for (int i = 0; toklist[i].isValid(); i++)
			root = insertToken(root, toklist[i]);

/*		cout<<"Tok list:\n";
		printTokenList(toklist);
		cout<<"Post order:\n";
		postOrder(root);
		cout<<'\n';
*/
		//check if there's a syntax error
		//if there is, don't execute
		if (syntax(root) != tn_error){
			solve(root);	//add .print() for debugging purpose
			cout<<'\n';
		}

		else {
			cout<<"syntax error\n";	
			return -1;
		}

		deleteTree(root);
	}
	else
		return -1;

	//clean up
	destroyLexemeList(lexlist);
	destroyTokenList(toklist);
}

int readfile(const char *filename){
	char buffer1[1023];
	ifstream file;
	file.open(filename, ios::in);

	if (!file.is_open()) {
		cout << "File " << filename << " does not exist.\n";
	 	return -1;
	}

	while(!file.eof()) {
		file.getline(buffer1, 1023);
		executeLine(buffer1);
	}
	return 0;
}

int main(){
	cout<<"Do you want to run "<<filename<<" y/n: ";
	char c;
	cin>>c;
	if (c == 'y'){
		readfile(filename);  
		return 0;
	}

	cout<<"Running command line interpreter mode...\n\n";
	while (!programExit){
		char s[100];
		cout<<"bell$ ";
		cin.getline(s, 100);
		executeLine(s);
	}
	return 0;
}
