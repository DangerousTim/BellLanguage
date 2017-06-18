#include "error.h"

using std::cout;

void tokenError(const char msg[]){
	cout<<"Token error: "<<msg<<'\n';
}

void syntaxError(const char msg[]){
	cout<<"Syntax error: "<<msg<<'\n';
}

void execError(const char msg[]){
	cout<<"Execution error: "<<msg<<'\n';
}
