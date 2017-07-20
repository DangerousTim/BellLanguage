#include <iostream>
#include <fstream>
#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "interpreter.h"

using namespace std;

char buffer1[1023];

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
			solve(root).print();	//for debugging purpose
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
	ifstream file;
	file.open(filename, ios::in);

    if (!file.is_open()) {
        cout << "File " << filename << " does not exist.\n";
     	return -1;
    }

    while(!file.eof()) {
        file.getline(buffer1,1023);
        buffer1[1023]='\0';
        executeLine(buffer1);
    }
    return 0;
}

int main(void){
    readfile("test.txt");   /*Only works if test.txt is in same directory as project
                                Else, address of file has to be written
                                    eg. C:\\Users\\Desktop\\Ron\\bell-master\\test.txt*/

        while (!programExit){
		char s[100];
		cout<<"bell$ ";
		cin.getline(s, 100);
		executeLine(s);
	}
	return 0;
}
