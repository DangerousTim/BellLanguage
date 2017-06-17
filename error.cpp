#include "error.h"

using std::cout;

void syntaxError(const char msg[]){
	cout<<"Syntax error: "<<msg<<'\n';
}

void execError(const char msg[]){
	cout<<"Execution error: "<<msg<<'\n';
}
