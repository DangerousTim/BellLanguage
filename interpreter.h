#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include "token.h"
#include "parser.h"
#include "error.h"

#define TAPE_SIZE 1024

Token solve(treeNode*);	

Token funcAssign(treeNode*);
Token funcPoint(treeNode*, Side);
Token funcShift(treeNode*, Side);
Token funcThis();

Token funcDiv(treeNode*);
Token funcMult(treeNode*);
Token funcAdd(treeNode*);
Token funcSub(treeNode*);

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
};

#endif
