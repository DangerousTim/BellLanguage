#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include "token.h"
#include "parser.h"

#define TAPE_SIZE 1024

/*syntax analyser*/

tokenName syntax(treeNode*);

tokenName syntaxExit(treeNode*);
tokenName syntaxOutput(treeNode*);
tokenName syntaxInput(treeNode*);
tokenName syntaxShift(treeNode*);
tokenName syntaxAssignAndPoint(treeNode*);
tokenName syntaxBinary(treeNode*);
tokenName syntaxPlusMinus(treeNode*);
tokenName syntaxThis(treeNode*);
tokenName syntaxConst(treeNode*);

/*solver*/

Token solve(treeNode*);	

Token funcExit();
Token funcAssign(treeNode*);
Token funcPoint(treeNode*, Side);
Token funcShift(treeNode*, Side);
Token funcThis();

Token funcAnd(treeNode*);
Token funcOr(treeNode*);
Token funcEq(treeNode*);
Token funcLt(treeNode*);
Token funcGt(treeNode*);

Token funcDiv(treeNode*);
Token funcMult(treeNode*);
Token funcMod(treeNode*);
Token funcAdd(treeNode*);
Token funcSub(treeNode*);

Token funcMem(treeNode*);
Token funcInput(treeNode*);
Token funcPrint(treeNode*);

/*Memory class: handles virtual program memory*/
class Memory {
	static int tape[TAPE_SIZE];
	unsigned int index;

	public:
	Memory(){ index = 0; }

	int readVal(int steps=0);
	void writeVal(int data);
	void movePointer(int steps);
	int currentIndex();
	void writeAtLocation(int idx, int data);
	void printTape(int num);
};

#endif
